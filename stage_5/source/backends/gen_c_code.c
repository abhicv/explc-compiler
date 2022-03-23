#include "../ast.h"
#include "../symbol.h"

extern struct GlobalSymbolTable globalSymbolTable;
struct LocalSymbolTable _localSymbolTable;

char *typeString[] = {
    [INTEGER_TYPE] = "int",
    [STRING_TYPE] = "char *",
    [POINTER_INT_TYPE] = "int *",
    [POINTER_STR_TYPE] = "str *",
};

// declares global variables and function declaration
void DeclareGlobalSymbols(FILE *output)
{
    for(int n = 0; n < globalSymbolTable.size; n++)
    {
        struct GlobalSymbol symbol = globalSymbolTable.symbols[n];
        if(symbol.functionLabel <= -1)
        {
            if(symbol.arrayDim == 0)
            {
                fprintf(output, "%s %s;\n", typeString[symbol.type], symbol.name);
            }   
            else if(symbol.arrayDim == 1)
            {
                fprintf(output, "%s %s[%d];\n", typeString[symbol.type], symbol.name, symbol.size);
            }
            else if(symbol.arrayDim == 2)
            {
                fprintf(output, "%s %s[%d][%d];\n", typeString[symbol.type], symbol.name, symbol.size / symbol.colSize, symbol.colSize);
            }
        }
        else
        {
            fprintf(output, "%s %s(", typeString[symbol.type], symbol.name);
            if(symbol.paramList)
            {
                for(int i = 0; i < symbol.paramList->size-1; i++)
                {
                    fprintf(output, "%s %s, ", typeString[symbol.paramList->params[i].type], symbol.paramList->params[i].name);
                }
                int index = symbol.paramList->size-1;
                fprintf(output, "%s %s", typeString[symbol.paramList->params[index].type], symbol.paramList->params[index].name);
            }
            fprintf(output, ");\n");
        }
    }
}

void GenerateCBoilerPlateCode(FILE *output)
{
    fprintf(output, "// auto generated c source code by explc c backend! DO NOT MODIFY !\n");
    fprintf(output, "#include <stdio.h>\n");
    fprintf(output, "#include <stdlib.h>\n");

    fprintf(output, "\n//global variables and function declaration from global symbol table\n");
    DeclareGlobalSymbols(output);
    fprintf(output, "\n");
}

char* GenerateC(struct ASTNode *node, FILE *output)
{
    switch(node->nodeType)
    {
        case CONNECTOR_NODE:
        {
            GenerateC(node->left, output);
            GenerateC(node->right, output);
        }
        break;

        case WRITE_NODE:
        {
            char *left = GenerateC(node->left, output);  
            if(node->left->expType == INTEGER_TYPE)
            {
                fprintf(output, "printf(\"%%d\\n\", %s);\n", left);
            }
            else if(node->left->expType == STRING_TYPE)
            {
                fprintf(output, "printf(\"%%s\\n\", %s);\n", left);
            }
            free(left);
        };
        break;

        case READ_NODE:
        {
            char *left = GenerateC(node->left, output);  
            fprintf(output, "scanf(\"%%d\", %s);\n", left);
            free(left);
        };
        break;
        
        case INTEGER_NODE:
        {
            int x = node->val > 0 ? node->val : -node->val;
            int count = 0;
            do
            {   
                x = x / 10;
                count++;
            } while(x);

            char *buf = (char*)malloc(count + 1);
            x = node->val > 0 ? node->val : -node->val;    
            for(int n = 0; n < count; n++)
            {
                buf[count - 1 - n] = (x % 10) + 48;
                x = x / 10;
            }
            buf[count] = 0;
            return buf;
        }
        break;

        case STRING_NODE:
        {
            int len = strlen(node->strVal);
            char *buf = (char*)malloc(len + 3);
            buf[0] = '"';
            buf[len + 1] = '"';
            strncpy(buf + 1, node->strVal, len);
            buf[len + 2] = 0;
            return buf;
        }
        break;

        case IDENTIFIER_NODE:
        {
            struct LocalSymbol *localSymbol = LookUpLocalSymbolTable(_localSymbolTable, node->varName);
            if(localSymbol)
            {
                return strdup(localSymbol->name);
            }
            return strdup(node->symbol->name);
        }
        break;

        case ARRAY_NODE:
        {
            if(node->left->symbol->arrayDim == 1)
            {
                char* index = GenerateC(node->right, output);
                int len = strlen(node->left->varName) + strlen(index) + 3;
                char *buf = malloc(len);
                sprintf(buf, "%s[%s]\n", node->left->varName, index);
                buf[len - 1] = 0;
                free(index);
                return buf;
            }
            else if(node->left->symbol->arrayDim == 2)
            {
                char* row = GenerateC(node->right->left, output);
                char* col = GenerateC(node->right->right, output);
                int len = strlen(node->left->varName) + strlen(row) + strlen(col) + 5;
                char *buf = malloc(len);
                sprintf(buf, "%s[%s][%s]\n", node->left->varName, row, col);
                buf[len - 1] = 0;
                free(row);
                free(col);
                return buf;
            }
        }
        break;

        case EQ_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            fprintf(output, "%s = %s;\n", lhs, rhs);
            free(lhs);
            free(rhs);
        }
        break;

        case PLUS_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 4;
            char *buf = malloc(len);
            sprintf(buf, "%s + %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case MINUS_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 4;
            char *buf = malloc(len);
            sprintf(buf, "%s - %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;
        
        case MUL_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 4;
            char *buf = malloc(len);
            sprintf(buf, "%s * %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case DIV_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 4;
            char *buf = malloc(len);
            sprintf(buf, "%s / %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case MOD_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 4;
            char *buf = malloc(len);
            sprintf(buf, "%s %% %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case LT_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 4;
            char *buf = malloc(len);
            sprintf(buf, "%s < %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case LT_EQ_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 5;
            char *buf = malloc(len);
            sprintf(buf, "%s <= %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case GT_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 4;
            char *buf = malloc(len);
            sprintf(buf, "%s > %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case GT_EQ_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 5;
            char *buf = malloc(len);
            sprintf(buf, "%s >= %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case EQUAL_EQ_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 5;
            char *buf = malloc(len);
            sprintf(buf, "%s == %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case NOT_EQ_OP_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 5;
            char *buf = malloc(len);
            sprintf(buf, "%s != %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case AND_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 5;
            char *buf = malloc(len);
            sprintf(buf, "%s && %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case OR_NODE:
        {
            char *lhs = GenerateC(node->left, output);
            char *rhs = GenerateC(node->right, output);
            int len = strlen(lhs) + strlen(rhs) + 5;
            char *buf = malloc(len);
            sprintf(buf, "%s || %s", lhs, rhs);
            buf[len-1] = 0;
            free(lhs);
            free(rhs);
            return buf;
        }
        break;

        case IF_NODE:
        {
            char *condition = GenerateC(node->left, output);
            fprintf(output, "if(%s) {\n", condition);
            free(condition);

            if(node->right->nodeType == BRANCH_NODE)
            {
                GenerateC(node->right->left, output);
                fprintf(output, "}\n");
                fprintf(output, "else {\n");
                GenerateC(node->right->right, output);
                fprintf(output, "}\n");
            }
            else
            {
                GenerateC(node->right, output);
                fprintf(output, "}\n");
            }
        };
        break;

        case WHILE_NODE:
        {
            char *condition = GenerateC(node->left, output);
            fprintf(output, "while ( %s ) {\n", condition);
            GenerateC(node->right, output);
            fprintf(output, "}\n");
            free(condition);
        } 
        break;

        case BREAK_NODE:
        {
            fprintf(output, "break;\n");
        }
        break;

        case CONTINUE_NODE:
        {
            fprintf(output, "continue;\n");
        }
        break;

        case FUNCTION_CALL_NODE:
        {
            char buf[4096] = {0};
            int pos = 0;
            sprintf(&buf[pos], "%s(", node->left->varName);
            pos = strlen(buf);

            if(node->argList)
            {
                for(int n = 0; n < node->argCount - 1; n++)
                {
                    char *arg = GenerateC(&node->argList[n], output);
                    pos = strlen(buf);
                    sprintf(&buf[pos], "%s, ", arg);
                    free(arg);
                }
                char *arg = GenerateC(&node->argList[node->argCount - 1], output);
                pos = strlen(buf);
                sprintf(&buf[pos], "%s", arg);
                free(arg);
            }

            pos = strlen(buf);
            sprintf(&buf[pos], ")");
            return strdup(buf);
        }
        break;

        case DEREF_NODE:
        {
            char *exp = GenerateC(node->left, output);
            int len = strlen(exp) + 4;
            char *buf = malloc(len);
            sprintf(buf, "*(%s)", exp);
            buf[len - 1] = 0;
            free(exp);
            return buf;
        }
        break;

        case ADDR_OF_NODE:
        {
            char *exp = GenerateC(node->left, output);
            int len = strlen(exp) + 4;
            char *buf = malloc(len);
            sprintf(buf, "&(%s)", exp);
            buf[len - 1] = 0;
            free(exp);
            return buf;
        }
        break;

        case FUNCTION_DEF_NODE:
        {
            fprintf(output, "\n%s %s", typeString[node->returnType], node->varName);
            fprintf(output, "(");

            if(node->paramList)
            {
                for(int n = 0; n < node->paramList->size-1; n++)
                {
                    fprintf(output, "%s %s, ", typeString[node->paramList->params[n].type], node->paramList->params[n].name);
                }
                int index = node->paramList->size - 1;
                fprintf(output, "%s %s", typeString[node->paramList->params[index].type], node->paramList->params[index].name);
            }

            fprintf(output, ")\n");
            fprintf(output, "{\n");

            _localSymbolTable.size = 0;
            if(node->localSymbolTable)
            {
                for(int n = 0; n < node->localSymbolTable->size; n++)
                {
                    struct LocalSymbol symbol = node->localSymbolTable->symbols[n];
                    if(symbol.binding > 0)
                    {
                        fprintf(output, "%s %s;\n", typeString[symbol.type], symbol.name);
                    }
                }
                _localSymbolTable = *(node->localSymbolTable);
            }

            if(node->left)
            {
                GenerateC(node->left, output);
            }
            fprintf(output, "}\n");
        }
        break;

        case RETURN_NODE:
        {
            char *ret = GenerateC(node->left, output);
            fprintf(output, "return (%s);\n", ret);
            free(ret);
        }
        break;
    }
    
    return strdup("no implmented yet!"); 
}

void C_backend(struct ASTNode *node, FILE *output)
{
    GenerateCBoilerPlateCode(output);
    GenerateC(node, output);
}