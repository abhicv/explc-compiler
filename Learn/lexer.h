#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum TOKEN
{
    TOKEN_INTEGER = 0,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_STOP,
};

typedef struct Token
{
    int type;

    char *lexeme;

    int integerValue;
    char* stringValue;
    
    int column;
    int line;
    int size;
} Token;

typedef struct Lexer
{
    char *data;
    int pos;
    int line;
    int column;
} Lexer;

#endif