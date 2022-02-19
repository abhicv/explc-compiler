#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>

enum NodeType
{
    CONNECTOR_NODE = 1,

    READ_NODE,
    WRITE_NODE,

    //binary operators
    PLUS_OP_NODE,
    MINUS_OP_NODE,
    MUL_OP_NODE,
    DIV_OP_NODE,

    LT_OP_NODE,
    LT_EQ_OP_NODE,
    GT_OP_NODE,
    GT_EQ_OP_NODE,
    EQUAL_EQ_OP_NODE,
    NOT_EQ_OP_NODE,

    EQ_OP_NODE,

    IF_NODE,
    BRANCH_NODE,
    WHILE_NODE,

    BREAK_NODE,
    CONTINUE_NODE,
    
    IDENTIFIER_NODE,
    INTEGER_NODE,
};

enum VariableType
{
    INTEGER_TYPE = 1,
    BOOLEAN_TYPE,
    STRING_TYPE,
};

// +, -, *, /, >, >=, <, <= , ==, != 
#define IS_OPERATOR_NODE(n) (n == PLUS_OP_NODE) || (n == MINUS_OP_NODE) || (n == MUL_OP_NODE) || (n == DIV_OP_NODE) \
            || (n == LT_OP_NODE) || (n == LT_EQ_OP_NODE) || (n == GT_OP_NODE) || (n == GT_EQ_OP_NODE) \
            || (n == EQUAL_EQ_OP_NODE) || (n == NOT_EQ_OP_NODE)

struct ASTNode
{
    int val;
    char *varName;    
    int nodeType;
    int expType;

    struct ASTNode *left;
    struct ASTNode *right;
};

struct ASTNode* CreateASTNode(int val, char *varName, int nodeType, int varType, struct ASTNode *left, struct ASTNode *right);

int GenerateCode(struct ASTNode *node, FILE *output);
int EvaluateAST(struct ASTNode *node);
void PrintAST(struct ASTNode* node, int indent);
#endif