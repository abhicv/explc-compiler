%{
    #include <stdio.h>
    #include <stdlib.h>

    int yyerror();
    extern int yylex();
    extern FILE *yyin;
%}

%union
{
    int intVal;
};

%token DIGIT
%type<intVal> DIGIT

%left '+' '-'
%left '*' '/'

%%

start : expr '\n' { printf("Eval: %d\n", $<intVal>1);}
    | start expr  { printf("Eval: %d\n", $<intVal>2);}
    ;

expr: expr '+' expr     { $<intVal>$ = $<intVal>1 + $<intVal>3; }
    | expr '-' expr     { $<intVal>$ = $<intVal>1 - $<intVal>3; }
    | expr '*' expr     { $<intVal>$ = $<intVal>1 * $<intVal>3; }
    | expr '/' expr     { $<intVal>$ = $<intVal>1 / $<intVal>3; }
    | '(' expr ')'      { $<intVal>$ = $<intVal>2; }
    | DIGIT             { $<intVal>$ = $<intVal>1; }
    ;

%%

int yyerror(char const *s)
{
    printf("yyerror: %s\n",s);
    return 1;
}

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

    yyparse();
    return 1;
}