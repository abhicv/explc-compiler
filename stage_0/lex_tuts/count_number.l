/* Declarations */
%{
	#include <stdio.h>
	#include <stdlib.h>

    unsigned int intCount = 0;
    unsigned int floatCount = 0;    
%}

integer [0-9]*
floating [0-9]*[.][0-9]*

%%
{integer} {intCount++;}
{floating} {floatCount++;}
[(.) | (\n)] {;}
%%

int main(int argc, char *argv[]) 
{
    if(argc > 1)
    {
        FILE *inputFile = fopen(argv[1], "r");
        if(inputFile)
        {
            yyin = inputFile;
        }
    }
    
    yylex();

    printf("integer count: %u, float count: %u\n", intCount, floatCount);
    
    return 1;
}

int yywrap()
{
    return 1;
}

