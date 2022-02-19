%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
%}

%token DIGIT LETTER

%%
start: variable_name '\n' {exit(1);}
    | variable_name ' ' '\n' {exit(1);}
    ;

variable_name: LETTER string
    ;

string: string string
    | LETTER
    | DIGIT
    ;

%%

int yyerror(char const *s)
{
    printf("yyerror %s", s);
}

int yylex()
{
    char c = getchar();

    if(isdigit(c))
    {
        return DIGIT;
    }
    else if(isalpha(c))
    {
        return LETTER;
    }
    
    return c;
}

int main()
{
    yyparse();

    return 1;
}