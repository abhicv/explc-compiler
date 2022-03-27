#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Param
{
    int typeIndex;
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
    int typeIndex;
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
    int typeIndex;
    int binding;
};

struct LocalSymbolTable
{
    struct LocalSymbol *symbols;
    unsigned int size;
};

struct Field
{
    char *name;
    unsigned int typeIndex;
};

struct FieldList
{
    struct Field *fields;
    unsigned int count;
};

struct Type
{
    char *name;
    unsigned int size;
    struct FieldList fieldList;
};

struct TypeTable
{
    struct Type *types;
    unsigned int size;
};

char *TypeToString(int type);
struct GlobalSymbol *LookUpGlobalSymbolTable(struct GlobalSymbolTable table, const char *name);
struct LocalSymbol *LookUpLocalSymbolTable(struct LocalSymbolTable table, const char *name);
int LookUpTypeTableIndex(struct TypeTable table, const char* name);

#endif