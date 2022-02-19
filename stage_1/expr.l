%{
    #include <stdio.h> 
	#include "y.tab.h"
    #include "exptree.h"
%}

%%

"+"     { return PLUS; } 
"-"     { return MINUS; } 
"*"     { return MUL; } 
"/"     { return DIV; } 
[\n]    { return END; }

[-?0-9]+  {
        yylval.n = MakeLeafNode(atoi(yytext));
        return INTEGER;
}

[()]    { return *yytext; }
" "     { ; }
.	    { printf("unknown character %s\n", yytext); exit(1);}

%%

int yywrap()
{
	return 1;
}
