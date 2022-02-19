#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct GlobalSymbol
{
    char* name;            
    int type;                       
    int size;             
    int binding;         
};

struct GlobalSymbolTable
{
    struct GlobalSymbol *symbols;
    unsigned int size;
    unsigned int staticAddressOffset;
};

#endif