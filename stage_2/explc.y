%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "ast.h"
	#include "ast.c"

    int yyerror(char const *s);
    extern int yylex();
    extern FILE *yyin;

    int compilerMode = 3;
%}

%union {
    struct ASTNode *astNode;
};

%token INTEGER IDENTIFIER
%token BEGIN_TOKEN END_TOKEN READ_TOKEN WRITE_TOKEN
%token PLUS MINUS MUL DIV 

%type<astNode> program statement stmt_list input_stmt output_stmt assign_stmt expr INTEGER IDENTIFIER 
%left PLUS MINUS
%left MUL DIV

%%

program : BEGIN_TOKEN stmt_list END_TOKEN { 
        $$ = $2;
        
        if(compilerMode == 0)
        {
            PrintAST($2, 0);
        }
        else if(compilerMode == 1)
        {
            EvaluateAST($2);
        }
        else if(compilerMode == 2)
        {
            printf("[INFO] Generating XSM machine code...\n");
            
            char *outFile = "out.xsm";
        
            FILE *output = fopen(outFile, "w");
            if(output)
            {
                fprintf(output, "0\n2056\n0\n0\n0\n0\n0\n0\n");
                fprintf(output, "MOV SP, 4121\n");
                GenerateCode($2, output);
                fprintf(output, "BRKP\n");
                fprintf(output, "INT 10\n");
            }
            else
            {
                printf("[ERROR] Failed  to create output file!\n");
            }

            printf("[INF0] Compilation finished, output file -> '%s'\n", outFile);
        }
        exit(1);
    }
    | BEGIN_TOKEN END_TOKEN { exit(1); }
    ;

stmt_list: stmt_list statement { $$ = CreateASTNode(0, 0, 0, CONNECTOR_NODE, 0, $1, $2); } 
    | statement { $$ = $1; }
    ;

statement: input_stmt { $$ = $1; }
    | output_stmt { $$ = $1; }
    | assign_stmt { $$ = $1; }
    ;

input_stmt: READ_TOKEN '(' IDENTIFIER ')' ';' { $$ = CreateASTNode(0, 0, 0, READ_NODE, 0, $3, 0); }
    ;

output_stmt: WRITE_TOKEN '(' expr ')' ';' { $$ = CreateASTNode(0, 0, 0, WRITE_NODE, 0, $3, 0); }
    ;

assign_stmt: IDENTIFIER '=' expr ';' { $$ = CreateASTNode(0, '=', 0, OPERATOR_NODE, 0, $1, $3); }
    ;

expr: expr PLUS expr { $$ = CreateASTNode(0, '+', 0, OPERATOR_NODE, 0, $1, $3); }
	| expr MINUS expr { $$ = CreateASTNode(0, '-', 0, OPERATOR_NODE, 0, $1, $3); }
    | expr MUL expr { $$ = CreateASTNode(0, '*', 0, OPERATOR_NODE, 0, $1, $3); }
    | expr DIV expr { $$ = CreateASTNode(0, '/', 0, OPERATOR_NODE, 0, $1, $3); }
    | '(' expr ')' { $$ = $2; }
    | IDENTIFIER { $$ = $1; }
    | INTEGER { $$ = $1; }
    ;

%%

int yyerror(char const *s)
{
    printf("yyerror: %s\n",s);
    return 1;
}

void Usage()
{
    printf("Usage: ./explc.out [sub-command] [source file]\n");
    printf("[sub-command] :\n");
    printf("    -e: evaluates the AST\n");
    printf("    -c: compiles the source file into XSM code\n");
    printf("    -p: print AST\n");
}

int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        yyin = fopen(argv[2], "r");

        if(yyin)
        {   
            if(!strcmp(argv[1], "-e"))
            {
                compilerMode = 1;
            }
            else if(!strcmp(argv[1], "-c"))
            {
                compilerMode = 2;
            }
            else if(!strcmp(argv[1], "-p"))
            {
                compilerMode = 0;
            }
            else
            {
                Usage();
                return 1;
            }
            yyparse();
        }
        else
        {
            printf("[ERROR] Failed to open source file = '%s' !\n", argv[2]);
            return 1;
        }
    }

    Usage();
    return 1;
}