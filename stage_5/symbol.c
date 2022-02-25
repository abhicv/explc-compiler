#include "symbol.h"
#include "ast.h"

struct GlobalSymbolTable globalSymbolTable;
const unsigned int stackStartAddress = 4096;
    
struct LocalSymbolTable localSymbolTable;
int returnType = 0;
int localVariableCount = 0;

char *TypeToString(int type)
{
    if(type == INTEGER_TYPE)
    {
        return "int";
    }
    else if(type == STRING_TYPE)
    {
        return "str";
    }
    else if(type == POINTER_INT_TYPE)
    {
        return "int *";
    }
    else if(type == POINTER_STR_TYPE)
    {
        return "str *";
    }
    else if(type == BOOLEAN_TYPE)
    {
        return "bool";
    }
    else
    {
        return 0;
    }
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

void InstallParam(struct ParamList *list, char *name, int type)
{
    struct Param *param = LookUpParamList(*list, name);

    if(param)
    {
        printf("[ERROR] parameter with similar name exist -> '%s'!\n", name);
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
        param.type = type;
        list->params[list->size - 1] = param;
    }
}

void PrintParamList(struct ParamList list)
{
    for(int n = 0; n < list.size; n++)
    {
        struct Param param = list.params[n];
        printf("   param [%d] name: '%s', type: '%s'\n", n, param.name, TypeToString(param.type));
    }
}

struct GlobalSymbol *LookUpGlobalSymbolTable(struct GlobalSymbolTable table, char *name)
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

void InstallGlobalSymbol(struct GlobalSymbolTable *table, char *name, int type, int size)
{
    struct GlobalSymbol *symbol = LookUpGlobalSymbolTable(*table, name);

    if(symbol)
    {
        printf("[ERROR] multiple declaration of variable -> '%s'!\n", name);
        exit(1);
    }
    else
    {
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

        struct GlobalSymbol symbol = {0};
        symbol.name = name;
        symbol.type = type;
        symbol.size = size;
        symbol.binding = stackStartAddress + table->staticAddressOffset;
        table->staticAddressOffset += size;

        table->symbols[table->size - 1] = symbol;
    }
}

void PrintGlobalSymbolTable(struct GlobalSymbolTable table)
{
    for(int n = 0; n < table.size; n++)
    {
        struct GlobalSymbol symbol = table.symbols[n];
        printf("[%d] name: %s, size: %d, addr: %d, type: %s, col_size: %d, array_dim: %d\n", n, symbol.name, symbol.size, symbol.binding, TypeToString(symbol.type), symbol.colSize, symbol.arrayDim);
    }
}

struct LocalSymbol *LookUpLocalSymbolTable(struct LocalSymbolTable table, char *name)
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

void InstallLocalSymbol(struct LocalSymbolTable *table, char *name, int type)
{
    struct LocalSymbol *symbol = LookUpLocalSymbolTable(*table, name);

    if(symbol)
    {
        printf("[ERROR] multiple declaration of variable -> '%s'!\n", name);
        exit(1);
    }
    else
    {
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

        struct LocalSymbol symbol = {0};
        symbol.name = name;
        symbol.type = type;
        symbol.binding = 0;
        table->symbols[table->size - 1] = symbol;
    }
}

void PrintLocalSymbolTable(struct LocalSymbolTable table)
{
    for(int n = 0; n < table.size; n++)
    {
        struct LocalSymbol symbol = table.symbols[n];
        printf("[%d] name: %s, addr: %d, type: %s\n", n, symbol.name, symbol.binding, TypeToString(symbol.type));
    }
}
