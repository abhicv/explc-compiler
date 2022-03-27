#include "symbol.h"
#include "ast.h"

struct GlobalSymbolTable globalSymbolTable;
struct TypeTable typeTable;

const unsigned int stackStartAddress = 4096;

int returnTypeIndex = 0;

char *TypeToString(int type)
{
    if(type == INTEGER_TYPE) return "int";
    else if(type == STRING_TYPE) return "str";
    else if(type == POINTER_INT_TYPE) return "int *";
    else if(type == POINTER_STR_TYPE) return "str *";
    else if(type == BOOLEAN_TYPE) return "bool";
    else return "unknown type";
}

struct Param* LookUpParamList(struct ParamList list, char *name)
{
    for(int n = 0; n < list.size; n++)
    {
        if(!strcmp(list.params[n].name, name))
        {
            return (list.params + n);
        }
    }
    return 0;
}

void InstallParam(struct ParamList *list, char *name, int typeIndex)
{
    struct Param *param = LookUpParamList(*list, name);

    if(param)
    {
        printf("error: parameter with similar name exist '%s'!\n", name);
        exit(1);
    }
    else
    {
        if(list->size == 0)
        {
            list->size++;
            list->params = (struct Param*)malloc(sizeof(struct Param));
        }
        else
        {
            list->size++;
            list->params = (struct Param*)realloc(list->params, list->size * sizeof(struct Param));
        }

        struct Param param = {0};
        param.name = name;
        param.typeIndex = typeIndex;
        list->params[list->size - 1] = param;
    }
}

void PrintParamList(struct ParamList list)
{
    for(int n = 0; n < list.size; n++)
    {
        struct Param param = list.params[n];
        printf("param [%d] name: '%s', type: '%d'\n", n, param.name, param.typeIndex);
    }
}

struct GlobalSymbol *LookUpGlobalSymbolTable(struct GlobalSymbolTable table, const char *name)
{
    for(int n = 0; n < table.size; n++)
    {
        if(!strcmp(table.symbols[n].name, name))
        {
            return (table.symbols + n);
        }
    }
    return 0;
}

void InstallGlobalSymbol(struct GlobalSymbolTable *table, struct GlobalSymbol symbol)
{
    if(LookUpGlobalSymbolTable(*table, symbol.name))
    {
        printf("error: redeclaration of variable '%s'\n", symbol.name);
        exit(1);
    }

    if(table->size == 0)
    {
        table->size++;
        table->symbols = (struct GlobalSymbol*)malloc(sizeof(struct GlobalSymbol));
    }
    else
    {
        table->size++;
        table->symbols = (struct GlobalSymbol*)realloc(table->symbols, sizeof(struct GlobalSymbol) * table->size);
    }

    symbol.binding = stackStartAddress + table->staticAddressOffset;
    table->staticAddressOffset += typeTable.types[symbol.typeIndex].size;
    table->symbols[table->size - 1] = symbol;
}

void PrintGlobalSymbolTable(struct GlobalSymbolTable table)
{
    for(int n = 0; n < table.size; n++)
    {
        struct GlobalSymbol symbol = table.symbols[n];
        printf("[%d] name: %s, addr: %d, type: %d, col_size: %d, array_dim: %d\n", n, symbol.name, symbol.binding, symbol.typeIndex, symbol.colSize, symbol.arrayDim);
    }
}

struct LocalSymbol *LookUpLocalSymbolTable(struct LocalSymbolTable table, const char *name)
{
    for(int n = 0; n < table.size; n++)
    {
        if(!strcmp(table.symbols[n].name, name))
        {
            return (table.symbols + n);
        }
    }
    return 0;
}

void InstallLocalSymbol(struct LocalSymbolTable *table, struct LocalSymbol symbol)
{
    if(LookUpLocalSymbolTable(*table, symbol.name))
    {
        printf("error: redeclaration of variable '%s'\n", symbol.name);
        exit(1);
    }

    if(table->size == 0)
    {
        table->size++;
        table->symbols = (struct LocalSymbol*)malloc(sizeof(struct LocalSymbol));
    }
    else
    {
        table->size++;
        table->symbols = (struct LocalSymbol*)realloc(table->symbols, sizeof(struct LocalSymbol) * table->size);
    }

    table->symbols[table->size - 1] = symbol;
}

void PrintLocalSymbolTable(struct LocalSymbolTable table)
{
    for(int n = 0; n < table.size; n++)
    {
        struct LocalSymbol symbol = table.symbols[n];
        printf("[%d] name: %s, addr: %d, type: %d\n", n, symbol.name, symbol.binding, symbol.typeIndex);
    }
}

struct Type *LookUpTypeTable(struct TypeTable table, const char* name)
{
    for(int n = 0; n < table.size; n++)
    {
        if(!strcmp(table.types[n].name, name))
        {
            return (table.types + n);
        }
    }
    return 0;
}

int LookUpTypeTableIndex(struct TypeTable table, const char* name)
{
    for(unsigned int n = 0; n < table.size; n++)
    {
        if(!strcmp(table.types[n].name, name))
        {
            return n;
        }
    }
    return -1;
}

void InstallType(struct TypeTable *table, struct Type type)
{
    if(LookUpTypeTable(*table, type.name))
    {
        printf("error: redefinition of type '%s'\n", type.name);
        exit(1);
    }

    if(table->size == 0)
    {
        table->size++;
        table->types = (struct Type*)malloc(sizeof(struct Type));
    }
    else
    {
        table->size++;
        table->types = (struct Type*)realloc(table->types, sizeof(struct Type) * table->size);
    }

    table->types[table->size - 1] = type;
}

void InitializeTypeTable(struct TypeTable *table)
{
    if(table->size == 0)
    {
        struct Type integer = {0};
        integer.name = strdup("int");
        integer.size = 1;

        struct Type string = {0};
        string.name = strdup("str");
        string.size = 1;

        struct Type boolean = {0};
        boolean.name = strdup("bool");
        boolean.size = 1;

        struct Type null = {0};
        null.name = strdup("null");
        null.size = 0;

        InstallType(table, integer);
        InstallType(table, string);
        InstallType(table, boolean);
        InstallType(table, null);
    }
}

void PrintTypeTable(struct TypeTable typeTable)
{
    for(int n = 0; n < typeTable.size; n++)
    {
        struct Type type = typeTable.types[n];
        printf("type [%d] name: '%s', size: %d\n", n+1, type.name, type.size);

        for(int i = 0; i < type.fieldList.count; i++)
        {
            struct Field field = type.fieldList.fields[i];
            char *typeName = typeTable.types[field.typeIndex].name;
            printf("   field [%d] name: '%s', type: '%s'\n", i+1, field.name, typeName);
        }
    }
}

struct Field *LookUpField(struct FieldList list, const char *name)
{
    for(int n = 0; n < list.count; n++)
    {
        if(!strcmp(list.fields[n].name, name))
        {
            return (list.fields + n);
        }
    }
    return 0;
}

void InstallField(struct FieldList *list, struct Field field)
{
    if(LookUpField(*list, field.name))
    {
        printf("error: redeclaration of field '%s'\n", field.name);
        exit(1);
    }

    if(list->count == 0)
    {
        list->count++;
        list->fields = (struct Field*)malloc(sizeof(struct Field));
    }
    else
    {
        list->count++;
        list->fields = (struct Field*)realloc(list->fields, sizeof(struct Field) * list->count);
    }

    list->fields[list->count - 1] = field;
}
