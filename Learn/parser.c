#include "lexer.c"

Lexer lexer;

// left recursive
// expr := expr PLUS expr
//     | expr MINUS expr
//     | expr MUL expr
//     | ( epxr )
//     | INTEGER

//right recursive
// expr := p {b p}
// p := INTEGER | '(' expr ')' | u p
// b := '+' | '-' | '*' | '/' | '%'
// u := '-'

enum NodeType
{
    INTEGER,
    OP
};

struct AST
{
    int type;
    int value;
    char op;
    struct AST *left;
    struct AST *right;

    int precedence;
};

Token PeekNextToken(Lexer *lexer)
{
    Token tok = GetNextToken(lexer);
    lexer->pos -= tok.size;
    return tok;
}

struct AST *ParseExpression()
{
    Token token = GetNextToken(&lexer);
    // printf("tok: %s\n", TokenStr(token.type));

    if(token.type == TOKEN_INTEGER)
    {
        struct AST* node = (struct AST*)malloc(sizeof(struct AST));
        node->type = INTEGER;
        node->value = token.integerValue;
        node->left = 0;
        node->right = 0;

        Token next = PeekNextToken(&lexer);
        if(next.type == TOKEN_MUL || next.type == TOKEN_MINUS || next.type == TOKEN_PLUS)
        {
            struct AST *op = ParseExpression();
            op->left = node;

            if(op->right->type == OP)
            {
                if(op->precedence > op->right->precedence)
                {
                    struct AST *tmp = op->right;
                    op->right = tmp->left;
                    tmp->left = op;
                    return tmp;
                }
            }            
            return op;
        }
        return node;
    }
    else if(token.type == TOKEN_PLUS)
    {
        struct AST* op = (struct AST*)malloc(sizeof(struct AST));
        op->precedence = 10;
        op->type = OP;
        op->op = '+';
        struct AST *right = ParseExpression();
        op->right = right;
        return op;
    }
    else if(token.type == TOKEN_MINUS)
    {
        struct AST* op = (struct AST*)malloc(sizeof(struct AST));
        op->precedence = 10;
        op->type = OP;
        op->op = '-';
        struct AST *right = ParseExpression();
        op->right = right;
        return op;
    }
    else if(token.type == TOKEN_MUL)
    {
        struct AST* op = (struct AST*)malloc(sizeof(struct AST));
        op->precedence = 20;
        op->type = OP;
        op->op = '*';
        struct AST *right = ParseExpression();
        op->right = right;
        return op;
    }
    else if(token.type == TOKEN_OPEN_BRACKET)
    {
        struct AST *expr = ParseExpression();
        expr->precedence = 30;

        Token next = PeekNextToken(&lexer);

        if(next.type != TOKEN_CLOSE_BRACKET)
        {
            printf("[ERROR] line:%d col:%d -> expecting a closing bracket!\n", next.line, next.column);
        }
        else
        {
            GetNextToken(&lexer);
        }

        next = PeekNextToken(&lexer);
        if(next.type == TOKEN_MUL || next.type == TOKEN_MINUS || next.type == TOKEN_PLUS)
        {
            struct AST *node = ParseExpression();
            node->left = expr;
            return node;
        }

        return expr;
    }
}

int EvaluateExpression(struct AST *node)
{
    if(node->type == INTEGER)
    {
        return node->value;
    }
    else if(node->type == OP)
    {
        if(node->op == '+')
        {
            return EvaluateExpression(node->left) + EvaluateExpression(node->right);
        }
        if(node->op == '-')
        {
            return EvaluateExpression(node->left) - EvaluateExpression(node->right);
        }
        if(node->op == '*')
        {
            return EvaluateExpression(node->left) * EvaluateExpression(node->right);
        }
    }
}

void PrintAST(struct AST *ast, int indent)
{
    for(int n = 0; n < indent; n++)
    {
        printf("   ");
    }

    printf("+-");

    if(ast->type == INTEGER)
    {
        printf("INT: %d\n", ast->value);
    }
    else if(ast->type == OP)
    {
        printf("OP:'%c'\n", ast->op);
        PrintAST(ast->left, indent + 1);
        PrintAST(ast->right, indent + 1);
    }
}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        lexer.data = LoadFileNullTerminated(argv[1]);

        if(lexer.data)
        {
            struct AST *ast = ParseExpression();
            PrintAST(ast, 0);
            printf("eval: %d\n", EvaluateExpression(ast));
        }

        free(lexer.data);
    }
}

// int main(int argc, char *argv[])
// {
//     if(argc > 1)
//     {
//         lexer.data = LoadFileNullTerminated(argv[1]);

//         if(lexer.data)
//         {
//             while(true)
//             {
//                 Token token = GetNextToken(&lexer);
//                 PrintTokenInfo(token);

//                 if(token.type == TOKEN_STOP)
//                 {
//                     break;
//                 }
//             }
//         }
//         free(lexer.data);
//     }
// }