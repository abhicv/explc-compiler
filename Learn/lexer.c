#include "lexer.h"

char *TokenStr(int type)
{
    switch(type)
    {
        case TOKEN_INTEGER:
            return "TOKEN_INTEGER";
        case TOKEN_PLUS:
            return "TOKEN_PLUS";
        case TOKEN_MINUS:
            return "TOKEN_MINUS";
        case TOKEN_MUL:
            return "TOKEN_MUL";
        case TOKEN_OPEN_BRACKET:
            return "TOKEN_OPEN_BRACKET";
        case TOKEN_CLOSE_BRACKET:
            return "TOKEN_CLOSE_BRACKET";
        case TOKEN_STOP:
            return "TOKEN_STOP";
    }
}

char GetNextCharacter(Lexer *lexer)
{
    return lexer->data[lexer->pos++];
}

char PeekNextCharacter(Lexer *lexer)
{
    return lexer->data[lexer->pos];
}

char *LoadFileNullTerminated(const char *fileName)
{
    char *data = 0;
    
    FILE *input = fopen(fileName, "r");
    if(input)
    {
        fseek(input, 0, SEEK_END);
        int size = ftell(input);
        fseek(input, 0, SEEK_SET);

        data = (char*)malloc(size + 1);
        fread(data, 1, size, input);
        data[size] = 0;
        
        fclose(input);
    }
    else
    {
        printf("[ERROR] failed to open file -> %s\n", fileName);
    }

    return data;
}

int IsNumeric(char c)
{
    return (c >= '0' && c <= '9');
}

int IsAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

Token ParseInteger(Lexer *lexer)
{
    int value = 0;
    int start = lexer->pos - 1;
    int pos = start;
 
    char character = lexer->data[pos];
    while(IsNumeric(character))
    {
        value = (value * 10) + character -  '0';
        character = lexer->data[++pos];
    }

    lexer->pos = pos;
    int end = pos;
    int size = end - start;

    Token token = {0};
    token.type = TOKEN_INTEGER;
    token.integerValue = value;
    token.column = lexer->column;
    lexer->column += size;
    token.line = lexer->line;
    token.size = size;

    return token;
}

Token GetNextToken(Lexer *lexer)
{
    Token token = {0};

    while(true)
    {
        char character = GetNextCharacter(lexer);

        if(IsNumeric(character))
        {
            token = ParseInteger(lexer);
            break;
        }
        else if(character == '+')
        {
            token.type = TOKEN_PLUS;
            token.column = lexer->column++;
            token.line = lexer->line;
            token.size = 1;
            break;
        }
        else if(character == '-')
        {
            token.type = TOKEN_MINUS;
            token.column = lexer->column++;
            token.line = lexer->line;
            token.size = 1;
            break;                
        }
        else if(character == '*')
        {
            token.type = TOKEN_MUL;
            token.column = lexer->column++;
            token.line = lexer->line;
            token.size = 1;
            break;
        }
        else if(character == '(')
        {
            token.type = TOKEN_OPEN_BRACKET;
            token.column = lexer->column++;
            token.line = lexer->line;
            token.size = 1;
            break;
        }
        else if(character == ')')
        {
            token.type = TOKEN_CLOSE_BRACKET;
            token.column = lexer->column++;
            token.line = lexer->line;
            token.size = 1;
            break;
        }
        else if(character == '\n')
        {
            lexer->line++;
            lexer->column = 0;
            continue;
        }
        else if(character == 0)
        {
            token.type = TOKEN_STOP;
            token.column = lexer->column++;
            token.line = lexer->line;
            token.size = 1;
            break; 
        }
        lexer->column++;
    }

    return token;
}

void PrintTokenInfo(Token token)
{
    printf("type: %s, int value: %d, line: %d, col: %d, size: %d\n", TokenStr(token.type), token.integerValue, token.line, token.column, token.size);
}
