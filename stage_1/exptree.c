#include "exptree.h"

int registers[20] = {0};

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

int GetRegister()
{
    for(int n = 0; n < 20; n++)
    {
        if(registers[n] == 0)
        {
            registers[n] = 1;
            return n;
        }
    }

    return 0;
}

void FreeRegister()
{
    for(int n = 19; n >= 0; n--)
    {
        if(registers[n] == 1)
        {
            registers[n] = 0;
            return;
        }
    }
}

int GenerateCode(struct Node *node, FILE *output)
{
    if(node->isLeafNode)
    {
        int reg = GetRegister();
        fprintf(output, "MOV R%d, %d\n", reg, node->val);
        return reg;
    }

    switch (node->op)
    {
        case '+':
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "ADD R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;

        case '-':
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "SUB R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;

        case '*':  
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "MUL R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;

        case '/':
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "DIV R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
    }
}

void PostFixForm(struct Node *node)
{
    if(node->left)
    {
        PostFixForm(node->left);
    } 

    if(node->right)
    {
        PostFixForm(node->right);
    }

    if(node->isLeafNode)
    {
        printf("%d ", node->val);
    }
    else
    {
        printf("%c ", node->op);
    }    
}

void PreFixForm(struct Node *node)
{
    if(node->isLeafNode)
    {
        printf("%d ", node->val);
    }
    else
    {
        printf("%c ", node->op);
    }

    if(node->left)
    {
        PostFixForm(node->left);
    } 

    if(node->right)
    {
        PostFixForm(node->right);
    }    
}