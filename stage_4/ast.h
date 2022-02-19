#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum NodeType
{
    CONNECTOR_NODE = 1,

    // IO library call
    READ_NODE,
    WRITE_NODE,

    //arithmetic operators
    PLUS_OP_NODE,
    MINUS_OP_NODE,
    MUL_OP_NODE,
    DIV_OP_NODE,
    MOD_OP_NODE,

    //relational operators
    LT_OP_NODE,
    LT_EQ_OP_NODE,
    GT_OP_NODE,
    GT_EQ_OP_NODE,
    EQUAL_EQ_OP_NODE,
    NOT_EQ_OP_NODE,

    //assignemnt operator
    EQ_OP_NODE,

    // control flow
    IF_NODE,
    BRANCH_NODE,
    WHILE_NODE,
    BREAK_NODE,
    CONTINUE_NODE,
    
    // variable names
    IDENTIFIER_NODE,

    // integer literal/constant
    INTEGER_NODE,

    // string literal/constant
    STRING_NODE,

    //array decl/usage
    ARRAY_NODE,

    DEREF_NODE,
    ADDR_OF_NODE,
};

enum VariableType
{
    INTEGER_TYPE = 1,
    STRING_TYPE,
    POINTER_INT_TYPE,
    POINTER_STR_TYPE,
    BOOLEAN_TYPE,
};
 
#define IS_ARITHMETIC_OPERATOR_NODE(n) (n == PLUS_OP_NODE) || (n == MINUS_OP_NODE) || (n == MUL_OP_NODE) \
            || (n == DIV_OP_NODE)

#define IS_BOOLEAN_OPERATOR_NODE(n) (n == LT_OP_NODE) || (n == LT_EQ_OP_NODE) || (n == GT_OP_NODE) \
            || (n == GT_EQ_OP_NODE) || (n == EQUAL_EQ_OP_NODE) || (n == NOT_EQ_OP_NODE)

struct ASTNode
{
    int val;
    char *strVal;
    
    char *varName;    
    int nodeType;
    int expType;

    struct ASTNode *left;
    struct ASTNode *right;

    struct GlobalSymbol *symbol;
};

struct ASTNode* CreateASTNode(int val, char *varName, int nodeType, int varType, struct ASTNode *left, struct ASTNode *right);

#endif