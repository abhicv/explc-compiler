#include "../ast.h"

extern struct GlobalSymbol *globalSymbolTable;

int variableCounter = 0;
int labelCounter = 0;

#define MAX_TEMP_VAR_COUNT 20
int tempVariables[MAX_TEMP_VAR_COUNT] = {0};

int GetTempVariable()
{
    for(int n = 0; n < MAX_TEMP_VAR_COUNT; n++)
    {
        if(tempVariables[n] == 0)
        {
            tempVariables[n] = 1;
            return n;
        }
    }

    return 0;
}

void FreeTempVariable()
{
    for(int n = MAX_TEMP_VAR_COUNT - 1; n >= 0; n--)
    {
        if(tempVariables[n] == 1)
        {
            tempVariables[n] = 0;
            return;
        }
    }
}

void DeclareVariablesFromGlobalSymbolTable(struct GlobalSymbol *symbol, FILE *output)
{
    if(symbol)
    {
        if(symbol->type == INTEGER_TYPE)
        {
            if(symbol->size > 1)
            {
                fprintf(output, "int %s[%d] = {0};\n", symbol->name, symbol->size);
            }
            else
            {
                fprintf(output, "int %s = 0;\n", symbol->name);
            }
        }
        else if(symbol->type == STRING_TYPE)
        {
            if(symbol->size > 1)
            {
                fprintf(output, "char *%s[%d] = {0};\n", symbol->name, symbol->size);
            }
            else
            {
                fprintf(output, "char *%s = 0;\n", symbol->name);
            }
        }

        DeclareVariablesFromGlobalSymbolTable(symbol->next, output);
    }
}

void GenerateCBoilerPlateCode(FILE *output)
{
    fprintf(output, "// auto generated c source code by explc c backend! DO NOT MODIFY !\n");
    fprintf(output, "#include <stdio.h>\n");
    fprintf(output, "#include <stdlib.h>\n");
    fprintf(output, "#include <stdbool.h>\n");
    fprintf(output, "#include <string.h>\n");

    fprintf(output, "\n");
    fprintf(output, "int main(int argc, char *argv[])\n");
    fprintf(output, "{\n");

    fprintf(output, "\n//variables from global symbol table\n");
    DeclareVariablesFromGlobalSymbolTable(globalSymbolTable, output);
    fprintf(output, "\n");

    //temporary variables
    for(int n = 0; n < MAX_TEMP_VAR_COUNT; n++)
    {
        fprintf(output, "int var_%d = 0;\n", n);
    }
    fprintf(output, "\n");
}

char *indentStr = "\t";

int GenerateCCode(struct ASTNode *node, FILE *output, int indent)
{
    switch (node->nodeType)
    {
        case CONNECTOR_NODE:
        {
            GenerateCCode(node->left, output, indent);
            GenerateCCode(node->right, output, indent);
        }
        break;

        case WRITE_NODE:
        {   
            int a = GenerateCCode(node->left, output, indent);
            
            fprintf(output, "printf(\"%%d\\n\", var_%d);\n", a);
            FreeTempVariable();
        }
        break;

        case READ_NODE:
        {
            
            fprintf(output, "scanf(\"%%d\", &%c);\n", node->left->varName[0]);           
            FreeTempVariable();
        }
        break;

        case INTEGER_NODE:
        {
            int a = GetTempVariable();
            
            fprintf(output, "var_%d = %d;\n", a, node->val);
            return a;
        }
        break;

        case IDENTIFIER_NODE:
        {
            int a = GetTempVariable();
            
            fprintf(output, "var_%d = %c;\n", a, node->varName[0]);
            return a;
        }
        break;

        case PLUS_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "var_%d = var_%d + var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case MINUS_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "var_%d = var_%d - var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case MUL_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "var_%d = var_%d * var_%d;\n", a, a, b);
            FreeTempVariable();
            return a;  
        }
        break;

        case DIV_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "var_%d = var_%d / var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case EQ_OP_NODE:
        {
            int a = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "%c = var_%d;\n", node->left->varName[0], a);
            FreeTempVariable();
        }             
        break;

        case LT_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "var_%d = var_%d < var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case LT_EQ_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "var_%d = var_%d >= var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case GT_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);

            fprintf(output, "var_%d = var_%d > var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;
        
        case GT_EQ_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            
            fprintf(output, "var_%d = var_%d >= var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case EQUAL_EQ_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            fprintf(output, "var_%d = var_%d == var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case NOT_EQ_OP_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            int b = GenerateCCode(node->right, output, indent);
            fprintf(output, "var_%d = var_%d != var_%d;\n", a, a, b);
            FreeTempVariable();
            return a; 
        }
        break;

        case IF_NODE:
        {
            int a = GenerateCCode(node->left, output, indent);
            fprintf(output, "if(var_%d) {\n", a);
            if(node->right->nodeType == BRANCH_NODE)
            {
                GenerateCCode(node->right->left, output, indent + 1);
                fprintf(output, "}\n");
                fprintf(output, "else {\n");
                fprintf(output, "}\n");
            }
            else
            {
                GenerateCCode(node->right, output, indent + 1);
                fprintf(output, "}\n");
            }
            FreeTempVariable();
        }
        break;

        case WHILE_NODE:
        {
            int L1 = labelCounter++;
            fprintf(output, "L%d:\n", L1);
            int a = GenerateCCode(node->left, output, indent);
            
            fprintf(output, "if(var_%d) {\n", a);
            GenerateCCode(node->right, output, indent + 1);
            for(int n = 0; n < indent+1; n++) { fprintf(output, "%s", indentStr); }
            fprintf(output, "goto L%d;\n", L1);
            
            fprintf(output, "}\n");
            FreeTempVariable();
        }
        break;
    }    
}

void C_backend(struct ASTNode *node)
{
    FILE *output = fopen("generated.c", "w");
    GenerateCBoilerPlateCode(output);
    //GenerateCCode(node, output, 1);
    fprintf(output, "return 0;\n");
    fprintf(output, "}");
    fclose(output);
}