#include "ast.h"
#include "symbol.h"

extern int yyerror(char const *);

//keeps track of the registers state (0 = free, 1 = in use)
int registers[20] = {0};

//label counter for while and if statemnts codegen
unsigned int labelCount = 0;

// stack for keeping track which labels(L1, L2) is active currently
// used by break and continue statements
#define MAX_LABEL_STACK_SIZE 500
unsigned int labelStackPos = 0;
unsigned int labelStack[MAX_LABEL_STACK_SIZE];

extern struct GlobalSymbolTable globalSymbolTable;
extern struct GlobalSymbol *LookUpGlobalSymbolTable(struct GlobalSymbolTable table, char *name);

struct LocalSymbolTable localSymbolTable;
extern struct LocalSymbol *LookUpLocalSymbolTable(struct LocalSymbolTable table, char *name);

// return type of current active function(function definition for which semntics and codegen is being done)
int returnType;

bool entryPointFound = false;

char *NodeTypeToString(int nodeType)
{
    if(nodeType == CONNECTOR_NODE) return  "CONNECTOR_NODE";
    else if(nodeType == READ_NODE) return  "READ_NODE";
    else if(nodeType == WRITE_NODE) return  "WRITE_NODE";
    else if(nodeType == PLUS_OP_NODE) return  "PLUS_OP_NODE";
    else if(nodeType == MINUS_OP_NODE) return  "MINUS_OP_NODE";
    else if(nodeType == MUL_OP_NODE) return  "MUL_OP_NODE";
    else if(nodeType == DIV_OP_NODE) return  "DIV_OP_NODE";
    else if(nodeType == MOD_OP_NODE) return  "MOD_OP_NODE";
    else if(nodeType == LT_OP_NODE) return  "LT_OP_NODE";
    else if(nodeType == LT_EQ_OP_NODE) return  "LT_EQ_OP_NODE";
    else if(nodeType == GT_OP_NODE) return  "GT_OP_NODE";
    else if(nodeType == GT_EQ_OP_NODE) return  "GT_EQ_OP_NODE";
    else if(nodeType == EQUAL_EQ_OP_NODE) return  "EQUAL_EQ_OP_NODE";
    else if(nodeType == NOT_EQ_OP_NODE) return  "NOT_EQ_OP_NODE,";
    else if(nodeType == AND_NODE) return  "AND_NODE";
    else if(nodeType == OR_NODE) return  "OR_NODE";
    else if(nodeType == EQ_OP_NODE) return  "EQ_OP_NODE";
    else if(nodeType == IF_NODE) return  "IF_NODE";
    else if(nodeType == BRANCH_NODE) return  "BRANCH_NODE";
    else if(nodeType == WHILE_NODE) return  "WHILE_NODE";
    else if(nodeType == BREAK_NODE) return  "BREAK_NODE";
    else if(nodeType == CONTINUE_NODE) return  "CONTINUE_NODE";
    else if(nodeType == IDENTIFIER_NODE) return  "IDENTIFIER_NODE";
    else if(nodeType == INTEGER_NODE) return  "INTEGER_NODE";
    else if(nodeType == STRING_NODE) return  "STRING_NODE";
    else if(nodeType == ARRAY_NODE) return  "ARRAY_NODE";
    else if(nodeType == INDEX_NODE) return  "INDEX_NODE";
    else if(nodeType == DEREF_NODE) return  "DEREF_NODE";
    else if(nodeType == ADDR_OF_NODE) return  "ADDR_OF_NODE";
    else if(nodeType == FUNCTION_CALL_NODE) return  "FUNCTION_CALL_NODE";
    else if(nodeType == RETURN_NODE) return  "RETURN_NODE";

    return "UNKNOWN_NODE_TYPE";
}

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
    
    node->localSymbolTable = 0;
    node->paramList = 0;
    node->returnType = 0;
    
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

    printf("error: all registers used!!\n");
    exit(1);

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

void PushLabel(int label)
{
    labelStack[labelStackPos++] = label;
}

void PopLabel()
{
    labelStackPos--;
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
    // printf("%s\n", NodeTypeToString(node->nodeType));

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

        case AND_NODE:
        {
            int L1 = GetLabel();
            int L2 = GetLabel();
            int reg = GetRegister();
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            int tmp = GetRegister();
            fprintf(output, "MOV R%d, R%d\n", tmp, a);
            fprintf(output, "GT R%d, R%d\n", a, b);
            fprintf(output, "JNZ R%d, L%d\n", a, L1);
            fprintf(output, "LT R%d, R%d\n", tmp, b);
            fprintf(output, "JNZ R%d, L%d\n", tmp, L1);
            fprintf(output, "JZ R%d, L%d\n", b, L1);
            fprintf(output, "MOV R%d, 1\n", reg);
            fprintf(output, "JMP L%d\n", L2);
            fprintf(output, "L%d:\n", L1);
            fprintf(output, "MOV R%d, 0\n", reg);
            fprintf(output, "L%d:\n", L2);
            FreeRegister();
            FreeRegister();
            FreeRegister();
            return reg;
        }
        break;
        
        case OR_NODE:
        {
            int L1 = GetLabel();
            int L2 = GetLabel();
            int reg = GetRegister();
            int a = GenerateCode(node->left, output);
            int b = GenerateCode(node->right, output);
            int tmp = GetRegister();
            fprintf(output, "MOV R%d, R%d\n", tmp, a);
            fprintf(output, "GT R%d, R%d\n", a, b);
            fprintf(output, "JNZ R%d, L%d\n", a, L1);
            fprintf(output, "LT R%d, R%d\n", tmp, b);
            fprintf(output, "JNZ R%d, L%d\n", tmp, L1);
            fprintf(output, "JNZ R%d, L%d\n", b, L1);
            fprintf(output, "MOV R%d, 0\n", reg);
            fprintf(output, "JMP L%d\n", L2);
            fprintf(output, "L%d:\n", L1);
            fprintf(output, "MOV R%d, 1\n", reg);
            fprintf(output, "L%d:\n", L2);
            FreeRegister();
            FreeRegister();
            FreeRegister();
            return reg;
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
            FreeRegister();
            
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
        }
        break;
        
        case WHILE_NODE:
        {
            int L1 = GetLabel();
            int L2 = GetLabel();
            PushLabel(L1);
            PushLabel(L2);
            
            fprintf(output, "L%d:\n", L1);
            
            int a = GenerateCode(node->left, output);
            fprintf(output, "JZ R%d, L%d\n", a, L2);
            FreeRegister();
            
            GenerateCode(node->right, output);
            fprintf(output, "JMP L%d\n", L1);
            fprintf(output, "L%d:\n", L2);
            
            PopLabel();
            PopLabel();
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
                struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(localSymbolTable, node->left->varName);
                if(localSymbol)
                {
                    int reg = GetRegister();
                    fprintf(output, "MOV R%d, BP\n", reg);
                    fprintf(output, "ADD R%d, %d\n", reg, localSymbol->binding);
                    return reg;
                }

                int reg = GetRegister();
                int address = node->left->symbol->binding;
                fprintf(output, "MOV R%d, %d\n", reg, address);
                return reg;
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                if(node->left->left->symbol->arrayDim == 1)
                {
                    int address = node->left->left->symbol->binding;
                    int reg = GenerateCode(node->left->right, output);
                    fprintf(output, "ADD R%d, %d\n", reg, address);
                    return reg;
                }
                else if(node->left->left->symbol->arrayDim == 2)
                {
                    struct ASTNode *arrayNode = node->left;
                    int r1 = GenerateCode(arrayNode->right->left, output);
                    int r2 = GenerateCode(arrayNode->right->right, output);
                    fprintf(output, "MUL R%d, %d\n", r1, arrayNode->left->symbol->colSize);
                    fprintf(output, "ADD R%d, R%d\n", r2, r1);
                    fprintf(output, "ADD R%d, %d\n", r2, arrayNode->left->symbol->binding);
                    FreeRegister();
                    return r2;
                }
            }
        }
        break;

        case FUNCTION_CALL_NODE:
        {
            int tmpRegState[20] = {0};

            // pushing in-use registers to stack
            for(int n = 0; n < 20; n++)
            {
                if(registers[n] == 1)
                {
                    fprintf(output, "PUSH R%d\n", n);
                }
            }

            // pushing function arguments
            if(node->argList)
            {
                for(int n = node->argCount - 1; n >= 0; n--)
                {
                    int tmp = GenerateCode(&node->argList[n], output);
                    fprintf(output, "PUSH R%d\n", tmp);
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
                int tmp = GetRegister();
                for(int n = 0; n < node->argCount; n++)
                {
                    fprintf(output, "POP R%d\n", tmp);
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
            fprintf(output, "MOV SP, BP\n");
            fprintf(output, "POP BP\n");
            fprintf(output, "RET\n");
            FreeRegister();
            FreeRegister();
        }
        break;

        case FUNCTION_DEF_NODE:
        {
            fprintf(output, "#%s\n", node->varName);
            fprintf(output, "PUSH BP\n");
            fprintf(output, "MOV BP, SP\n");

            // allocating space for local variables in the stack
            if(node->localSymbolTable)
            {
                localSymbolTable = *(node->localSymbolTable);
                int localVarCount = 0;
                for(int n  = 0; n < localSymbolTable.size; n++)
                {
                    if(localSymbolTable.symbols[n].binding >= 1) localVarCount++;
                }
                fprintf(output, "ADD SP, %d\n", localVarCount);
            }

            //generating code for function
            if(node->left)
            {
                GenerateCode(node->left, output);
            }

            // adding return statement in case the user forget to put a return 
            fprintf(output, "MOV SP, BP\n");
            fprintf(output, "POP BP\n");
            fprintf(output, "RET\n");
        }
        break;
    }

    return -1;
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
            printf("'int': '%d'\n", node->val);
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
        
        case AND_NODE:
        {
            printf("OPERATOR: 'and'\n");
            PrintAST(node->left, indent);
            PrintAST(node->right, indent);
        }
        break;
 
        case OR_NODE:
        {
            printf("OPERATOR: 'or'\n");
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

        case FUNCTION_DEF_NODE:
        {
            printf("FUNCTION DEF: %s %s( ", TypeToString(node->returnType), node->varName);
            if(node->paramList)
            {
                for(int n = 0; n < node->paramList->size; n++)
                {
                    printf("%s %s, ", TypeToString(node->paramList->params[n].type), node->paramList->params[n].name);
                }
            }
            printf(")\n");

            PrintAST(node->left, indent);
        };
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
                int type = CheckSemantics(node->left);
                if(type != POINTER_INT_TYPE || type != POINTER_STR_TYPE)
                {
                    printf("error: read library call expects an pointer variable!\n");
                    exit(1);
                }
            }
            else
            {
                printf("error: read library call expects an address !\n");
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
                    printf("error: '%s' is a function !\n", node->varName);
                    exit(1);        
                }
            }

            printf("error: use of undeclared variable -> '%s'!\n", node->varName);
            exit(1);
        }
        break;
        
        case ARRAY_NODE:
        {
            int type = CheckSemantics(node->left);
            int indexType = CheckSemantics(node->right);
            
            if(node->left->symbol->arrayDim == 0)
            {
                printf("error: '%s' is not an array\n", node->left->varName);
                exit(1);
            }
            
            if(node->right->nodeType == INDEX_NODE)
            {
                if(node->left->symbol->arrayDim != 2)
                {
                    printf("error: '%s' is not a 2d array\n", node->left->varName);
                    exit(1);
                }
            }
            
            if(indexType != INTEGER_TYPE)
            {
                printf("error: array index should be 'int' type\n");
                exit(1);
            }
            
            return type;
        }
        break;
        
        case PLUS_OP_NODE:
        case MINUS_OP_NODE:
        {
            int leftExprType = CheckSemantics(node->left);
            int rightExprType = CheckSemantics(node->right);
            
            // TODO : separate checks for str ptr and int ptr
            if(leftExprType == POINTER_INT_TYPE || leftExprType == POINTER_STR_TYPE)
            {
                if(rightExprType == INTEGER_TYPE)
                {
                    return leftExprType;
                }
                else
                {
                    printf("error: invalid operands for binary operator!\n");
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
                    printf("error: invalid operands for binary operator!\n");
                    exit(1);
                }
            }
            
            if(leftExprType != INTEGER_TYPE)
            {
                printf("error: left expression of arithmetic operator should be 'int' type!\n");
                exit(1);
            }
            
            if(rightExprType != INTEGER_TYPE)
            {
                printf("error: right expression of arithmetic operator should be 'int' type!\n");
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
            
            if(leftExprType != INTEGER_TYPE)
            {
                printf("error: left expression of arithmetic operator should be 'int' type!\n");
                exit(1);
            }
            
            if(rightExprType != INTEGER_TYPE)
            {
                printf("error: right expression of arithmetic operator should be 'int' type!\n");
                exit(1);
            }
            
            return node->expType;
        }
        break;
        
        case EQ_OP_NODE:
        {
            int leftExprType = CheckSemantics(node->left);
            int rightExprType = CheckSemantics(node->right);
            
            if(leftExprType != rightExprType)
            {
                printf("error: type mismatch in assignment statement!\n");
                printf("[NOTE] lhs type: '%s'\n", TypeToString(leftExprType));
                printf("[NOTE] rhs type: '%s'\n", TypeToString(rightExprType));
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
            
            if(leftExprType != INTEGER_TYPE)
            {
                printf("error: left expression of relational operator should be 'int' type!\n");
                exit(1);
            }
            
            if(rightExprType != INTEGER_TYPE)
            {
                printf("error: right expression of relational operator should be 'int' type!\n");
                exit(1);
            }
            return node->expType;
        }
        break;

        case AND_NODE:
        case OR_NODE:
        {
            int leftExprType = CheckSemantics(node->left);
            int rightExprType = CheckSemantics(node->right);
            
            if(leftExprType != BOOLEAN_TYPE)
            {
                printf("error: left expression of boolean operator should be 'bool' type!\n");
                exit(1);
            }
            
            if(rightExprType != BOOLEAN_TYPE)
            {
                printf("error: right expression of boolean operator should be 'bool' type!\n");
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
                printf("error: conditional expression of 'if' statement should be 'bool' type!\n");
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
                printf("error: conditional expression of 'while' statement should be 'bool' type!\n");
                exit(1);
            }

            CheckSemantics(node->right);
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
        
        case INDEX_NODE:
        {
            int leftType = CheckSemantics(node->left);
            int rightType = CheckSemantics(node->right);
            
            if(leftType != INTEGER_TYPE || rightType != INTEGER_TYPE)
            {
                printf("error: array index should be 'int'\n");
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
            
            printf("error: cannot dereference a non-pointer variable -> '%s' !\n", node->left->varName);
            exit(1);
        }
        break;
        
        case ADDR_OF_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE || node->left->nodeType == ARRAY_NODE)
            {
                int type = CheckSemantics(node->left);

                if(type == INTEGER_TYPE)
                {
                    return POINTER_INT_TYPE;
                }

                if(type == STRING_TYPE)
                {
                    return POINTER_STR_TYPE;
                }
            }
            else
            {
                printf("error: cannot get address of non-identifier\n");
                exit(1);
            }        
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
                        printf("error: '%s' is not a function\n", node->left->varName);
                        exit(1);
                    }
                }
            }
            
            if(!symbolFound)
            {
                printf("error: call to undeclared function -> '%s'\n", node->left->varName);
                exit(1);
            }

            if(node->argList)
            {
                if(!symbol.paramList)
                {
                    printf("error: too many arguments to function -> '%s'\n", node->left->varName);
                    exit(1);
                }
            }

            if(symbol.paramList)
            {
                if(!node->argList)
                {
                    printf("error: too few arguments to function -> '%s'\n", node->left->varName);
                    exit(1);
                }

                if(symbol.paramList->size < node->argCount)
                {
                    printf("error: too many arguments to function -> '%s'\n", node->left->varName);
                    exit(1);
                }

                if(symbol.paramList->size > node->argCount)
                {
                    printf("error: too few arguments to function -> '%s'\n", node->left->varName);
                    exit(1);
                }
            }

            if(symbol.paramList && node->argList)
            {
                for(int n = 0; n < node->argCount; n++)
                {
                    int argType = CheckSemantics(&node->argList[n]);
                    int expectedType = symbol.paramList->params[n].type; 
                    if(argType != expectedType)
                    {
                        printf("error: incompatible type for argument %d of function -> '%s'\n", n, node->left->varName);
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
                printf("error: incompatible return type expected '%s' but found '%s'\n", TypeToString(returnType), TypeToString(type));
                exit(1);
            }
        }
        break;

        case FUNCTION_DEF_NODE:
        {
            if(!strcmp("main", node->varName))
            {
                if(entryPointFound)
                {
                    printf("error: redefinition of 'int main()' !\n");
                    exit(1);
                }

                if(node->returnType != INTEGER_TYPE)
                {
                    printf("error: function 'main' must return 'int' !\n");
                    exit(1);
                }

                if(node->paramList)
                {
                    printf("error: function 'main' takes 0 parameter but found %d parameters!\n", node->paramList->size);
                    exit(1);
                }

                entryPointFound = true;
                returnType = INTEGER_TYPE;
            }
            else
            {
                struct GlobalSymbol *symbol = LookUpGlobalSymbolTable(globalSymbolTable, node->varName);

                if(!symbol)
                {
                    printf("error: undeclared function -> '%s' !\n", node->varName);
                    exit(1);
                }

                if(symbol->functionLabel <= -1)
                {
                    printf("error:  undeclared function -> '%s' !\n", node->varName);
                    exit(1);
                }

                if(symbol->type != node->returnType)
                {
                    printf("error: return type conflict in definition and declaration of function -> '%s' !\n", node->varName);
                    exit(1);
                }

                if(symbol->paramList && !node->paramList)
                {
                    printf("error: function ->'%s' has 0 parameter in its definition!\n", node->varName);
                    exit(1);
                }

                if(!symbol->paramList && node->paramList)
                {
                    printf("error: function ->'%s' has 0 parameter in its declaration!\n", node->varName);
                    exit(1);
                }

                if(symbol->paramList && node->paramList)
                {
                    if(symbol->paramList->size != node->paramList->size)
                    {
                        printf("error: parameter count different in declaration and definition of function -> '%s' !\n", node->varName);
                        exit(1);
                    }

                    for(int n = 0; n < node->paramList->size; n++)
                    {
                        if(symbol->paramList->params[n].type != node->paramList->params[n].type)
                        {
                            printf("error: parameter %d type conflict in declaration and definition of function -> '%s' !\n", n, node->varName);
                            exit(1);
                        }

                        if (strcmp(symbol->paramList->params[n].name, node->paramList->params[n].name))
                        {
                            printf("error: parameter %d name conflict in declaration and definition of function -> '%s' !\n", n, node->varName);
                            exit(1);
                        }
                    }
                }
            }

            returnType = node->returnType;

            localSymbolTable.size = 0;
            if(node->localSymbolTable)
            {
                localSymbolTable = *(node->localSymbolTable);
            }

            if(node->left)
            {
                CheckSemantics(node->left);
            }
        }
        break;
    }

    return 0;
}