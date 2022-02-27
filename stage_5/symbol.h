#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Param
{
    int type;
    char *name;
};

struct ParamList
{
    struct Param *params;
    unsigned int size;
};

struct GlobalSymbol
{
    char* name;            
    int type;                       
    int size;             
    int binding;
    
    int colSize;
    int arrayDim;

    int functionLabel;

    struct ParamList *paramList;
};

struct GlobalSymbolTable
{
    struct GlobalSymbol *symbols;
    unsigned int size;
    unsigned int staticAddressOffset;
};

struct LocalSymbol
{
    char* name;
    int type;
    int binding;
};

struct LocalSymbolTable
{
    struct LocalSymbol *symbols;
    unsigned int size;
};

char *TypeToString(int type);

#endif