%{
    #include <stdio.h> 
	#include "y.tab.h"
    #include "ast.h"

    extern int yyerror(char const *);
%}

%%

"+"     { return PLUS; } 
"-"     { return MINUS; } 
"*"     { return MUL; } 
"/"     { return DIV; } 

"begin" { return BEGIN_TOKEN; }
"end"   { return END_TOKEN; }
"read"  { return READ_TOKEN; }
"write" { return WRITE_TOKEN;}

[a-z]  {
    yylval.astNode = CreateASTNode(0, 0, strdup(yytext), IDENTIFIER_NODE, 0, 0,0);
    return IDENTIFIER;
}

[-?0-9]+  {
    yylval.astNode = CreateASTNode(atoi(yytext), 0, 0, INTEGER_NODE, INTEGER_TYPE, 0, 0);
    return INTEGER;
}

[=();]          { return *yytext; }
"//"[^\r\n]*    { ; }
"\n"            { ; }
" "             { ; }
"\t"            { ; }
.	            { yyerror("unknown character found"); exit(1);}

%%

int yywrap()
{
	return 1;
}
