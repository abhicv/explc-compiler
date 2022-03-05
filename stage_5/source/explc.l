%{
    #include <stdio.h> 
    #include "parser.h"
    #include "ast.h"

    int line = 1;
%}

%option yylineno

%%

"+"         { return PLUS; } 
"-"         { return MINUS; } 
"*"         { return MUL; } 
"/"         { return DIV; }
"%"         { return MOD; }
"="         { return EQ; }
"<"         { return LT; }
"<="        { return LT_EQ; }
">"         { return GT; }
">="        { return GT_EQ; }
"=="        { return EQUAL_EQ; }
"!="        { return NOT_EQ; }
"&"         { return ADDR_OF; }

"begin"     { return BEGIN_TOKEN; }
"end"       { return END_TOKEN; }
"decl"      { return DECL; }
"enddecl"   { return ENDDECL; }
"int"       { return INT; }
"str"       { return STR; }
"read"      { return READ_TOKEN; }
"write"     { return WRITE_TOKEN; }
"if"        { return IF; }
"then"      { return THEN; }
"endif"     { return ENDIF; }
"else"      { return ELSE; }
"elif"      { return ELIF; }
"while"     { return WHILE; }
"do"        { return DO; }
"endwhile"  { return ENDWHILE; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"return"    { return RETURN; }
"and"       { return AND; }
"or"        { return OR;  }

[_a-zA-Z][_a-zA-Z0-9]* {
    yylval.astNode = CreateASTNode(0, strdup(yytext), IDENTIFIER_NODE, 0, 0, 0);
    return IDENTIFIER;
}

[0-9]+  {
    yylval.astNode = CreateASTNode(atoi(yytext), 0, INTEGER_NODE, INTEGER_TYPE, 0, 0);
    return INTEGER_LITERAL;
}

\".+\" {
    yylval.astNode = CreateASTNode(0, 0, STRING_NODE, STRING_TYPE, 0, 0);
    int len = strlen(yytext) - 1;
    char *str = (char*)malloc(len);
    strncpy(str, yytext + 1, len);
    str[len - 1] = 0;
    yylval.astNode->strVal = str;
    return STRING_LITERAL;
}

[();,\[\]"\{\}]      { return *yytext; }
"//"[^\r\n]*    { ; }
"\n"            { line++; }
" "             { ; }
"\t"            { ; }
"\r"            { ; }
.               { printf("[ERROR] line %d unknown character found -> '%s'\n", line, yytext); exit(1); }

%%

int yywrap()
{
    return 1;
}