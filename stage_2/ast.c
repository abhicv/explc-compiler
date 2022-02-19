#include "ast.h"

//keeps track of the free registers (0 = free, 1 = in use)
int registers[20] = {0};

//used by the AST evlaution function as static memory for variables a to z
int virtualMem[26] = {0};

struct ASTNode* CreateASTNode(int val, char op, char *varName, int nodeType, int varType, struct ASTNode *left, struct ASTNode *right)
{
    struct ASTNode *node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    node->val = val;
    node->op = op;
    node->varName = varName;
    node->nodeType = nodeType;
    node->varType = varType;
    node->left = left;
    node->right = right;
    return node;
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

void GenerateReadCode(int mem, FILE *output)
{
    int a = GetRegister();

    fprintf(output, "\n");
    fprintf(output, "MOV R%d, \"Read\"\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "MOV R%d, -1\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "MOV R%d, %d\n", a, mem);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "CALL 0\n");
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "\n");
    
    FreeRegister();
}

void GenerateWriteCode(int reg, FILE *output)
{
    int a = GetRegister();
    
    fprintf(output, "\n");
    fprintf(output, "MOV R%d, \"Write\"\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "MOV R%d, -2\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "PUSH R%d\n", reg);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "CALL 0\n");
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "POP R%d\n", a);
    fprintf(output, "\n");

    FreeRegister();
}

int GenerateCode(struct ASTNode *node, FILE *output)
{
    switch (node->nodeType)
    {
        case CONNECTOR_NODE:
        {
            GenerateCode(node->left, output);
            GenerateCode(node->right, output);
        }
        break;

        case WRITE_NODE:
        {
            int reg = GenerateCode(node->left, output);
            GenerateWriteCode(reg, output);
            FreeRegister();
        }
        break;

        case READ_NODE:
        {
            int mem = 4096 + (node->left->varName[0] - 'a');
            GenerateReadCode(mem, output);
        }
        break;

        case INTEGER_NODE:
        {
            int reg = GetRegister();
            fprintf(output, "MOV R%d, %d\n", reg, node->val);
            return reg;
        }
        break;

        case IDENTIFIER_NODE:
        {
            char var = node->varName[0];
            int mem = 4096 + (var - 'a');
            int reg = GetRegister();
            fprintf(output, "MOV R%d, [%d]\n", reg, mem);
            return reg;    
        }
        break;

        case OPERATOR_NODE:
        {
            if(node->op == '+')
            {
                int a = GenerateCode(node->left, output);
                int b = GenerateCode(node->right, output);
                fprintf(output, "ADD R%d, R%d\n", a, b);
                FreeRegister();
                return a;
            }
            else if(node->op == '-')
            {
                int a = GenerateCode(node->left, output);
                int b = GenerateCode(node->right, output);
                fprintf(output, "SUB R%d, R%d\n", a, b);
                FreeRegister();
                return a;
            }
            else if(node->op == '*')
            {
                int a = GenerateCode(node->left, output);
                int b = GenerateCode(node->right, output);
                fprintf(output, "MUL R%d, R%d\n", a, b);
                FreeRegister();
                return a;                
            } 
            else if(node->op == '/')
            {
                int a = GenerateCode(node->left, output);
                int b = GenerateCode(node->right, output);
                fprintf(output, "DIV R%d, R%d\n", a, b);
                FreeRegister();
                return a;
            }
            else if(node->op == '=')
            {
                int mem = 4096 + (node->left->varName[0] - 'a');
                int reg = GenerateCode(node->right, output);
                fprintf(output, "MOV [%d], R%d\n", mem, reg);
                FreeRegister();
            }             
        }
        break;
    }
}

int EvaluateAST(struct ASTNode *node)
{
    switch (node->nodeType)
    {
        case CONNECTOR_NODE:
        {
            EvaluateAST(node->left);
            EvaluateAST(node->right);
        }
        break;

        case WRITE_NODE:
        {
            printf("%d\n", EvaluateAST(node->left));
        }
        break;

        case READ_NODE:
        {
            int index = (node->left->varName[0] - 'a');
            scanf("%d", &virtualMem[index]);
        }
        break;

        case INTEGER_NODE:
        {
            return node->val;
        }
        break;

        case IDENTIFIER_NODE:
        {
            char var = node->varName[0];
            int index = (var - 'a');
            return virtualMem[index];
        }
        break;

        case OPERATOR_NODE:
        {
            if(node->op == '+')
            {
                return EvaluateAST(node->left) + EvaluateAST(node->right);
            }
            else if(node->op == '-')
            {
                return EvaluateAST(node->left) - EvaluateAST(node->right);
            }
            else if(node->op == '*')
            {
                return EvaluateAST(node->left) * EvaluateAST(node->right);           
            } 
            else if(node->op == '/')
            {
                return EvaluateAST(node->left) / EvaluateAST(node->right);
            }
            else if(node->op == '=')
            {
                int index = (node->left->varName[0] - 'a');
                virtualMem[index] = EvaluateAST(node->right);
            }             
        }
        break;
    }
}

void PrintAST(struct ASTNode* node, int indent)
{
    for(int n = 0; n < indent; n++)
    {
        printf("  ");
    }
    printf("+-");

    indent += 1;

    switch (node->nodeType)
    {
        case CONNECTOR_NODE:
        {
            printf("CONNECTOR\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;

        case WRITE_NODE:
        {
            printf("WRITE\n");
            PrintAST(node->left, indent);
            printf("\n");
        }
        break;

        case READ_NODE:
        {
            printf("READ\n");
            PrintAST(node->left, indent);
            printf("\n");
        }
        break;

        case INTEGER_NODE:
        {
            printf("INTEGER: '%d'", node->val);
        }
        break;

        case IDENTIFIER_NODE:
        {
            printf("IDENTIFIER: '%s'", node->varName);
        }
        break;

        case OPERATOR_NODE:
        {
            printf("OPERATOR: '%c'\n", node->op);
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
    }
}