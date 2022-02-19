%{
    #include <stdio.h>
    #include <stdlib.h>

    int yyerror();
    extern int yylex();
%}

%union
{
    char charVal;
};

%token CHARACTER
%type<charVal> CHARACTER

%left '+' '-'
%left '*' '/'

%%

start : expr '\n' { return 1;}
    ;

expr: expr '+' expr     { printf("%c " , $<charVal>2); }
    | expr '-' expr     { printf("%c " , $<charVal>2); }
    | expr '*' expr     { printf("%c " , $<charVal>2); }
    | expr '/' expr     { printf("%c " , $<charVal>2); }
    | '(' expr ')'
    | CHARACTER         { printf("%c " , $<charVal>1); }
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