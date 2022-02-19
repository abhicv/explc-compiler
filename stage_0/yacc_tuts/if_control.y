%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>

    int nest_level = 0;
%}

%token DIGIT IF
%left '+'
%left '*'

%%
start: statement '\n' {exit(1);}
    ;

statement: '{' statement '}'
    | expr
    | IF '(' expr ')' statement {printf("nest level: %d\n", nest_level++);}
    | %empty
    ;

expr: expr '+' expr     {;}
    | expr '*' expr     {;}
    | '(' expr ')'
    | DIGIT             {;}
    ;

%%

int yyerror(char const *s)
{
    printf("yyerror %s", s);
}

int yylex()
{
    char c;
    c = getchar();
    if(isdigit(c)){
        yylval = c - '0';
        return DIGIT;
    }
    else if(c == 'i')
    {
        c = getchar();
        if(c == 'f')
        {
            return IF;
        }
    }
    else if(c == ' '){
        yylex();         /*This is to ignore whitespaces in the input*/
    }
    else {
        return c;
    }
}

int main()
{
    yyparse();

    return 1;
}