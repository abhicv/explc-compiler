//backend to generate nasm x86 32 bit assembly

#include "../ast.h"

extern struct GlobalSymbol *globalSymbolTable;

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

unsigned int basePointerReg = EBP;
unsigned int stackPointerReg = ESP;

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

static int Getx86Register()
{
    for(int n = 0; n < REGISTER_COUNT - 2; n++)
    {
        if(regUseFlags[n] == 0)
        {
            regUseFlags[n] = 1;
            return n;
        }
    }
}

static void Freex86Register()
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
int AllocateStaticMemory(struct GlobalSymbol *symbol, FILE *output)
{
    if(symbol)
    {
        fprintf(output, "%s resd %d\n", symbol->name, symbol->size);
        AllocateStaticMemory(symbol->next, output);
    }
}

// prints the string literal table
void PrintStrTable()
{
    for(int n = 0; n < stringLiteralCount; n++)
    {
        printf("%u: %s, len: %u\n", n, stringLiteralTable[n].str, stringLiteralTable[n].size);
    }
}

void CreateDataSegment(FILE *output)
{
    fprintf(output, "\nsection .data\n");
    for(int n = 0; n < stringLiteralCount; n++)
    {
        fprintf(output, "str_%d db '%s', 0x0\n", n, stringLiteralTable[n].str);
    }

    fprintf(output, "NL db 0xA\n");
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
            if(node->left->nodeType == STRING_NODE)
            {
                int reg = GenerateNasmAssembly32(node->left, output);
            
                fprintf(output, "\n");
                fprintf(output, "push eax\n");
                fprintf(output, "push ebx\n");
                fprintf(output, "push ecx\n");
                fprintf(output, "push edx\n");
                fprintf(output, "mov edx, %d\n", (int)strlen(node->left->strVal));
                fprintf(output, "mov ecx, %s\n", regName[reg]);
                fprintf(output, "mov ebx, 1\n");
                fprintf(output, "mov eax, 4\n");
                fprintf(output, "int 0x80\n");
                fprintf(output, "mov edx, 1\n");
                fprintf(output, "mov ecx, NL\n");
                fprintf(output, "mov ebx, 1\n");
                fprintf(output, "mov eax, 4\n");
                fprintf(output, "int 0x80\n");
                fprintf(output, "pop edx\n");
                fprintf(output, "pop ecx\n");
                fprintf(output, "pop ebx\n");
                fprintf(output, "pop eax\n");
                fprintf(output, "\n");

                Freex86Register();
            }
            else
            {
                int reg = GenerateNasmAssembly32(node->left, output);

                if(reg != EBX)
                {
                    fprintf(output, "mov ebx, %s\n", regName[reg]);
                }

                int L1 = labelCounter++;

                fprintf(output, "push eax\n");
                fprintf(output, "push ebx\n");
                fprintf(output, "push ecx\n");
                fprintf(output, "push edx\n");
                fprintf(output, "push edi\n");
                fprintf(output, "sub esp, 10\n");
                fprintf(output, "mov dword [esp], 0\n");
                fprintf(output, "mov dword [esp + 4], 0\n");
                fprintf(output, "mov word  [esp + 8], 0\n");
                fprintf(output, "mov ecx, 0\n");
                fprintf(output, "L%u:\n", L1);
                fprintf(output, "mov eax, ebx\n");
                fprintf(output, "mov edx, 0\n");
                fprintf(output, "mov edi, 10\n");
                fprintf(output, "idiv edi\n");
                fprintf(output, "add dl, 48\n");
                fprintf(output, "mov eax, 9\n");
                fprintf(output, "sub eax, ecx\n");
                fprintf(output, "mov byte [esp + eax], dl\n");
                fprintf(output, "add ecx, 1 \n");
                fprintf(output, "mov eax, ebx\n");
                fprintf(output, "mov edx, 0\n");
                fprintf(output, "mov edi, 10\n");
                fprintf(output, "idiv edi\n");
                fprintf(output, "mov ebx, eax\n");
                fprintf(output, "cmp ebx, 0\n");
                fprintf(output, "jne L%d\n", L1);
                fprintf(output, "mov edx, ecx\n");
                fprintf(output, "mov eax, 10\n");
                fprintf(output, "sub eax, ecx\n");
                fprintf(output, "lea eax, [esp + eax]\n");
                fprintf(output, "mov ecx, eax\n");
                fprintf(output, "mov ebx, 1\n");
                fprintf(output, "mov eax, 4\n");
                fprintf(output, "int 0x80\n");
                fprintf(output, "mov edx, 1\n");
                fprintf(output, "mov ecx, NL\n");
                fprintf(output, "mov ebx, 1\n");
                fprintf(output, "mov eax, 4\n");
                fprintf(output, "int 0x80\n");
                fprintf(output, "add esp, 10\n");
                fprintf(output, "pop edi\n");
                fprintf(output, "pop edx\n");
                fprintf(output, "pop ecx\n");
                fprintf(output, "pop ebx\n");
                fprintf(output, "pop eax\n");

                Freex86Register();
            }
        }
        break;
        
        case READ_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {                
                int L1 = labelCounter++;
                int L2 = labelCounter++;

                fprintf(output, "push eax\n");
                fprintf(output, "push ebx\n");
                fprintf(output, "push ecx\n");
                fprintf(output, "push edx\n");
                fprintf(output, "push edi\n");
                fprintf(output, "sub esp, 10\n");
                fprintf(output, "mov dword [esp], 0\n");
                fprintf(output, "mov dword [esp + 4], 0\n");
                fprintf(output, "mov word [esp + 8], 0\n");
                fprintf(output, "lea esi, [esp]\n");
                fprintf(output, "mov eax, 3\n");
                fprintf(output, "mov ebx, 0\n");
                fprintf(output, "mov ecx, esi\n");
                fprintf(output, "mov edx, 10\n");
                fprintf(output, "int 0x80\n");
                fprintf(output, "mov eax, 0\n");
                fprintf(output, "mov ecx, 0\n");
                fprintf(output, "mov ebx, 0\n");
                fprintf(output, "mov bl, byte [esi]\n");
                fprintf(output, "cmp ebx, 0\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "cmp ebx, 0xa\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "L%d:\n", L1);
                fprintf(output, "mov edx, ecx\n");
                fprintf(output, "shl edx, 3\n");
                fprintf(output, "shl ecx, 1\n");
                fprintf(output, "add ecx, edx\n");
                fprintf(output, "sub ebx, 48    \n");
                fprintf(output, "add ecx, ebx\n");
                fprintf(output, "inc eax\n");
                fprintf(output, "mov ebx, 0\n");
                fprintf(output, "mov bl, byte [esi + eax]\n");
                fprintf(output, "cmp ebx, 0\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "cmp ebx, 0xa\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "jmp L%d\n", L1);
                fprintf(output, "L%d:\n", L2);
                fprintf(output, "mov dword [%s], ecx\n", node->left->varName);
                fprintf(output, "add esp, 10\n");
                fprintf(output, "pop edi\n");
                fprintf(output, "pop edx\n");
                fprintf(output, "pop ecx\n");
                fprintf(output, "pop ebx\n");
                fprintf(output, "pop eax\n");
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                int L1 = labelCounter++;
                int L2 = labelCounter++;

                fprintf(output, "push eax\n");
                fprintf(output, "push ebx\n");
                fprintf(output, "push ecx\n");
                fprintf(output, "push edx\n");
                fprintf(output, "push edi\n");
                fprintf(output, "sub esp, 10\n");
                fprintf(output, "mov dword [esp], 0\n");
                fprintf(output, "mov dword [esp + 4], 0\n");
                fprintf(output, "mov word [esp + 8], 0\n");
                fprintf(output, "lea esi, [esp]\n");
                fprintf(output, "mov eax, 3\n");
                fprintf(output, "mov ebx, 0\n");
                fprintf(output, "mov ecx, esi\n");
                fprintf(output, "mov edx, 10\n");
                fprintf(output, "int 0x80\n");
                fprintf(output, "mov eax, 0\n");
                fprintf(output, "mov ecx, 0\n");
                fprintf(output, "mov ebx, 0\n");
                fprintf(output, "mov bl, byte [esi]\n");
                fprintf(output, "cmp ebx, 0\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "cmp ebx, 0xa\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "L%d:\n", L1);
                fprintf(output, "mov edx, ecx\n");
                fprintf(output, "shl edx, 3\n");
                fprintf(output, "shl ecx, 1\n");
                fprintf(output, "add ecx, edx\n");
                fprintf(output, "sub ebx, 48    \n");
                fprintf(output, "add ecx, ebx\n");
                fprintf(output, "inc eax\n");
                fprintf(output, "mov ebx, 0\n");
                fprintf(output, "mov bl, byte [esi + eax]\n");
                fprintf(output, "cmp ebx, 0\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "cmp ebx, 0xa\n");
                fprintf(output, "je L%d\n", L2);
                fprintf(output, "jmp L%d\n", L1);
                fprintf(output, "L%d:\n", L2);

                fprintf(output, "\npush ecx\n");

                int tmp = Getx86Register();
                fprintf(output, "mov %s, dword [esp]\n", regName[tmp]);
                
                int reg = GenerateNasmAssembly32(node->left->right, output);
                fprintf(output, "lea %s, [%s + %s * 4]\n", regName[reg], node->left->left->varName, regName[reg]);
                fprintf(output, "mov dword [%s], %s\n", regName[reg], regName[tmp]);
                
                fprintf(output, "pop ecx\n");

                Freex86Register();
                Freex86Register();
                
                fprintf(output, "add esp, 10\n");
                fprintf(output, "pop edi\n");
                fprintf(output, "pop edx\n");
                fprintf(output, "pop ecx\n");
                fprintf(output, "pop ebx\n");
                fprintf(output, "pop eax\n");
            }
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
            int reg = Getx86Register();
            fprintf(output, "mov %s, dword [%s]\n", regName[reg], node->varName);
            return reg;
        }
        break;
        
        case ARRAY_NODE:
        {
            int reg = Getx86Register();

            if(node->right->nodeType == INTEGER_NODE)
            {
                int reg_1 = Getx86Register();
                fprintf(output, "lea %s, [%s + %d]\n", regName[reg_1], node->left->varName, node->right->val  * 4);
                fprintf(output, "mov %s, dword [%s]\n", regName[reg], regName[reg_1]);
                Freex86Register();
            }
            else
            {
                int reg_1 = GenerateNasmAssembly32(node->right, output);
                fprintf(output, "lea %s, [%s + %s * 4]\n", regName[reg_1], node->left->varName, regName[reg_1]);
                fprintf(output, "mov %s, dword [%s]\n", regName[reg], regName[reg_1]);
                Freex86Register();
            }

            return reg;
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
                if(node->right->nodeType == INTEGER_NODE)
                {
                    fprintf(output, "mov dword [%s], %d\n", node->left->varName, node->right->val);
                }
                else
                {
                    int reg = GenerateNasmAssembly32(node->right, output);
                    fprintf(output, "mov dword [%s], %s\n", node->left->varName, regName[reg]);
                    Freex86Register();
                }
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                int reg = GenerateNasmAssembly32(node->right, output);

                if(node->left->right->nodeType == INTEGER_NODE)
                {
                    int reg_1 = Getx86Register();
                    fprintf(output, "lea %s, [%s + %d]\n", regName[reg_1], node->left->left->varName, node->left->right->val * 4);
                    fprintf(output, "mov dword [%s], %s\n", regName[reg_1], regName[reg]);
                }
                else
                {
                    int reg_1 = GenerateNasmAssembly32(node->left->right, output);
                    fprintf(output, "lea %s, [%s + %s * 4]\n", regName[reg_1], node->left->left->varName, regName[reg_1]);
                    fprintf(output, "mov dword [%s], %s\n", regName[reg_1], regName[reg]);
                }

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
            // if(labelStackPos >= 2)
            // {
            //     fprintf(output, "JMP L%d\n", labelStack[labelStackPos-1]);
            // }
        }
        break;
        
        case CONTINUE_NODE:
        {
            // if(labelStackPos >= 2)
            // {
            //     fprintf(output, "JMP L%d\n", labelStack[labelStackPos-2]);
            // }
        }
        break;
    }
}

void x86AssemblyBackend_32bit(struct ASTNode *node)
{
    FILE *output = fopen("out_x86.asm", "w");
    
    // bss section (global variables are stored)
    fprintf(output, "section .bss\n");
    AllocateStaticMemory(globalSymbolTable, output);
    
    // text section
    fprintf(output, "\nsection .text\n");
    fprintf(output, "global _start\n");
    fprintf(output, "_start:\n");
    GenerateNasmAssembly32(node, output);

    // calling exit syscall
    fprintf(output, "\nmov eax, 1\n");
    fprintf(output, "int 0x80\n");

    // data segment(where string literals are stored)
    CreateDataSegment(output);

    fclose(output);
}