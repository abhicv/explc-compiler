#include "ast.h"

#define MAX_NODE_COUNT 1000

void InitAST(AST *ast)
{
    ast->nodeList = (Node*)malloc(sizeof(Node) * MAX_NODE_COUNT);
    ast->nodeCount = 0;
}

Index PushNode(AST *ast, Node node)
{
    if(ast->nodeCount < MAX_NODE_COUNT)
    {
        Index index = ast->nodeCount;
        ast->nodeList[index] = node;
        ast->nodeCount++;
        return index;
    }
    else
    {
        printf("internal error: AST node list full!");
        exit(1);
    }
}

void PushIndex(Index **indexList, unsigned int *indexCount, Index index)
{
    if((*indexCount) == 0)
    {
        (*indexCount)++;
        (*indexList) = (Index*)malloc(sizeof(Index));
    }
    else
    {
        (*indexCount)++;
        (*indexList) = (Index*)realloc((*indexList), sizeof(Index) * (*indexCount));
    }

    (*indexList)[(*indexCount) - 1] = index;
}