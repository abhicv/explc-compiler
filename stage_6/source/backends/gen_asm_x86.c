//backend to generate nasm x86 32 bit assembly

#include "../ast.h"
#include "../symbol.h"

extern bool entryPointFound;
extern struct GlobalSymbolTable globalSymbolTable;
struct LocalSymbolTable localSymbolTable;

typedef struct StringLiteral
{
    char *str;
    unsigned int size;
} StringLiteral;

#define MAX_STR_LITERAL 1024
StringLiteral stringLiteralTable[MAX_STR_LITERAL];
unsigned int stringLiteralCount = 0;

unsigned int labelCounter = 0;

enum Register
{
    EAX,
    EBX,
    ECX,
    EDX,
    ESI,
    EDI,
    ESP,
    EBP,
    REGISTER_COUNT
};

char *regName[REGISTER_COUNT] = 
{
    "eax\0",
    "ebx\0",
    "ecx\0",
    "edx\0",
    "esi\0",
    "edi\0",
    "esp\0",
    "ebp\0",
};

int regUseFlags[REGISTER_COUNT] = {0};

int Getx86Register()
{
    for(int n = 0; n < REGISTER_COUNT - 2; n++)
    {
        if(regUseFlags[n] == 0)
        {
            regUseFlags[n] = 1;
            return n;
        }
    }

    return -1;
}

void Freex86Register()
{
    for(int n = REGISTER_COUNT - 3; n >= 0; n--)
    {
        if(regUseFlags[n] == 1)
        {
            regUseFlags[n] = 0;
            return;
        }
    }
}

//allocates memory in the bss section for variables
void AllocateStaticMemory(struct GlobalSymbolTable table, FILE *output)
{
    for(int n = 0; n < table.size; n++)
    {
        if(table.symbols[n].functionLabel <= -1)
        {
            fprintf(output, "%s: resd %d\n", table.symbols[n].name, table.symbols[n].size);
        }
    }
}

void PrintStringTable()
{
    for(int n = 0; n < stringLiteralCount; n++)
    {
        printf("[%u] -> '%s', len: %u\n", n, stringLiteralTable[n].str, stringLiteralTable[n].size);
    }
}

void CreateDataSegment(FILE *output)
{
    fprintf(output, "\nsection .data\n");
    for(int n = 0; n < stringLiteralCount; n++)
    {
        fprintf(output, "str_%d: db ", n);
        unsigned int len = strlen(stringLiteralTable[n].str);
        char *str = stringLiteralTable[n].str;
        for(int i = 0; i < len; i++)
        {
            if(str[i] == '\\' && i <= len - 2 && str[i+1] == 'n')
            {
                fprintf(output, "0xa, ");
                i += 1;
            }
            else
            {
                fprintf(output, "0x%x, ", (int)str[i]);
            }
        }
        fprintf(output, "0x0\n");
    }
}

void GenerateJumpInstruction(FILE *output, int type, int label)
{
    if(type == LT_OP_NODE)
    {
        fprintf(output, "jge L%d\n", label);
    }
    else if(type == LT_EQ_OP_NODE)
    {
        fprintf(output, "jg L%d\n", label);
    }
    else if(type == GT_OP_NODE)
    {
        fprintf(output, "jle L%d\n", label);
    }
    else if(type == GT_EQ_OP_NODE)
    {
        fprintf(output, "jl L%d\n", label);
    }
    else if(type == EQUAL_EQ_OP_NODE)
    {
        fprintf(output, "jne L%d\n", label);
    }
    else if(type == NOT_EQ_OP_NODE)
    {
        fprintf(output, "je L%d\n", label);
    }
}

int GenerateNasmAssembly32(struct ASTNode *node, FILE *output)
{
    switch (node->nodeType)
    {
        case CONNECTOR_NODE:
        {
            GenerateNasmAssembly32(node->left, output);
            GenerateNasmAssembly32(node->right, output);
        }
        break;
        
        case WRITE_NODE:
        {
            
        }
        break;
        
        case READ_NODE:
        {
            
        }
        break;
        
        case INTEGER_NODE:
        {
            int reg = Getx86Register();
            fprintf(output, "mov %s, %d\n", regName[reg], node->val);
            return reg;
        }
        break;
        
        case STRING_NODE:
        {
            StringLiteral strLiteral = {0};
            strLiteral.str = node->strVal;
            strLiteral.size = strlen(node->strVal);     

            assert(stringLiteralCount < MAX_STR_LITERAL);
            stringLiteralTable[stringLiteralCount] = strLiteral;

            int reg = Getx86Register();
            fprintf(output, "lea %s, [str_%d]\n", regName[reg], stringLiteralCount++);
            return reg;
        }
        break;

        case IDENTIFIER_NODE:
        {
            struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(localSymbolTable, node->varName);
            if(localSymbol)
            {
                int reg = Getx86Register();
                int offset = localSymbol->binding < 0 ? localSymbol->binding + 1 : localSymbol->binding;
                fprintf(output, "mov %s, dword [ebp-%d]\n", regName[reg], offset * 4);
                return reg;
            }

            int reg = Getx86Register();
            fprintf(output, "mov %s, dword [%s]\n", regName[reg], node->varName);
            return reg;
        }
        break;
        
        case ARRAY_NODE:
        {
            if(node->left->symbol->arrayDim == 1)
            {
                int reg = Getx86Register();
                int tmp = GenerateNasmAssembly32(node->right, output);
                fprintf(output, "lea %s, [%s + %s * 4]\n", regName[tmp], node->left->varName, regName[tmp]);
                fprintf(output, "mov %s, dword [%s]\n", regName[reg], regName[tmp]);
                Freex86Register();
                return reg;
            }
            else if(node->left->symbol->arrayDim == 2)
            {
                int reg = Getx86Register();
                int row = GenerateNasmAssembly32(node->right->left, output);
                int col = GenerateNasmAssembly32(node->right->right, output);
                fprintf(output, "imul %s, %s, %d\n", regName[row], regName[row], node->left->symbol->colSize);
                fprintf(output, "add %s, %s\n", regName[row], regName[col]);
                fprintf(output, "lea %s, [%s + %s * 4]\n", regName[row], node->left->varName, regName[row]);
                fprintf(output, "mov %s, dword [%s]\n", regName[reg], regName[row]);
                Freex86Register();
                Freex86Register();
                return reg;
            }
        }

        case PLUS_OP_NODE:
        {
            int a = GenerateNasmAssembly32(node->left, output);
            int b = GenerateNasmAssembly32(node->right, output);
            fprintf(output, "add %s, %s\n", regName[a], regName[b]);
            Freex86Register();
            return a;
        }
        break;
        
        case MINUS_OP_NODE:
        {
            int a = GenerateNasmAssembly32(node->left, output);
            int b = GenerateNasmAssembly32(node->right, output);
            fprintf(output, "sub %s, %s\n", regName[a], regName[b]);
            Freex86Register();
            return a;
        }
        break;
        
        case MUL_OP_NODE:
        {
            int a = GenerateNasmAssembly32(node->left, output);
            int b = GenerateNasmAssembly32(node->right, output);
            fprintf(output, "imul %s, %s\n", regName[a], regName[b]);
            Freex86Register();
            return a;
        }
        break;
        
        case DIV_OP_NODE:
        {
            // TODO: fix 
            int a = GenerateNasmAssembly32(node->left, output);
            int b = GenerateNasmAssembly32(node->right, output);

            if(a != EAX)
            {
                fprintf(output, "push eax\n");
            }

            fprintf(output, "push ecx\n");
            fprintf(output, "push edx\n");
            fprintf(output, "mov ecx, %s\n", regName[b]);
            fprintf(output, "mov eax, %s\n", regName[a]);
            fprintf(output, "mov edx, 0\n");
            fprintf(output, "idiv ecx\n");
            fprintf(output, "mov %s, eax\n", regName[a]);
            fprintf(output, "pop edx\n");
            fprintf(output, "pop ecx\n");
            
            if(a != EAX)
            {
                fprintf(output, "pop eax\n");
            }

            Freex86Register();

            return a;
        }
        break;

        case MOD_OP_NODE:
        {
            // TODO: fix 
            int a = GenerateNasmAssembly32(node->left, output);
            int b = GenerateNasmAssembly32(node->right, output);

            if(a != EAX)
            {
                fprintf(output, "push eax\n");
            }

            fprintf(output, "push ecx\n");
            fprintf(output, "push edx\n");
            fprintf(output, "mov ecx, %s\n", regName[b]);
            fprintf(output, "mov eax, %s\n", regName[a]);
            fprintf(output, "mov edx, 0\n");
            fprintf(output, "idiv ecx\n");
            fprintf(output, "mov %s, edx\n", regName[a]);
            fprintf(output, "pop edx\n");
            fprintf(output, "pop ecx\n");
            
            if(a != EAX)
            {
                fprintf(output, "pop eax\n");
            }

            Freex86Register();

            return a;
        }
        break;
        
        case EQ_OP_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {
                int reg = GenerateNasmAssembly32(node->right, output);
                struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(localSymbolTable, node->left->varName);
                if(localSymbol)
                {
                    int offset = localSymbol->binding < 0 ? localSymbol->binding + 1 : localSymbol->binding;
                    fprintf(output, "mov dword [ebp-%d], %s\n", offset * 4, regName[reg]);
                }
                else
                {
                    fprintf(output, "mov dword [%s], %s\n", node->left->varName, regName[reg]);
                }
                Freex86Register();
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                if(node->left->left->symbol->arrayDim == 1)
                {
                    int reg = GenerateNasmAssembly32(node->right, output);
                    int tmp = GenerateNasmAssembly32(node->left->right, output);
                    fprintf(output, "lea %s, [%s + %s * 4]\n", regName[tmp], node->left->left->varName, regName[tmp]);
                    fprintf(output, "mov dword [%s], %s\n", regName[tmp], regName[reg]);
                    Freex86Register();
                    Freex86Register();
                }
                else if(node->left->left->symbol->arrayDim == 2)
                {
                    int reg = GenerateNasmAssembly32(node->right, output);
                    int row = GenerateNasmAssembly32(node->left->right->left, output);
                    int col = GenerateNasmAssembly32(node->left->right->right, output);
                    fprintf(output, "imul %s, %s, %d\n", regName[row], regName[row], node->left->left->symbol->colSize);
                    fprintf(output, "add %s, %s\n", regName[row], regName[col]);
                    fprintf(output, "lea %s, [%s + %s * 4]\n", regName[row], node->left->left->varName, regName[row]);
                    fprintf(output, "mov dword [%s], %s\n", regName[row], regName[reg]);
                    Freex86Register();
                    Freex86Register();
                    Freex86Register();
                }
            }
            else if(node->left->nodeType == DEREF_NODE)
            {
                int a = GenerateNasmAssembly32(node->left->left, output);
                int b = GenerateNasmAssembly32(node->right, output);
                fprintf(output, "mov dword [%s], %s\n", regName[a], regName[b]);
                Freex86Register();
                Freex86Register();
            }
        }
        break;
        
        case IF_NODE:
        {
            int L1 = labelCounter++;
            
            int a = GenerateNasmAssembly32(node->left->left, output);
            int b = GenerateNasmAssembly32(node->left->right, output);

            fprintf(output, "cmp %s, %s\n", regName[a], regName[b]);
            GenerateJumpInstruction(output, node->left->nodeType, L1);

            Freex86Register();
            Freex86Register();
    
            if(node->right->nodeType == BRANCH_NODE)
            {
                GenerateNasmAssembly32(node->right->left, output);
                int L2 = labelCounter++;
                fprintf(output, "jmp L%d\n", L2);
                fprintf(output, "L%d:\n", L1);
                GenerateNasmAssembly32(node->right->right, output);
                fprintf(output, "L%d:\n", L2);
            }
            else
            {
                GenerateNasmAssembly32(node->right, output);
                fprintf(output, "L%d:\n", L1);
            }
        }
        break;
        
        case WHILE_NODE:
        {
            int L1 = labelCounter++;
            int L2 = labelCounter++;

            fprintf(output, "L%d:\n", L1);

            int a = GenerateNasmAssembly32(node->left->left, output);
            int b = GenerateNasmAssembly32(node->left->right, output);
            
            Freex86Register();
            Freex86Register();

            fprintf(output, "cmp %s, %s\n", regName[a], regName[b]);
            GenerateJumpInstruction(output, node->left->nodeType, L2);
            GenerateNasmAssembly32(node->right, output);

            fprintf(output, "jmp L%d\n", L1);
            fprintf(output, "L%d:\n", L2);       
        }
        break;
            
        case BREAK_NODE:
        {
        }
        break;
        
        case CONTINUE_NODE:
        {
        }
        break;

        case ADDR_OF_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {
                struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(localSymbolTable, node->left->varName);
                if(localSymbol)
                {
                    int reg = Getx86Register();
                    int offset = localSymbol->binding < 0 ? localSymbol->binding + 1 : localSymbol->binding;
                    fprintf(output, "lea %s, [ebp-%d]\n", regName[reg], offset * 4);
                    return reg;
                }

                int reg = Getx86Register();
                fprintf(output, "lea %s, [%s]\n", regName[reg], node->left->symbol->name);
                return reg;
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                if(node->left->left->symbol->arrayDim == 1)
                {
                    int reg = GenerateNasmAssembly32(node->left->right, output);
                    fprintf(output, "lea %s, [%s + %s * 4]\n", regName[reg], node->left->left->varName, regName[reg]);
                    return reg;
                }
                else if(node->left->left->symbol->arrayDim == 2)
                {
                    int reg = Getx86Register();
                    int row = GenerateNasmAssembly32(node->left->right->left, output);
                    int col = GenerateNasmAssembly32(node->left->right->right, output);
                    fprintf(output, "imul %s, %s, %d\n", regName[row], regName[row], node->left->left->symbol->colSize);
                    fprintf(output, "add %s, %s\n", regName[row], regName[col]);
                    fprintf(output, "lea %s, [%s + %s * 4]\n", regName[row], node->left->left->varName, regName[row]);
                    Freex86Register();
                    Freex86Register();
                    return reg;
                }
            }
        }
        break;

        case DEREF_NODE:
        {
            int reg = Getx86Register();
            int tmp = GenerateNasmAssembly32(node->left, output);
            fprintf(output, "mov %s, dword [%s]\n", regName[reg], regName[tmp]);
            Freex86Register();
            return reg;
        }
        break;

        case FUNCTION_CALL_NODE:
        {
            fprintf(output, ";calling %s()\n", node->left->varName);
            int tmpRegState[6] = {0};

            for(int n = 0; n < 6; n++)
            {
                if(regUseFlags[n] == 1)
                {
                    fprintf(output, "push %s\n", regName[n]);
                }
            }

            // pushing function arguments
            if(node->argList)
            {
                for(int n = node->argCount - 1; n >= 0; n--)
                {
                    int tmp = GenerateNasmAssembly32(&node->argList[n], output);
                    fprintf(output, "push %s\n", regName[tmp]);
                    Freex86Register();
                }
            }

            // saving and clearing old register states
            for(int n = 0; n < 6; n++)
            {
                tmpRegState[n] = regUseFlags[n];
                regUseFlags[n] = 0;
            }

            fprintf(output, "call %s\n", node->left->varName);

            // getting old reg state back
            for(int n = 0; n < 6; n++)
            {
                regUseFlags[n] = tmpRegState[n];
            }

            int reg = Getx86Register();
            fprintf(output, "mov %s, eax\n",regName[reg]);

            if(node->argList)
            {
                for(int n = 0; n < node->argCount; n++)
                {
                    int tmp = Getx86Register();
                    fprintf(output, "pop %s\n", regName[tmp]);
                    Freex86Register();
                }
            }

            for(int n = 5; n >= 0; n--)
            {
                if(tmpRegState[n] == 1)
                {
                    fprintf(output, "pop %s\n", regName[n]);
                }
            }

            fprintf(output, ";end %s()\n", node->left->varName);
            return reg;
        }
        break;

        case RETURN_NODE:
        {
            int reg = GenerateNasmAssembly32(node->left, output);
            fprintf(output, "mov eax, %s\n", regName[reg]);
            fprintf(output, "mov esp, ebp\n");
            fprintf(output, "pop ebp\n");
            fprintf(output, "ret\n");
            Freex86Register();
        }
        break;

        case FUNCTION_DEF_NODE:
        {
            fprintf(output, "\n%s:\n", node->varName);
            fprintf(output, "push ebp\n");
            fprintf(output, "mov ebp, esp\n");

            // allocating space for local variables in the stack
            if(node->localSymbolTable)
            {
                localSymbolTable = *(node->localSymbolTable);
                
                int localVarCount = 0;

                for(int n  = 0; n < localSymbolTable.size; n++)
                {
                    if(localSymbolTable.symbols[n].binding >= 1) localVarCount++;
                }
                
                if(localVarCount > 0)
                {
                    fprintf(output, "sub esp, %d\n", localVarCount * 4);
                }
            }

            // generate code for function body
            if(node->left)
            {
                GenerateNasmAssembly32(node->left, output);
            }

            fprintf(output, "mov esp, ebp\n");
            fprintf(output, "pop ebp\n");
            fprintf(output, "ret\n");
        }
        break;
    }

    return -1;
}

void x86AssemblyBackend_32bit(struct ASTNode *node, FILE *output)
{
    if(entryPointFound)
    {
        // text section
        fprintf(output, "section .text\n");
        fprintf(output, "global _start\n");

        // external function from library
        fprintf(output, "extern write_int\n");
        fprintf(output, "extern write_str\n");
        fprintf(output, "extern read_int\n");

        GenerateNasmAssembly32(node, output);

        fprintf(output, "\n_start:\n");
        fprintf(output, "call main\n");
        fprintf(output, "mov ebx, eax\n");
        fprintf(output, "mov eax, 1\n");
        fprintf(output, "int 0x80\n");

        // data segment(where string literals are stored)
        CreateDataSegment(output);

        // bss section (global variables are stored)
        fprintf(output, "\nsection .bss\n");
        AllocateStaticMemory(globalSymbolTable, output);
    }
    else
    {
        printf("error: entry point 'main' not defined !");
        printf("info: aborting x86 32 bit nasm assembly code generation !");
    }
}