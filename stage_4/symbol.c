#include "symbol.h"
#include "ast.h"

struct GlobalSymbolTable globalSymbolTable;
const unsigned int stackStartAddress = 4096;

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

        struct GlobalSymbol symbol;
        symbol.name = name;
        symbol.type = type;
        symbol.size = size;
        symbol.binding = stackStartAddress + table->staticAddressOffset;
        table->staticAddressOffset += size;

        table->symbols[table->size - 1] = symbol;
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

char *TypeToString(int type)
{
    if(type == INTEGER_TYPE)
    {
        return "INT";
    }
    else if(type == STRING_TYPE)
    {
        return "STR";
    }
    else if(type == POINTER_INT_TYPE)
    {
        return "INT PTR";
    }
    else if(type == POINTER_STR_TYPE)
    {
        return "STR PTR";
    }
    else if(type == BOOLEAN_TYPE)
    {
        return "BOOL";
    }
    else
    {
        return 0;
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