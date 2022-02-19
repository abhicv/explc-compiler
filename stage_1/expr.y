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

program : expr END { 
        printf("Answer: %d\n", Evaluate($1));

        FILE *output = fopen("out.xsm", "w");
        if(output)
        {
            fprintf(output, "0\n2056\n0\n0\n0\n0\n0\n0\n");
            int reg = GenerateCode($1, output);
            fprintf(output, "MOV SP, 4095\n");
            fprintf(output, "PUSH R%d\n", reg);
            fprintf(output, "BRKP\n");
            fprintf(output, "INT 10\n");   
        }
        exit(1);
    }
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