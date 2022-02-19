%{
    #include <stdio.h>
    #include <stdlib.h>
	#include "exptree.c"

    int yyerror();
    extern int yylex();
%}

%union
{
    struct Node *n;
};

%token INTEGER PLUS MINUS MUL DIV END
%type<n> expr program INTEGER

%left PLUS MINUS
%left MUL DIV

%%

program : expr END { printf("Answer: %d\n", Evaluate($1)); return 1;}
    ;

expr: expr PLUS expr { $$ = MakeOperatorNode('+', $1, $3); }
    | expr MINUS expr { $$ = MakeOperatorNode('-', $1, $3); }
    | expr MUL expr { $$ = MakeOperatorNode('*', $1, $3); }
    | expr DIV expr { $$ = MakeOperatorNode('/', $1, $3); }
    | '(' expr ')'  { $$ = $2; }
    | INTEGER       { $$ = $1; }
    ;

%%

int yyerror(char const *s)
{
    printf("yyerror: %s\n",s);
    return 1;
}

int main(int argc, char *argv[])
{
    yyparse();
    return 1;
}