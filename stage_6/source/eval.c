#include "ast.h"

extern struct GlobalSymbolTable globalSymbolTable;

typedef struct EvalResult
{
    union
    {
        int intVal;
        char *strVal;
    };

    int type;
} EvalResult;

EvalResult virtualMem[2048] = {0};

EvalResult EvaluateAST(struct ASTNode *node)
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
            EvalResult result = EvaluateAST(node->left);
            
            if(result.type == INTEGER_TYPE)
            {
                printf("%d\n", result.intVal);
            }
            else
            {
                if(result.strVal)
                {
                    printf("%s\n", result.strVal);
                }
                else
                {
                    printf("(null)\n");
                }
            }
        }
        break;
        
        case READ_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {
                struct GlobalSymbol* symbol = LookUpGlobalSymbolTable(globalSymbolTable, node->left->varName);
                int index = symbol->binding - 4096;
                // scanf("%d", &virtualMem[index].intVal);
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                struct GlobalSymbol* symbol = LookUpGlobalSymbolTable(globalSymbolTable, node->left->left->varName);
                EvalResult result = EvaluateAST(node->left->right);
                int index = symbol->binding + result.intVal - 4096;
                // scanf("%d", &virtualMem[index].intVal);
            }
        }
        break;
        
        case INTEGER_NODE:
        {
            EvalResult result = {0};
            result.type = INTEGER_TYPE;
            result.intVal = node->val;
            return result;
        }
        break;
        
        case STRING_NODE:
        {
            EvalResult result = {0};
            result.type = STRING_TYPE;
            result.strVal = node->strVal;
            return result;
        }
        break;

        case IDENTIFIER_NODE:
        {
            struct GlobalSymbol* symbol = LookUpGlobalSymbolTable(globalSymbolTable, node->varName);
            int index = symbol->binding - 4096;
            EvalResult result = virtualMem[index];
            result.type = symbol->type;
            return result;
        }
        break;
        
        case ARRAY_NODE:
        {
            struct GlobalSymbol* symbol = LookUpGlobalSymbolTable(globalSymbolTable, node->left->varName);
            EvalResult tmpResult = EvaluateAST(node->right);
            int index = symbol->binding + tmpResult.intVal - 4096;
            EvalResult result = virtualMem[index];
            result.type = symbol->type;
            return result;
        }

        case PLUS_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = l.intVal + r.intVal;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case MINUS_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = l.intVal - r.intVal;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case MUL_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = l.intVal * r.intVal;
            result.type = INTEGER_TYPE;
            return result;
        } 
        break;
        
        case DIV_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = l.intVal / r.intVal;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case MOD_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = l.intVal % r.intVal;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;

        case LT_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = (l.intVal < r.intVal) ? 1 : 0;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case LT_EQ_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = (l.intVal <= r.intVal) ? 1 : 0;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case GT_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = (l.intVal > r.intVal) ? 1 : 0;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case GT_EQ_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = (l.intVal >= r.intVal) ? 1 : 0;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case EQUAL_EQ_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = (l.intVal == r.intVal) ? 1 : 0;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case NOT_EQ_OP_NODE:
        {
            EvalResult l = EvaluateAST(node->left);
            EvalResult r = EvaluateAST(node->right);
            EvalResult result = {0};
            result.intVal = (l.intVal != r.intVal) ? 1 : 0;
            result.type = INTEGER_TYPE;
            return result;
        }
        break;
        
        case EQ_OP_NODE:
        {
            if(node->left->nodeType == IDENTIFIER_NODE)
            {
                struct GlobalSymbol* symbol = LookUpGlobalSymbolTable(globalSymbolTable, node->left->varName);
                int index = symbol->binding - 4096;
                virtualMem[index] = EvaluateAST(node->right);
            }
            else if(node->left->nodeType == ARRAY_NODE)
            {
                struct GlobalSymbol* symbol = LookUpGlobalSymbolTable(globalSymbolTable, node->left->left->varName);
                EvalResult tmpResult = EvaluateAST(node->left->right);
                int index = symbol->binding + tmpResult.intVal - 4096;
                EvalResult result = EvaluateAST(node->right);
                virtualMem[index] = result;
            }
        }             
        break;
        
        case IF_NODE:
        {
            EvalResult result =  EvaluateAST(node->left);
            if(result.intVal == 1)
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
            EvalResult result = EvaluateAST(node->left); 
            while(result.intVal == 1)
            {
                EvaluateAST(node->right);
                result = EvaluateAST(node->left);
            }            
        }
        break;
    }
}