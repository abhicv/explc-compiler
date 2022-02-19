#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>

enum NodeType
{
    CONNECTOR_NODE = 1,
    READ_NODE,
    WRITE_NODE,
    OPERATOR_NODE,
    IDENTIFIER_NODE,
    INTEGER_NODE,
};

enum VariableType
{
    INTEGER_TYPE = 1,
    STRING_TYPE,
};

struct ASTNode
{
    int val;
    char op;
    char *varName;    
    int nodeType;
    int varType;

    struct ASTNode *left;
    struct ASTNode *right;
};

struct ASTNode* CreateASTNode(int val, char op, char *varName, int nodeType, int varType, struct ASTNode *left, struct ASTNode *right);

int GetRegister();
void FreeRegister();
int GenerateCode(struct ASTNode *node, FILE *output);
int EvaluateAST(struct ASTNode *node);
void PrintAST(struct ASTNode* node, int indent);
#endif