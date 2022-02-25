#include "ast.h"
#include "symbol.h"

extern int yyerror(char const *);
extern int yylineno;

//keeps track of the free registers (0 = free, 1 = in use)
int registers[20] = {0};

//label counter for while and if statemnts codegen
unsigned int labelCount = 0;

// stack for keeping track which labels(L1, L2) is active currently
// used by break and continue statements
#define MAX_LABEL_STACK_SIZE 100
unsigned int labelStackPos = 0;
unsigned int labelStack[MAX_LABEL_STACK_SIZE];

extern struct GlobalSymbolTable globalSymbolTable;
extern struct GlobalSymbol *LookUpGlobalSymbolTable(struct GlobalSymbolTable table, char *name);

extern struct LocalSymbolTable localSymbolTable;
extern struct LocalSymbol *LookUpLocalSymbolTable(struct LocalSymbolTable table, char *name);

extern int returnType;
extern int localVariableCount;

struct ASTNode* CreateASTNode(int val, char *varName, int nodeType, int expType, struct ASTNode *left, struct ASTNode *right)
{
    struct ASTNode *node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    node->val = val;
    node->varName = varName;
    node->nodeType = nodeType;
    node->expType = expType;
    node->left = left;
    node->right = right;
    node->symbol = 0;
    node->argList = 0;
    node->argCount = 0;

    if(nodeType == IDENTIFIER_NODE)
    {
        struct GlobalSymbol *symbol = LookUpGlobalSymbolTable(globalSymbolTable, varName);
        if(symbol)
        {
            node->symbol = symbol;
            node->expType = symbol->type;
        }
    }
    
    return node;
}

void InsertASTNode(struct ASTNodeList *list, struct ASTNode node)
{
    if(list->size == 0)
    {
        list->size++;
        list->nodes = (struct ASTNode*)malloc(sizeof(struct ASTNode));        
    }
    else
    {
        list->size++;
        list->nodes = (struct ASTNode*)realloc(list->nodes, sizeof(struct ASTNode) * list->size);
    }

    list->nodes[list->size - 1] = node;
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
    
    return -1;
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

//generates read lib call which reads into mem addr 'mem'
void GenerateReadCodeMem(int mem, FILE *output)
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

//generates read lib call which reads into mem addr stored in 'reg'
void GenerateReadCodeReg(int reg, FILE *output)
{
    int a = GetRegister();
    
    fprintf(output, "\n");
    fprintf(output, "MOV R%d, \"Read\"\n", a);
    fprintf(output, "PUSH R%d\n", a);
    fprintf(output, "MOV R%d, -1\n", a);
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
            int reg = GenerateCode(node->left, output);
            GenerateReadCodeReg(reg, output);
            FreeRegister();
        }
        break;
        
        case INTEGER_NODE:
        {
            int reg = GetRegister();
            fprintf(output, "MOV R%d, %d\n", reg, node->val);
            return reg;
        }
        break;
        
        case STRING_NODE:
        {
            int reg = GetRegister();
            fprintf(output, "MOV R%d, \"%s\"\n", reg, node->strVal);
            return reg;
        }
        break;
        
        case IDENTIFIER_NODE:
        {
            struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(localSymbolTable, node->varName);

            if(localSymbol)
            {
                int reg = GetRegister();
                int tmp = GetRegister();
                fprintf(output, "MOV R%d, BP\n", tmp);
                fprintf(output, "ADD R%d, %d\n", tmp, localSymbol->binding);
                fprintf(output, "MOV R%d, [R%d]\n", reg, tmp);
                FreeRegister();
                return reg;
            }

            int mem = node->symbol->binding;
            int reg = GetRegister();
            fprintf(output, "MOV R%d, [%d]\n", reg, mem);
            return reg;
        }
        break;
        
        case ARRAY_NODE:
        {
            if(node->left->symbol->arrayDim == 1)
            {
                int reg = GetRegister();
                int reg_1 = GenerateCode(node->right, output);
                fprintf(output, "ADD R%d, %d\n", reg_1, node->left->symbol->binding);
                fprintf(output, "MOV R%d, [R%d]\n", reg, reg_1);
                FreeRegister();
                return reg;
            }
            else if(node->left->symbol->arrayDim == 2)
            {
                int reg = GetRegister();
                int r1 = GenerateCode(node->right->left, output);
                int r2 = GenerateCode(node->right->right, output);
                fprintf(output, "MUL R%d, %d\n", r1, node->left->symbol->colSize);
                fprintf(output, "ADD R%d, R%d\n", r2, r1);
                fprintf(output, "ADD R%d, %d\n", r2, node->left->symbol->binding);
                fprintf(output, "MOV R%d, [R%d]\n", reg, r2);
                FreeRegister();
                FreeRegister();
                return reg;
            }
        }
        
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
        
        case MOD_OP_NODE:
        {
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            fprintf(output, "MOD R%d, R%d\n", a, b);
            FreeRegister();
            return a;
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
        
        case EQ_OP_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {
                struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(localSymbolTable, node->left->varName);
                if(localSymbol)
                {
                    int tmp = GetRegister();
                    int reg = GenerateCode(node->right, output);
                    fprintf(output, "MOV R%d, BP\n", tmp);
                    fprintf(output, "ADD R%d, %d\n", tmp, localSymbol->binding);
                    fprintf(output, "MOV [R%d], R%d\n", tmp, reg);
                    FreeRegister();
                    FreeRegister();
                    return 0;
                }

                int mem = node->left->symbol->binding;
                int reg = GenerateCode(node->right, output);
                fprintf(output, "MOV [%d], R%d\n", mem, reg);
                FreeRegister();
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                if(node->left->left->symbol->arrayDim == 1)
                {
                    int reg = GenerateCode(node->left->right, output);
                    int tmp = GenerateCode(node->right, output);
                    fprintf(output, "ADD R%d, %d\n", reg, node->left->left->symbol->binding);
                    fprintf(output, "MOV [R%d], R%d\n", reg, tmp);
                    FreeRegister();
                    FreeRegister();
                }
                else if(node->left->left->symbol->arrayDim == 2)
                {
                    struct ASTNode *arrayNode = node->left;
                    int tmp = GenerateCode(node->right, output);
                    int r1 = GenerateCode(arrayNode->right->left, output);
                    int r2 = GenerateCode(arrayNode->right->right, output);
                    fprintf(output, "MUL R%d, %d\n", r1, arrayNode->left->symbol->colSize);
                    fprintf(output, "ADD R%d, R%d\n", r2, r1);
                    fprintf(output, "ADD R%d, %d\n", r2, arrayNode->left->symbol->binding);
                    fprintf(output, "MOV [R%d], R%d\n", r2, tmp);
                    FreeRegister();
                    FreeRegister();
                    FreeRegister();
                }
            }
            else if(node->left->nodeType == DEREF_NODE)
            {
                int reg = GenerateCode(node->left->left, output);
                int tmp = GenerateCode(node->right, output);
                fprintf(output, "MOV [R%d], R%d\n", reg, tmp);
                FreeRegister();
                FreeRegister();
            }
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
        
        case DEREF_NODE:
        {
            int reg = GetRegister();
            int tmp = GenerateCode(node->left, output);
            fprintf(output, "MOV R%d, [R%d]\n", reg, tmp);
            FreeRegister();
            return reg;
        }
        break;
        
        case ADDR_OF_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {
                int address = node->left->symbol->binding;
                int reg = GetRegister();
                fprintf(output, "MOV R%d, %d\n", reg, address);
                return reg;
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                int address = node->left->left->symbol->binding;
                int reg = GenerateCode(node->left->right, output);
                fprintf(output, "ADD R%d, %d\n", reg, address);
                return reg;
            }
        }
        break;

        case FUNCTION_CALL_NODE:
        {
            int tmpRegState[20];

            // pushing in use registers to stack
            for(int n = 0; n < 20; n++)
            {
                if(registers[n] == 1)
                {
                    fprintf(output, "PUSH R%d\n", n);
                }
            }

            if(node->argList)
            {
                for(int n = node->argCount - 1; n >= 0; n--)
                {
                    int reg = GenerateCode(&node->argList[n], output);
                    fprintf(output, "PUSH R%d\n", reg);
                    FreeRegister();
                }
            }

            // clearing register states
            for(int n = 0; n < 20; n++)
            {
                tmpRegState[n] = registers[n];
                registers[n] = 0;
            }

            // pushing space for return value;
            fprintf(output, "PUSH R0\n");
            fprintf(output, "CALL %s\n", node->left->varName);
            
            // restoring old registers states
            for(int n = 0; n < 20; n++)
            {
                registers[n] = tmpRegState[n];
            }

            // get return value
            int reg = GetRegister();
            fprintf(output, "POP R%d\n", reg);

            // poping off arguments from stack
            if(node->argList)
            {
                int reg = GetRegister();
                for(int n = 0; n < node->argCount; n++)
                {
                    fprintf(output, "POP R%d\n", reg);
                }
                FreeRegister();
            }

            // poping off in use registers
            for(int n = 19; n >= 0; n--)
            {
                if(tmpRegState[n] == 1)
                {
                    fprintf(output, "POP R%d\n", n);
                }
            }

            return reg;
        }
        break;

        case RETURN_NODE:
        {
            int reg = GenerateCode(node->left, output);
            int tmp = GetRegister();
            fprintf(output, "MOV R%d, BP\n", tmp);
            fprintf(output, "SUB R%d, 2\n", tmp);
            fprintf(output, "MOV [R%d], R%d\n", tmp, reg);

            if(localVariableCount > 0)
            {
                fprintf(output, "SUB SP, %d\n", localVariableCount);
            }
            
            fprintf(output, "POP BP\n");
            fprintf(output, "RET\n");
            FreeRegister();
            FreeRegister();
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
        }
        break;
        
        case READ_NODE:
        {
            printf("READ\n");
            PrintAST(node->left, indent);
        }
        break;
        
        case INTEGER_NODE:
        {
            printf("INTEGER: '%d'\n", node->val);
        }
        break;
        
        case STRING_NODE:
        {
            printf("STRING: '%s'\n", node->strVal);
        }
        break;
        
        case IDENTIFIER_NODE:
        {
            printf("IDENTIFIER: '%s'\n", node->varName);
        }
        break;
        
        case PLUS_OP_NODE:
        {
            printf("OPERATOR: '+'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case MINUS_OP_NODE:
        {
            printf("OPERATOR: '-'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case MUL_OP_NODE:
        {
            printf("OPERATOR: '*'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case DIV_OP_NODE:
        {
            printf("OPERATOR: '/'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case MOD_OP_NODE:
        {
            printf("OPERATOR: '%%'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case EQ_OP_NODE:
        {
            printf("OPERATOR: '='\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case LT_OP_NODE:
        {
            printf("OPERATOR: '<'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case LT_EQ_OP_NODE:
        {
            printf("OPERATOR: '<='\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case GT_OP_NODE:
        {
            printf("OPERATOR: '>'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case GT_EQ_OP_NODE:
        {
            printf("OPERATOR: '>='\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case EQUAL_EQ_OP_NODE:
        {
            printf("OPERATOR: '=='\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case NOT_EQ_OP_NODE:
        {
            printf("OPERATOR: '!='\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case IF_NODE:
        {
            printf("IF\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case WHILE_NODE:
        {
            printf("WHILE\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
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
            PrintAST(node->right, indent);
        }
        break;
        
        case ARRAY_NODE:
        {
            printf("ARRAY:\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case INDEX_NODE:
        {
            printf("INDEX:\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
        
        case DEREF_NODE:
        {
            printf("DEREF:\n");
            PrintAST(node->left, indent);
        }
        break;
        
        case ADDR_OF_NODE:
        {
            printf("ADDR_OF:\n");
            PrintAST(node->left, indent);
        }
        break;

        case FUNCTION_CALL_NODE:
        {
            printf("FUNCTION CALL:\n");
            PrintAST(node->left, indent);

            if(node->argList)
            {
                for(int n = 0; n < node->argCount; n++)
                {
                    PrintAST(&node->argList[n], indent);
                }
            }
        }
        break;

        case RETURN_NODE:
        {
            printf("RETURN:\n");
            PrintAST(node->left, indent);
        }
        break;
    }
}

int CheckSemantics(struct ASTNode* node)
{
    switch (node->nodeType)
    {
        case CONNECTOR_NODE:
        {
            CheckSemantics(node->left);
            CheckSemantics(node->right);
        }
        break;
        
        case WRITE_NODE:
        {   
            CheckSemantics(node->left);
        }
        break;
        
        case READ_NODE:
        {
            if(node->left->nodeType == ADDR_OF_NODE)
            {
                CheckSemantics(node->left);
            }
            else if(node->left->nodeType == IDENTIFIER_NODE)
            {
                if(node->left->symbol->type == POINTER_INT_TYPE || node->left->symbol->type == POINTER_STR_TYPE)
                {
                    CheckSemantics(node->left);
                }
                else
                {
                    printf("[ERROR] read library call expects an pointer variable!\n");
                    exit(1);
                }
            }
            else
            {
                printf("[ERROR] read library call expects an address !\n");
                exit(1);
            }
        }
        break;
        
        case INTEGER_NODE:
        {
            return INTEGER_TYPE;
        }
        break;
        
        case STRING_NODE:
        {
            return STRING_TYPE;
        }
        break;
        
        case IDENTIFIER_NODE:
        {
            struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(localSymbolTable, node->varName);
            
            if(localSymbol)
            {
                return localSymbol->type;
            }

            if(node->symbol)
            {
                if(node->symbol->functionLabel <= -1)
                {
                    return node->symbol->type;
                }
                else
                {
                    printf("[ERROR] '%s' is a function !\n", node->varName);
                    exit(1);        
                }
            }

            printf("[ERROR] use of undeclared variable -> '%s'!\n", node->varName);
            exit(1);
        }
        break;
        
        case PLUS_OP_NODE:
        case MINUS_OP_NODE:
        {
            int leftExprType = CheckSemantics(node->left);
            int rightExprType = CheckSemantics(node->right);
            
            if(leftExprType == POINTER_INT_TYPE || leftExprType == POINTER_STR_TYPE)
            {
                if(rightExprType == INTEGER_TYPE)
                {
                    return leftExprType;
                }
                else
                {
                    printf("[ERROR] invalid operands for binary operator!\n");
                    exit(1);
                }
            }
            
            if(rightExprType == POINTER_INT_TYPE || rightExprType == POINTER_STR_TYPE)
            {
                if(leftExprType == INTEGER_TYPE)
                {
                    return rightExprType;
                }
                else
                {
                    printf("[ERROR] invalid operands for binary operator!\n");
                    exit(1);
                }
            }
            
            if(leftExprType != rightExprType)
            {
                printf("[ERROR] type mismatch!\n");
                exit(1);
            }
            
            if(leftExprType != INTEGER_TYPE)
            {
                printf("[ERROR] left expression of arithmetic operator should be INTEGER type!\n");
                exit(1);
            }
            
            if(rightExprType != INTEGER_TYPE)
            {
                printf("[ERROR] right expression of arithmetic operator should be INTEGER type!\n");
                exit(1);
            }
            
            return node->expType;
        }
        break;
        
        case MUL_OP_NODE:
        case DIV_OP_NODE:
        case MOD_OP_NODE:
        {
            int leftExprType = CheckSemantics(node->left);
            int rightExprType = CheckSemantics(node->right);
            
            if(leftExprType != rightExprType)
            {
                printf("[ERROR] type mismatch!\n");
                exit(1);
            }
            
            if(leftExprType != INTEGER_TYPE)
            {
                printf("[ERROR] left expression of arithmetic operator should be INTEGER type!\n");
                exit(1);
            }
            
            if(rightExprType != INTEGER_TYPE)
            {
                printf("[ERROR] right expression of arithmetic operator should be INTEGER type!\n");
                exit(1);
            }
            
            return node->expType;
        }
        break;
        
        case EQ_OP_NODE:
        {
            int leftExprType = CheckSemantics(node->left);
            int rightExprType = CheckSemantics(node->right);
            
            // printf("left_type: %d, right_left: %d\n", leftExprType, rightExprType);
            
            if(leftExprType != rightExprType)
            {
                printf("[ERROR] type mismatch in assignment statement!\n");
                exit(1);
            }
        }
        break;
        
        case LT_OP_NODE:
        case LT_EQ_OP_NODE:
        case GT_OP_NODE:
        case GT_EQ_OP_NODE:
        case EQUAL_EQ_OP_NODE:
        case NOT_EQ_OP_NODE:
        {
            int leftExprType = CheckSemantics(node->left);
            int rightExprType = CheckSemantics(node->right);
            
            if(leftExprType != rightExprType)
            {
                printf("[ERROR] type mismatch!\n");
                exit(1);
            }
            
            if(leftExprType != INTEGER_TYPE)
            {
                printf("[ERROR] left expression of relational operator should be INTEGER type!\n");
                exit(1);
            }
            
            if(rightExprType != INTEGER_TYPE)
            {
                printf("[ERROR] right expression of relational operator should be INTEGER type!\n");
                exit(1);
            }
            
            return node->expType;
        }
        break;
        
        case IF_NODE:
        {
            int condExprType = CheckSemantics(node->left);
            
            if(condExprType != BOOLEAN_TYPE)
            {
                printf("[ERROR] conditional expression of 'if' statement should be BOOLEAN type!\n");
                exit(1);
            }
            
            CheckSemantics(node->right);
        }
        break;
        
        case WHILE_NODE:
        {
            int condExprType = CheckSemantics(node->left);
            
            if(condExprType != BOOLEAN_TYPE)
            {
                printf("[ERROR] conditional expression of 'while' statement should be BOOLEAN type!\n");
                exit(1);
            }
        }
        break;
        
        case BREAK_NODE:
        case CONTINUE_NODE:
        {
            return 0;
        }
        break;
        
        case BRANCH_NODE:
        {
            CheckSemantics(node->left);
            CheckSemantics(node->right);
        }
        break;
        
        case ARRAY_NODE:
        {
            int type = CheckSemantics(node->left);
            int indexType = CheckSemantics(node->right);
            
            if(node->left->symbol->arrayDim == 0)
            {
                printf("[ERROR] '%s' is not an array\n", node->left->varName);
                exit(1);
            }
            
            if(node->right->nodeType == INDEX_NODE)
            {
                if(node->left->symbol->arrayDim != 2)
                {
                    printf("[ERROR] '%s' is not a 2d array\n", node->left->varName);
                    exit(1);
                }
            }
            
            if(indexType != INTEGER_TYPE)
            {
                printf("[ERROR] array index should be INTEGER type\n");
                exit(1);
            }
            
            return type;
        }
        break;
        
        case INDEX_NODE:
        {
            int leftType = CheckSemantics(node->left);
            int rightType = CheckSemantics(node->right);
            
            if(leftType != INTEGER_TYPE || rightType != INTEGER_TYPE)
            {
                printf("[ERROR] array index should be INTEGER type\n");
                exit(1);
            }
            
            return INTEGER_TYPE;
        }
        break;
        
        case DEREF_NODE:
        {
            int type = CheckSemantics(node->left);
            
            if(type == POINTER_INT_TYPE)
            {
                return INTEGER_TYPE;
            }
            
            if(type == POINTER_STR_TYPE)
            {
                return STRING_TYPE;
            }
            
            printf("[ERROR] cannot dereference a non-pointer variable type\n");
            exit(1);
        }
        break;
        
        case ADDR_OF_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {
                if(node->left->symbol->type == INTEGER_TYPE)
                {
                    return POINTER_INT_TYPE;
                }
                
                if(node->left->symbol->type == STRING_TYPE)
                {
                    return POINTER_STR_TYPE;
                }
            }
            
            if(node->left->nodeType == ARRAY_NODE)
            {
                if(node->left->left->symbol->type == INTEGER_TYPE)
                {
                    return POINTER_INT_TYPE;
                }
                
                if(node->left->left->symbol->type == STRING_TYPE)
                {
                    return POINTER_STR_TYPE;
                }
            }
            
            printf("[ERROR] cannot get address of non-identifier\n");
            exit(1);
        }

        case FUNCTION_CALL_NODE:
        {
            bool symbolFound = false;
            struct GlobalSymbol symbol = {0};
            for(int n = 0; n < globalSymbolTable.size; n++)
            {
                symbol = globalSymbolTable.symbols[n];

                if(!strcmp(symbol.name, node->left->varName))
                {
                    if(symbol.functionLabel >= 0)
                    {
                        symbolFound = true;
                        break;
                    }        
                    else
                    {
                        printf("[ERROR] '%s' is not a function\n", node->left->varName);
                        exit(1);
                    }
                }
            }

            if(!symbolFound)
            {
                printf("[ERROR] call to undeclared function -> '%s'\n", node->left->varName);
                exit(1);
            }

            if(node->argList)
            {
                if(!symbol.paramList)
                {
                    printf("[ERROR] too many arguments to function -> '%s'\n", node->left->varName);
                    exit(1);
                }
            }

            if(symbol.paramList)
            {
                if(!node->argList)
                {
                    printf("[ERROR] too few arguments to function -> '%s'\n", node->left->varName);
                    exit(1);
                }
            }

            if(symbol.paramList->size < node->argCount)
            {
                printf("[ERROR] too many arguments to function -> '%s'\n", node->left->varName);
                exit(1);
            }

            if(symbol.paramList->size > node->argCount)
            {
                printf("[ERROR] too few arguments to function -> '%s'\n", node->left->varName);
                exit(1);
            }

            if(node->argList && symbol.paramList)
            {
                for(int n = 0; n < node->argCount; n++)
                {
                    int argType = CheckSemantics(&node->argList[n]);
                    int expectedType = symbol.paramList->params[n].type; 
                    if(argType != expectedType)
                    {
                        printf("[ERROR] incompatible type for argument %d of function -> '%s'\n", n, node->left->varName);
                        printf("[NOTE] expected '%s' but argument is of type '%s'\n", TypeToString(expectedType), TypeToString(argType));
                        exit(1);
                    }
                }
            }
            return symbol.type;
        }
        break;

        case RETURN_NODE:
        {
            int type = CheckSemantics(node->left);

            if(type != returnType)
            {
                printf("[ERROR] incompatible return type expected '%s' but found '%s'\n", TypeToString(returnType), TypeToString(type));
                exit(1);
            }
        }
        break;
    }
}