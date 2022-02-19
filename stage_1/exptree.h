#ifndef EXPTREE_H
#define EXPTREE_H

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    char op;    
    int isLeafNode;
    struct Node *left;
    struct Node *right;
};

struct Node *MakeLeafNode(int n);
struct Node* MakeOperatorNode(char op, struct Node *left, struct Node *right);
int Evaluate(struct Node *node);
void PostFixForm(struct Node *node);
void PreFixForm(struct Node *node);

int GetRegister();
void FreeRegister();
int GenerateCode(struct Node *node, FILE *output);

#endif