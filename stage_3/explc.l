%{
    #include <stdio.h> 
	#include "y.tab.h"
    #include "ast.h"

    extern int yyerror(char const *);
%}

%option yylineno

%%

"+"         { return PLUS; } 
"-"         { return MINUS; } 
"*"         { return MUL; } 
"/"         { return DIV; } 
"="         { return EQ; }
"<"         { return LT; }
"<="        { return LT_EQ; }
">"         { return GT; }
">="        { return GT_EQ; }
"=="        { return EQUAL_EQ; }
"!="        { return NOT_EQ; }

"begin"     { return BEGIN_TOKEN; }
"end"       { return END_TOKEN; }

"read"      { return READ_TOKEN; }
"write"     { return WRITE_TOKEN; }

"if"        { return IF; }
"then"      { return THEN; }
"endif"     { return ENDIF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"do"        { return DO; }
"endwhile"  { return ENDWHILE; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }

[a-z]  {
    yylval.astNode = CreateASTNode(0, strdup(yytext), IDENTIFIER_NODE, INTEGER_TYPE, 0, 0);
    return IDENTIFIER;
}

[-?0-9]+  {
    yylval.astNode = CreateASTNode(atoi(yytext), 0, INTEGER_NODE, INTEGER_TYPE, 0, 0);
    return INTEGER;
}

[();]           { return *yytext; }
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
