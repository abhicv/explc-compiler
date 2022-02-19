/* Declarations */
%{
	#include <stdio.h>
	#include <stdlib.h>

	unsigned int singleLineCommentCount = 0;
	unsigned int multiLineCommentCount = 0;    
%}

%%
"//".* { singleLineCommentCount++;}
"/*"([^*]|\*+[^*/])*\*+"/" {multiLineCommentCount++;}
[aA][a-zA-Z]{2}[\n] {printf("found 3 letter word %s", yytext);}
\n {;}
. {;}
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

    printf("single line: %u, multi line: %u\n", singleLineCommentCount, multiLineCommentCount);
    
    return 0;
}

int yywrap()
{
    return 1;
}

