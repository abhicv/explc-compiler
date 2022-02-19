%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "ast.h"
    #include "ast.c"

    #include "c_backend/gen_c_code.c"

    int yyerror(char const *s);
    extern int yylex();
    extern FILE *yyin;
    extern int yylineno;

    int compilerMode = 3;
%}

%union {
    struct ASTNode *astNode;
};

%token INTEGER IDENTIFIER
%token BEGIN_TOKEN END_TOKEN
%token READ_TOKEN WRITE_TOKEN
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token BREAK CONTINUE
%token LT GT LT_EQ GT_EQ EQUAL_EQ NOT_EQ EQ
%token PLUS MINUS MUL DIV

%type<astNode> program statement stmt_list input_stmt output_stmt assign_stmt if_stmt while_stmt break_stmt continue_stmt expr INTEGER IDENTIFIER BREAK CONTINUE

%left EQ
%left LT LT_EQ
%left GT GT_EQ
%left EQUAL_EQ NOT_EQ
%left PLUS MINUS
%left MUL DIV

%%

program : BEGIN_TOKEN stmt_list END_TOKEN {
        $$ = $2;

        //C_backend($2);

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
                printf("[ERROR] Failed to create output file!\n");
            }

            printf("[INFO] Compilation finished, output file -> '%s'\n", outFile);
        }
        exit(1);
    }
    | BEGIN_TOKEN END_TOKEN { exit(1); }
    ;

stmt_list: stmt_list statement { $$ = CreateASTNode(0, 0, CONNECTOR_NODE, 0, $1, $2); }
    | statement { $$ = $1; }
    ;

statement: input_stmt   { $$ = $1; }
    | output_stmt       { $$ = $1; }
    | assign_stmt       { $$ = $1; }
    | if_stmt           { $$ = $1; }
    | while_stmt        { $$ = $1; }
    | break_stmt        { $$ = $1; }
    | continue_stmt     { $$ = $1; }
    ;

input_stmt: READ_TOKEN '(' IDENTIFIER ')' ';' { $$ = CreateASTNode(0, 0, READ_NODE, 0, $3, 0); }
    ;

output_stmt: WRITE_TOKEN '(' expr ')' ';' { $$ = CreateASTNode(0, 0, WRITE_NODE, 0, $3, 0); }
    ;

assign_stmt: IDENTIFIER EQ expr ';' { $$ = CreateASTNode(0, 0, EQ_OP_NODE, INTEGER_TYPE, $1, $3); }
    ;

if_stmt: IF '(' expr ')' THEN stmt_list ELSE stmt_list ENDIF ';' {
        struct ASTNode *branch = CreateASTNode(0, 0, BRANCH_NODE, 0, $6, $8);
        $$ = CreateASTNode(0, 0, IF_NODE, 0, $3, branch);
    }
    | IF '(' expr ')' THEN stmt_list ENDIF ';' { $$ = CreateASTNode(0, 0, IF_NODE, 0, $3, $6); }
    ;

while_stmt: WHILE '(' expr ')' DO stmt_list ENDWHILE ';' { $$ = CreateASTNode(0, 0, WHILE_NODE, 0, $3, $6); }
    ;

break_stmt: BREAK ';' { $$ = CreateASTNode(0, 0, BREAK_NODE, 0, 0, 0); }

continue_stmt: CONTINUE ';' { $$ = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }

expr: expr PLUS expr        { $$ = CreateASTNode(0, 0, PLUS_OP_NODE, INTEGER_TYPE, $1, $3); }
	| expr MINUS expr       { $$ = CreateASTNode(0, 0, MINUS_OP_NODE, INTEGER_TYPE, $1, $3); }
    | expr MUL expr         { $$ = CreateASTNode(0, 0, MUL_OP_NODE, INTEGER_TYPE, $1, $3); }
    | expr DIV expr         { $$ = CreateASTNode(0, 0, DIV_OP_NODE, INTEGER_TYPE, $1, $3); }
    | expr LT expr          { $$ = CreateASTNode(0, 0, LT_OP_NODE, BOOLEAN_TYPE, $1, $3); }
    | expr LT_EQ expr       { $$ = CreateASTNode(0, 0, LT_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3); }
    | expr GT expr          { $$ = CreateASTNode(0, 0, GT_OP_NODE, BOOLEAN_TYPE, $1, $3); }
    | expr GT_EQ expr       { $$ = CreateASTNode(0, 0, GT_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3); }
    | expr EQUAL_EQ expr    { $$ = CreateASTNode(0, 0, EQUAL_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3); }
    | expr NOT_EQ expr      { $$ = CreateASTNode(0, 0, NOT_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3); }
    | '(' expr ')'          { $$ = $2; }
    | IDENTIFIER            { $$ = $1; }
    | INTEGER               { $$ = $1; }
    ;

%%

int yyerror(char const *s)
{
    printf("[ERROR] line:%d -> %s\n", yylineno-1, s);
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
    else
    {
        Usage();
    }

    return 1;
}
