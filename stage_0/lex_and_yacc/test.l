%{
    #include <stdio.h> 
	#include "y.tab.h"
%}

%%

[0-9]+	{
          yylval.intVal = atoi(yytext);
          return DIGIT;
}
[+|-|*|/]   return *yytext;
.	        return *yytext;
[\n]        return *yytext;

%%

int yywrap()
{
	return 1;
}