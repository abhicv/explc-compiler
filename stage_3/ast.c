#include "ast.h"

extern int yyerror(char const *);
extern int yylineno;

//keeps track of the free registers (0 = free, 1 = in use)
int registers[20] = {0};

//used by the AST evlaution function as static memory for variables a to z
int virtualMem[26] = {0};

//label counter for while and if statemnts codegen
unsigned int labelCount = 0;

#define MAX_LABEL_STACK_SIZE 100
unsigned int labelStackPos = 0;
unsigned int labelStack[MAX_LABEL_STACK_SIZE];

struct ASTNode* CreateASTNode(int val, char *varName, int nodeType, int expType, struct ASTNode *left, struct ASTNode *right)
{
    struct ASTNode *node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    node->val = val;
    node->varName = varName;
    node->nodeType = nodeType;
    
    //checking for semantic error
    if(IS_OPERATOR_NODE(nodeType))
    {   
        if(right->expType != INTEGER_TYPE)
        {
            printf("[ERROR] type mismatch!\n");
            exit(1);            
        }
    }
    else if(nodeType == EQ_OP_NODE)
    {
        if(right->expType != INTEGER_TYPE)
        {
            printf("[ERROR] right side of '=' is not of type integer !\n");
            exit(1); 
        }
    }
    else if(nodeType == IF_NODE)
    {
        if(left->expType != BOOLEAN_TYPE)
        {
            printf("[ERROR] expression inside 'if' should evaluate into a boolean type !\n");
            exit(1);
        }
    }
    else if(nodeType == WHILE_NODE)
    {
        if(left->expType != BOOLEAN_TYPE)
        {
            printf("[ERROR] expression inside 'while' should evaluate into a boolean type !\n");
            exit(1);
        }
    }
    
    node->expType = expType;
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

int GetLabel()
{
    return labelCount++;
}

void PushLabels(int L1, int L2)
{
    labelStack[labelStackPos++] = L1;
    labelStack[labelStackPos++] = L2;
}

void PopLabels()
{
    labelStackPos -= 2;
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
        
        case PLUS_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "ADD R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case MINUS_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "SUB R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case MUL_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "MUL R%d, R%d\n", a, b);
            FreeRegister();
            return a;                
        }
        break;
        
        case DIV_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "DIV R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case EQ_OP_NODE:
        {
            int mem = 4096 + (node->left->varName[0] - 'a');
            int reg = GenerateCode(node->right, output);
            fprintf(output, "MOV [%d], R%d\n", mem, reg);
            FreeRegister();
        }             
        break;
        
        case LT_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "LT R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case LT_EQ_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "LE R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case GT_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "GT R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case GT_EQ_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "GE R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case EQUAL_EQ_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "EQ R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case NOT_EQ_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "NE R%d, R%d\n", a, b);
            FreeRegister();
            return a;
        }
        break;
        
        case IF_NODE:
        {
            int L1 = GetLabel();
            
            int a = GenerateCode(node->left, output);
            fprintf(output, "JZ R%d, L%d\n", a, L1);
            if(node->right->nodeType == BRANCH_NODE)
            {
                GenerateCode(node->right->left, output);
                
                int L2 = GetLabel();
                fprintf(output, "JMP L%d\n", L2);
                
                fprintf(output, "L%d:\n", L1);
                
                GenerateCode(node->right->right, output);
                
                fprintf(output, "L%d:\n", L2);
            }
            else
            {
                GenerateCode(node->right, output);
                fprintf(output, "L%d:\n", L1);
            }
            
            FreeRegister();
        }
        break;
        
        case WHILE_NODE:
        {
            int L1 = GetLabel();
            int L2 = GetLabel();
            PushLabels(L1, L2);
            
            fprintf(output, "L%d:\n", L1);
            
            int a = GenerateCode(node->left, output);
            
            fprintf(output, "JZ R%d, L%d\n", a, L2);
            GenerateCode(node->right, output);
            fprintf(output, "JMP L%d\n", L1);
            fprintf(output, "L%d:\n", L2);
            
            FreeRegister();
            
            PopLabels();
        }
        break;
        
        case BREAK_NODE:
        {
            if(labelStackPos >= 2)
            {
                fprintf(output, "JMP L%d\n", labelStack[labelStackPos-1]);
            }
        }
        break;
        
        case CONTINUE_NODE:
        {
            if(labelStackPos >= 2)
            {
                fprintf(output, "JMP L%d\n", labelStack[labelStackPos-2]);
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
        
        case PLUS_OP_NODE:
        {
            return EvaluateAST(node->left) + EvaluateAST(node->right);
        }
        break;
        
        case MINUS_OP_NODE:
        {
            return EvaluateAST(node->left) - EvaluateAST(node->right);
        }
        break;
        
        case MUL_OP_NODE:
        {
            return EvaluateAST(node->left) * EvaluateAST(node->right);           
        } 
        break;
        
        case DIV_OP_NODE:
        {
            return EvaluateAST(node->left) / EvaluateAST(node->right);
        }
        break;
        
        case LT_OP_NODE:
        {
            return (EvaluateAST(node->left) < EvaluateAST(node->right)) ? 1 : 0;
        }
        break;
        
        case LT_EQ_OP_NODE:
        {
            return (EvaluateAST(node->left) <= EvaluateAST(node->right)) ? 1 : 0;
        }
        break;
        
        case GT_OP_NODE:
        {
            return (EvaluateAST(node->left) > EvaluateAST(node->right)) ? 1 : 0;
        }
        break;
        
        case GT_EQ_OP_NODE:
        {
            return (EvaluateAST(node->left) >= EvaluateAST(node->right)) ? 1 : 0;
        }
        break;
        
        case EQUAL_EQ_OP_NODE:
        {
            return (EvaluateAST(node->left) == EvaluateAST(node->right)) ? 1 : 0;
        }
        break;
        
        case NOT_EQ_OP_NODE:
        {
            return (EvaluateAST(node->left) != EvaluateAST(node->right)) ? 1 : 0;
        }
        break;
        
        case EQ_OP_NODE:
        {
            int index = (node->left->varName[0] - 'a');
            virtualMem[index] = EvaluateAST(node->right);
        }             
        break;
        
        case IF_NODE:
        {
            if(EvaluateAST(node->left) == 1)
            {
                if(node->right->nodeType == BRANCH_NODE)
                {
                    return EvaluateAST(node->right->left);
                }
                else
                {
                    return EvaluateAST(node->right);
                }
            }
            else
            {
                if(node->right->nodeType == BRANCH_NODE)
                {
                    return EvaluateAST(node->right->right);
                }
            }
        }
        break;
        
        case WHILE_NODE:
        {
            while(EvaluateAST(node->left) == 1)
            {
                EvaluateAST(node->right);
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
        
        case PLUS_OP_NODE:
        {
            printf("OPERATOR: '+'\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case MINUS_OP_NODE:
        {
            printf("OPERATOR: '-'\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case MUL_OP_NODE:
        {
            printf("OPERATOR: '*'\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case DIV_OP_NODE:
        {
            printf("OPERATOR: '/'\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case EQ_OP_NODE:
        {
            printf("OPERATOR: '='\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case LT_OP_NODE:
        {
            printf("OPERATOR: '<'\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case LT_EQ_OP_NODE:
        {
            printf("OPERATOR: '<='\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case GT_OP_NODE:
        {
            printf("OPERATOR: '>'\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case GT_EQ_OP_NODE:
        {
            printf("OPERATOR: '>='\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case EQUAL_EQ_OP_NODE:
        {
            printf("OPERATOR: '=='\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case NOT_EQ_OP_NODE:
        {
            printf("OPERATOR: '!='\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case IF_NODE:
        {
            printf("IF\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case WHILE_NODE:
        {
            printf("WHILE\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
        
        case BREAK_NODE:
        {
            printf("BREAK\n");
        }
        break;
        
        case CONTINUE_NODE:
        {
            printf("CONTINUE\n");
        }
        break;
        
        case BRANCH_NODE:
        {
            printf("BRANCH\n");
            PrintAST(node->left, indent);
            printf("\n");
            PrintAST(node->right, indent);
            printf("\n");
        }
        break;
    }
}