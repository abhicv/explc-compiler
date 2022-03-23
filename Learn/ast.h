#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum NodeType
{
    NODE_PROGRAM,
    NODE_PROC_DEF,
    NODE_STRUCT_DEF,
    NODE_VAR_DECL,
    NODE_FIELD,
    NODE_BIN_OP,
    NODE_STATEMENT_LIST,
    NODE_ASSIGN_STATEMENT,
    NODE_IF_STATEMENT,
    NODE_WHILE_STATEMENT,
    NODE_RETURN_STATEMENT,
    NODE_PROC_CALL,
    NODE_IDENTIFIER,
    NODE_INTEGER_CONSTANT,

    NODE_COUNT
};

enum BinaryOperator
{
    BIN_OP_ADD,
    BIN_OP_SUB,
    BIN_OP_MUL,
    BIN_OP_DIV,
};

typedef unsigned int Index;

typedef struct Node Node;
struct Node
{
    unsigned int type;

    union
    {
        struct //program
        {
            Index *indexList;
            unsigned int indexCount;
        };

        struct //struct def
        {
            const char *structName;
            Index *fieldIndexList;
            unsigned int fieldIndexCount;
        };

        struct // procedure def or any block of statement
        {
            const char *procName;
            Index *parameterIndexList;
            unsigned int parameterIndexCount;
            Index *returnIndexList;
            unsigned int returnIndexCount;
            Index procBody;
        };
                    
        struct // binary operator or assignemnt statement
        {
            unsigned int binOpType;
            Index left;
            Index right;
        };

        struct // while and if-else statement
        {
            Index conditionExpr;
            Index trueBlock;
            Index falseBlock;
        };

        struct //identifier
        {
            const char *identifier;
        };

        struct //integer constant
        {
            int value;
        };
    };
};

typedef struct AST AST;
struct AST
{
    Node *nodeList;
    unsigned int nodeCount;
};

void InitAST(AST *ast);
Index PushNode(AST *ast, Node node);
void PushIndex(Index **indexList, unsigned int *indexCount, Index index);

#endif