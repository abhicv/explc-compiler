%{
    #include <stdio.h> 
	#include "y.tab.h"
    #include "exptree.h"
%}

%%

[0-9]+  {
        yylval.n = MakeLeafNode(atoi(yytext));
        return INTEGER;
}
"+"     { return PLUS; } 
"-"     { return MINUS; } 
"*"     { return MUL; } 
"/"     { return DIV; } 
[\n]    { return END; }
[()]    { return *yytext; }
.	    { yyerror("unknown character %c\n", *yytext); exit(1);}

%%

int yywrap()
{
	return 1;
}