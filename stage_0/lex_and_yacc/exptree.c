#include "exptree.h"
#include <stdlib.h>

struct Node *MakeLeafNode(int n)
{
    struct Node *leaf = (struct Node*)malloc(sizeof(struct Node));
    leaf->val = n;
    leaf->right = 0;
    leaf->left = 0;
    leaf->isLeafNode = 1;    
    return leaf;
}

struct Node* MakeOperatorNode(char op, struct Node *left, struct Node *right)
{
    struct Node *opNode =  (struct Node*)malloc(sizeof(struct Node));
    opNode->isLeafNode = 0;
    opNode->left = left;
    opNode->right = right;
    opNode->op = op;

    return opNode;
}

int Evaluate(struct Node *node)
{
    if(node->isLeafNode == 1)
    {
        return node->val;
    }

    switch (node->op)
    {
        case '+':  return Evaluate(node->left) + Evaluate(node->right); break;
        case '-':  return  Evaluate(node->left) - Evaluate(node->right); break;
        case '*':  return Evaluate(node->left) * Evaluate(node->right); break;
        case '/':  return Evaluate(node->left) / Evaluate(node->right); break;
    }
}