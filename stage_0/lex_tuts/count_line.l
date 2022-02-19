/* Declarations */
%{
	#include <stdio.h>
	#include <stdlib.h>

    unsigned int wordCount = 0;
    unsigned int lineCount = 0;
    unsigned int charCount = 0;    
%}

/* rules */
%%
[^\n\t]+ { wordCount++; charCount+= yyleng;}
\n  { lineCount++; }
. { charCount++; }
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

    printf("line count: %u, character count: %u, word count: %u\n", lineCount+1, charCount, wordCount);
    
    return 1;
}

int yywrap()
{
    return 1;
}

