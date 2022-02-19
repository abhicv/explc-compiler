/* Declarations */
%{
	#include <stdio.h>
	#include <stdlib.h>
%}

number [0-9]+
op [-|+|*|/|^|=]
string [(a-zA-Z)]+

/* rules */
%%

{number} {
    int number = atoi(yytext);
    if(number % 2 == 0) 
    {
        printf("number found = %d is an even number\n", number);
    }
    else
    {
        printf("number found = %d is an odd number\n", number);
    }
}

{op}  {printf("operator found = %s\n", yytext);}

{string} {printf("string found = %s with length = %d\n", yytext, yyleng);}

%%

int main(int argc, char *argv[]) 
{
    if(argc > 1)
    {
        FILE *inputFile = fopen(argv[1], "r");
        if(inputFile)
        {
            yyin = inputFile;
            printf("file inputed\n");
        }
    }
    
    yylex();

    return 1;
}

int yywrap()
{
    return 1;
}
