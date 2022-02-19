#ifndef EXPTREE_H
#define EXPTREE_H

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

#endif