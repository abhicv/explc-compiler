#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum TokenType
{
    TOKEN_INTEGER_CONSTANT,
    TOKEN_IDENTIFIER,

    // binary operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MODULUS,

    // assignment operator
    TOKEN_EQUAL,

    // keywords
    TOKEN_KEYWORD_PROC,
    TOKEN_KEYWORD_STRUCT,
    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_WHILE,
    TOKEN_KEYWORD_LET,
    TOKEN_KEYWORD_RETURN,

    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_OPEN_CURLY_BRACKET,
    TOKEN_CLOSE_CURLY_BRACKET,
    TOKEN_DOUBLE_COLON,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,

    TOKEN_PROGRAM_END,
    TOKEN_COUNT,
};

typedef struct Keyword Keyword;
struct Keyword
{
    char *keywordString;
    unsigned int len;
    unsigned int tokenType;
};

typedef struct Token Token;
struct Token
{
    int type;
    int size;
    int integerValue;
    char *identifier;
    int column;
    int line;
};

typedef struct Lexer Lexer;
struct Lexer
{
    const char *source;
    unsigned int pos;
    unsigned int line;
    unsigned int column;
};

typedef struct TokenList TokenList;
struct TokenList
{
    Token *tokens;
    unsigned int count;
};

#endif