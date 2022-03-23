#include "lexer.h"

Keyword keywordList[] = {
    [0] = {.keywordString = "proc", .len = 4, .tokenType = TOKEN_KEYWORD_PROC},
    [1] = {.keywordString = "struct", .len = 6, .tokenType = TOKEN_KEYWORD_STRUCT},
    [2] = {.keywordString = "if", .len = 2, .tokenType = TOKEN_KEYWORD_IF},
    [3] = {.keywordString = "else", .len = 4, .tokenType = TOKEN_KEYWORD_ELSE},
    [4] = {.keywordString = "while", .len = 5, .tokenType = TOKEN_KEYWORD_WHILE},
    [5] = {.keywordString = "return", .len = 6, .tokenType = TOKEN_KEYWORD_RETURN},
    [6] = {.keywordString = "let", .len = 3, .tokenType = TOKEN_KEYWORD_LET},
};

char GetNextCharacter(Lexer *lexer)
{
    return lexer->source[lexer->pos++];
}

char PeekNextCharacter(Lexer *lexer)
{
    return lexer->source[lexer->pos];
}

char *LoadFileNullTerminated(const char *fileName)
{
    char *data = 0;
    
    FILE *input = fopen(fileName, "r");
    if(input)
    {
        fseek(input, 0, SEEK_END);
        unsigned int size = ftell(input);
        fseek(input, 0, SEEK_SET);

        data = (char*)malloc(size + 1);
        fread(data, 1, size, input);
        data[size] = 0;
        
        fclose(input);
    }
    else
    {
        printf("error: failed to open input file '%s'\n", fileName);
    }

    return data;
}

bool IsNumeralCharacter(char c)
{
    return (c >= '0' && c <= '9');
}

bool IsAlphabetCharacter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool IsIdentifierCharacter(char c)
{
    return IsAlphabetCharacter(c) || (c == '_');
}

bool IsBinaryOperatorCharacter(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '%');
}

Token TokenizeIntegerConstant(Lexer *lexer)
{
    unsigned int start = lexer->pos;

    int value = 0;
    while(true)
    {
        char character = PeekNextCharacter(lexer);
        if(IsNumeralCharacter(character))
        {
            character = GetNextCharacter(lexer);
            value = (value * 10) + (character - '0');
        }
        else 
        {
            break;
        }
    }

    char character = PeekNextCharacter(lexer);
    if(IsIdentifierCharacter(character))
    {
        printf("error:%u:%u an identifier name cannot start with a number\n", lexer->line+1, lexer->column+1);
        exit(1);
    }

    unsigned int end = lexer->pos;

    Token token = {0};
    token.type = TOKEN_INTEGER_CONSTANT;
    token.integerValue = value;
    token.size = end - start;
    token.column = lexer->column;
    token.line = lexer->line;

    return token;
}

Token TokenizeIdentifier(Lexer *lexer)
{
    unsigned int len = 0;

    unsigned int start = lexer->pos;
    
    while(true)
    {
        char character = GetNextCharacter(lexer);
        if(IsIdentifierCharacter(character) || IsNumeralCharacter(character)) len++;
        else break;
    }

    lexer->pos = start + len;

    Token token = {0};
    token.type = TOKEN_IDENTIFIER;
    token.size = len;
    token.column = lexer->column;
    token.line = lexer->line;
    
    token.identifier = (char*)malloc(len + 1);
    strncpy(token.identifier, &lexer->source[start], len);
    token.identifier[len] = 0;

    return token;
}

bool TryTokenizeKeyword(Lexer *lexer, Token *token)
{
    unsigned int len = 0;

    unsigned int start = lexer->pos;

    while(true)
    {
        char character = GetNextCharacter(lexer);
        if(IsAlphabetCharacter(character)) len++;
        else break;
    }

    lexer->pos = start;

    unsigned int keywordListSize = sizeof(keywordList) / sizeof(keywordList[0]);

    bool keywordMatched = false;
    unsigned int index = 0;

    for(unsigned int n = 0; n < keywordListSize; n++)
    {
        if(len == keywordList[n].len)
        {
            if(!strncmp(&lexer->source[start], keywordList[n].keywordString, len))
            {
                keywordMatched = true;
                index = n;
                lexer->pos = start + len;
                break;
            }
        }
    }

    token->column = lexer->column;
    token->line = lexer->line;
    token->size = len;
    token->type = keywordList[index].tokenType;

    return keywordMatched;
}

Token TokenizeBinaryOperator(Lexer *lexer)
{
    Token token = {0};

    char character = GetNextCharacter(lexer);
    
    if(character == '+')
    {
        token.type = TOKEN_PLUS;
    }
    else if(character == '-')
    {
        token.type = TOKEN_MINUS;
    }
    else if(character == '*')
    {
        token.type = TOKEN_MULTIPLY;
    }
    else if(character == '/')
    {
        token.type = TOKEN_DIVIDE;
    }
    else if(character == '%')
    {
        token.type = TOKEN_MODULUS;
    }

    token.column = lexer->column;
    token.line = lexer->line;
    token.size = 1;

    return token;
}

void PushToken(TokenList *tokenList, Token token)
{
    if(tokenList->count == 0)
    {
        tokenList->count++;
        tokenList->tokens = (Token *)malloc(sizeof(Token));
    }
    else
    {
        tokenList->count++;
        tokenList->tokens = (Token *)realloc(tokenList->tokens, sizeof(Token) * tokenList->count);
    }

    tokenList->tokens[tokenList->count - 1] = token;
}

TokenList TokenizeSource(const char *source)
{
    TokenList tokenList = {0};

    Lexer lexer = {0};
    lexer.source = source;

    while(true)
    {
        char character = PeekNextCharacter(&lexer);
        if(IsNumeralCharacter(character))
        {
            Token token = TokenizeIntegerConstant(&lexer);
            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(IsIdentifierCharacter(character))
        {
            Token token = {0};
            bool isKeyword = TryTokenizeKeyword(&lexer, &token);
            if(!isKeyword)
            {
                token = TokenizeIdentifier(&lexer);
            }
            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(IsBinaryOperatorCharacter(character))
        {
            Token token = TokenizeBinaryOperator(&lexer);
            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == '=')
        {
            GetNextCharacter(&lexer);
            Token token = {0};
            token.type = TOKEN_EQUAL;
            token.line = lexer.line;
            token.column = lexer.column;
            token.size = 1;
            
            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == '(')
        {
            GetNextCharacter(&lexer);
            Token token = {0};
            token.type = TOKEN_OPEN_BRACKET;
            token.line = lexer.line;
            token.column = lexer.column;
            token.size = 1;
            
            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == ')')
        {
            GetNextCharacter(&lexer);
            Token token = {0};
            token.type = TOKEN_CLOSE_BRACKET;
            token.line = lexer.line;
            token.column = lexer.column;
            token.size = 1;

            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == '{')
        {
            GetNextCharacter(&lexer);
            Token token = {0};
            token.type = TOKEN_OPEN_CURLY_BRACKET;
            token.line = lexer.line;
            token.column = lexer.column;
            token.size = 1;

            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == '}')
        {
            GetNextCharacter(&lexer);
            Token token = {0};
            token.type = TOKEN_CLOSE_CURLY_BRACKET;
            token.line = lexer.line;
            token.column = lexer.column;
            token.size = 1;

            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == ';')
        {
            GetNextCharacter(&lexer);
            Token token = {0};
            token.type = TOKEN_SEMICOLON;
            token.line = lexer.line;
            token.column = lexer.column;
            token.size = 1;

            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == ',')
        {
            GetNextCharacter(&lexer);
            Token token = {0};
            token.type = TOKEN_COMMA;
            token.line = lexer.line;
            token.column = lexer.column;
            token.size = 1;

            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == ':')
        {

            GetNextCharacter(&lexer);
            character = PeekNextCharacter(&lexer);

            unsigned int column = lexer.column;

            Token token = {0};
            if(character == ':')
            {
                GetNextCharacter(&lexer);
                token.type = TOKEN_DOUBLE_COLON;
                token.line = lexer.line;
                token.column = column;
                token.size = 2;
            }
            else
            {
                token.type = TOKEN_COLON;
                token.line = lexer.line;
                token.column = column;
                token.size = 1;
            }

            lexer.column += token.size;
            PushToken(&tokenList, token);
        }
        else if(character == 0)
        {
            Token token = {0};
            token.type = TOKEN_PROGRAM_END;
            token.column = lexer.column;
            token.line = lexer.line;
            PushToken(&tokenList, token);
            break;
        }
        else if(character == '\n')
        {
            lexer.line++;
            lexer.column = 0;
            GetNextCharacter(&lexer);
        }
        else if(character == ' ')
        {
            lexer.column++;
            GetNextCharacter(&lexer);
        }
        else
        {
            printf("%u:%u: error: unsupported character '%c'\n",  lexer.line + 1, lexer.column + 1, character);
            exit(1);
        }
    }

    return tokenList;
}

char *TokenTypeToString(unsigned int type)
{
    switch(type)
    {
        case TOKEN_INTEGER_CONSTANT:        return "token_integer_constant"; break;
        case TOKEN_IDENTIFIER:              return "token_identifier"; break;
        case TOKEN_PLUS:                    return "token_plus"; break;
        case TOKEN_MINUS:                   return "token_minus"; break;
        case TOKEN_MULTIPLY:                return "token_multiply"; break;
        case TOKEN_DIVIDE:                  return "token_divide"; break;
        case TOKEN_MODULUS:                 return "token_modulus"; break;
        case TOKEN_EQUAL:                   return "token_equal"; break;
        case TOKEN_KEYWORD_PROC:            return "token_keyword_proc"; break;
        case TOKEN_KEYWORD_STRUCT:          return "token_keyword_struct"; break;
        case TOKEN_KEYWORD_IF:              return "token_keyword_if"; break;
        case TOKEN_KEYWORD_ELSE:            return "token_keyword_else"; break;
        case TOKEN_KEYWORD_WHILE:           return "token_keyword_while"; break;
        case TOKEN_KEYWORD_RETURN:          return "token_keyword_return"; break;
        case TOKEN_KEYWORD_LET:             return "token_keyword_let"; break;
        case TOKEN_OPEN_BRACKET:            return "token_open_bracket"; break;
        case TOKEN_CLOSE_BRACKET:           return "token_close_bracket"; break;
        case TOKEN_OPEN_CURLY_BRACKET:      return "token_open_curly_bracket"; break;
        case TOKEN_CLOSE_CURLY_BRACKET:     return "token_close_curly_bracket"; break;
        case TOKEN_DOUBLE_COLON:            return "token_double_colon"; break;
        case TOKEN_COLON:                   return "token_colon"; break;
        case TOKEN_SEMICOLON:               return "token_semicolon"; break;
        case TOKEN_COMMA:                   return "token_comma"; break;
        case TOKEN_PROGRAM_END:             return "token_program_end"; break;
        case TOKEN_COUNT:                   return "token_count"; break;
        default:                            return "unknown_token_type";
    }
}

void PrintTokenInfo(Token token)
{
    printf("%u:%u: type: '%s', size: %u\n", token.line+1, token.column+1, TokenTypeToString(token.type), token.size);
}
