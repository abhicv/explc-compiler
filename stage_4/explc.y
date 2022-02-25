%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "ast.h"
    #include "ast.c"
    
    #include "eval.c"
    #include "symbol.c"

    //#include "backends/gen_c_code.c"
    // #include "backends/gen_asm_x86.c"

    extern int yylex();
    extern FILE *yyin;
    extern int yylineno;
    int yyerror(char const *s);

    extern int line;

    int compilerMode = 3;
    int type = 0;

    extern struct GlobalSymbolTable globalSymbolTable;

    void Compile(struct ASTNode *node);
%}

%union {
    struct ASTNode *astNode;
    struct GlobalSymbolTable *table;
};

%token INTEGER_LITERAL STRING_LITERAL IDENTIFIER
%token INT STR
%token DECL ENDDECL
%token BEGIN_TOKEN END_TOKEN
%token READ_TOKEN WRITE_TOKEN
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token BREAK CONTINUE
%token LT GT LT_EQ GT_EQ EQUAL_EQ NOT_EQ EQ
%token PLUS MINUS MUL DIV MOD
%token ADDR_OF

%type<astNode> program statement stmt_list read_stmt write_stmt assign_stmt if_stmt while_stmt break_stmt continue_stmt expr INTEGER_LITERAL STRING_LITERAL IDENTIFIER BREAK CONTINUE l_value
%type<table> var_decl var_list

%left EQ
%left LT LT_EQ
%left GT GT_EQ
%left EQUAL_EQ NOT_EQ
%left PLUS MINUS
%left MUL DIV MOD
%right ADDR_OF
%%

program : BEGIN_TOKEN decl_block stmt_list END_TOKEN {
        $$ = $3;
        Compile($3);
    }
    | BEGIN_TOKEN END_TOKEN { exit(1); }
    ;

stmt_list: stmt_list statement  { $$ = CreateASTNode(0, 0, CONNECTOR_NODE, 0, $1, $2); }
    | statement                 { $$ = $1; }
    ;

statement: read_stmt    { $$ = $1; }
    | write_stmt        { $$ = $1; }
    | assign_stmt       { $$ = $1; }
    | if_stmt           { $$ = $1; }
    | while_stmt        { $$ = $1; }
    | break_stmt        { $$ = $1; }
    | continue_stmt     { $$ = $1; }
    ;

read_stmt: READ_TOKEN '(' ADDR_OF l_value ')' ';' { 
        struct ASTNode *addrNode = CreateASTNode(0, 0, ADDR_OF_NODE, 0, $4, 0);
        $$ = CreateASTNode(0, 0, READ_NODE, 0, addrNode, 0);
    }
    | READ_TOKEN '(' IDENTIFIER ')' ';' {
        $$ = CreateASTNode(0, 0, READ_NODE, 0, $3, 0);
    }
    ;

write_stmt: WRITE_TOKEN '(' expr ')' ';' { $$ = CreateASTNode(0, 0, WRITE_NODE, 0, $3, 0); }
    ;

assign_stmt: l_value EQ expr ';' { $$ = CreateASTNode(0, 0, EQ_OP_NODE, 0, $1, $3); }
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
    ;

continue_stmt: CONTINUE ';' { $$ = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }
    ;

decl_block: DECL decl_list ENDDECL { ; } 
    | DECL ENDDECL                 { ; }
    ;

decl_list: decl_list declaration { ; }
    | declaration                { ; }
    ;

declaration: INT var_list ';' { 
        for(int n = 0; n < $2->size; n++)
        {
            struct GlobalSymbol symbol = $2->symbols[n];
            InstallGlobalSymbol(&globalSymbolTable, symbol.name, symbol.type + INTEGER_TYPE, symbol.size);
            globalSymbolTable.symbols[globalSymbolTable.size - 1].colSize = $2->symbols[n].colSize;
            globalSymbolTable.symbols[globalSymbolTable.size - 1].arrayDim = $2->symbols[n].arrayDim;
        }
    }
    | STR var_list ';' {  
        for(int n = 0; n < $2->size; n++)
        {
            struct GlobalSymbol symbol = $2->symbols[n];
            InstallGlobalSymbol(&globalSymbolTable, symbol.name, symbol.type + STRING_TYPE, symbol.size);
            globalSymbolTable.symbols[globalSymbolTable.size - 1].colSize = $2->symbols[n].colSize;
            globalSymbolTable.symbols[globalSymbolTable.size - 1].arrayDim = $2->symbols[n].arrayDim;
        }
    }
    ;

var_list: var_list ',' var_decl {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        for(int n = 0; n < $1->size; n++)
        {
            struct GlobalSymbol symbol = $1->symbols[n];
            InstallGlobalSymbol($$, symbol.name, symbol.type, symbol.size);
            $$->symbols[$$->size - 1].colSize = $1->symbols[n].colSize;
            $$->symbols[$$->size - 1].arrayDim = $1->symbols[n].arrayDim;
        }
        struct GlobalSymbol symbol = $3->symbols[0];
        InstallGlobalSymbol($$, symbol.name, symbol.type, symbol.size);
        $$->symbols[$$->size - 1].colSize = $3->symbols[0].colSize;
        $$->symbols[$$->size - 1].arrayDim = $3->symbols[0].arrayDim;
        free($1);
        free($3);
    }
    | var_decl { $$ = $1; }

var_decl: IDENTIFIER  {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        InstallGlobalSymbol($$, $1->varName, 0, 1);
        $$->symbols[0].colSize = 0;
        $$->symbols[0].arrayDim = 0;
    }
    | IDENTIFIER '[' INTEGER_LITERAL ']' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        InstallGlobalSymbol($$, $1->varName, 0, $3->val);
        $$->symbols[0].colSize = 0;
        $$->symbols[0].arrayDim = 1;
    }
    | IDENTIFIER '[' INTEGER_LITERAL ']' '[' INTEGER_LITERAL ']' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        InstallGlobalSymbol($$, $1->varName, 0, $3->val * $6->val);
        $$->symbols[0].colSize = $6->val;
        $$->symbols[0].arrayDim = 2;
    }
    | MUL var_decl  {
        $2->symbols[0].type = 2;
        $$ = $2;
    }
    ;

expr: expr PLUS expr      { $$ = CreateASTNode(0, 0, PLUS_OP_NODE, INTEGER_TYPE, $1, $3);      }
	| expr MINUS expr     { $$ = CreateASTNode(0, 0, MINUS_OP_NODE, INTEGER_TYPE, $1, $3);     }
    | expr MUL expr       { $$ = CreateASTNode(0, 0, MUL_OP_NODE, INTEGER_TYPE, $1, $3);       }
    | expr DIV expr       { $$ = CreateASTNode(0, 0, DIV_OP_NODE, INTEGER_TYPE, $1, $3);       }
    | expr MOD expr       { $$ = CreateASTNode(0, 0, MOD_OP_NODE, INTEGER_TYPE, $1, $3);       }
    | expr LT expr        { $$ = CreateASTNode(0, 0, LT_OP_NODE, BOOLEAN_TYPE, $1, $3);        }
    | expr LT_EQ expr     { $$ = CreateASTNode(0, 0, LT_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3);     }
    | expr GT expr        { $$ = CreateASTNode(0, 0, GT_OP_NODE, BOOLEAN_TYPE, $1, $3);        }
    | expr GT_EQ expr     { $$ = CreateASTNode(0, 0, GT_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3);     }
    | expr EQUAL_EQ expr  { $$ = CreateASTNode(0, 0, EQUAL_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3);  }
    | expr NOT_EQ expr    { $$ = CreateASTNode(0, 0, NOT_EQ_OP_NODE, BOOLEAN_TYPE, $1, $3);    }
    | '(' expr ')'        { $$ = $2; }
    | INTEGER_LITERAL     { $$ = $1; }
    | STRING_LITERAL      { $$ = $1; }
    | l_value             { $$ = $1; }
    | ADDR_OF l_value     { $$ = CreateASTNode(0, 0, ADDR_OF_NODE, 0, $2, 0); }
    ;

l_value: IDENTIFIER                        { $$ = $1; }
    | IDENTIFIER '[' expr ']'              { $$ = CreateASTNode(0, 0, ARRAY_NODE, 0, $1, $3); }
    | IDENTIFIER '[' expr ']' '[' expr ']' { 
            struct ASTNode *index = CreateASTNode(0, 0, INDEX_NODE, 0, $3, $6); 
            $$ = CreateASTNode(0, 0, ARRAY_NODE, 0, $1, index);
        }
    | MUL expr { $$ = CreateASTNode(0, 0, DEREF_NODE, 0, $2, 0);  }
%%

int yyerror(char const *s)
{
    printf("[ERROR] line:%d -> %s\n", line-1, s);
    return 1;
}

void PrintUsage()
{
    printf("Usage: ./explc.out [sub-command] [source file]\n");
    printf("[sub-command] :\n");
    printf("    -e: evaluates the AST\n");
    printf("    -c: compiles the source file into XSM code\n");
    printf("    -p: print AST\n");
}

void Compile(struct ASTNode *node)
{
    CheckSemantics(node);
    if(compilerMode == 0)
    {
        PrintGlobalSymbolTable(globalSymbolTable);
        PrintAST(node, 0);
    }
    else if(compilerMode == 1)
    {
        EvaluateAST(node);
    }
    else if(compilerMode == 2)
    {
        printf("[INFO] Generating XSM machine code ...\n");

        char *outFile = "out.xsm";

        FILE *output = fopen(outFile, "w");
        if(output)
        {
            fprintf(output, "0\n2056\n0\n0\n0\n0\n0\n0\n");
            fprintf(output, "MOV SP, %d\n", 4096 + globalSymbolTable.staticAddressOffset - 1);
            GenerateCode(node, output);
            fprintf(output, "BRKP\n");
            fprintf(output, "INT 10\n");
        }
        else
        {
            printf("[ERROR] Failed to create output file!\n");
            exit(1);
        }
        fclose(output);

        printf("[INFO] Compilation finished, output file -> '%s'\n", outFile);
    }
    exit(1);
}

int main(int argc, char *argv[]) 
{
    if(argc > 2)
    {
        yyin = fopen(argv[2], "r");

        if(yyin)
        {
            if(!strcmp(argv[1], "-p")) 
            {
                compilerMode = 0;
            }
            else if(!strcmp(argv[1], "-e"))
            {
                compilerMode = 1;
            }
            else if(!strcmp(argv[1], "-c"))
            {
                compilerMode = 2;
            }
            else
            {
                PrintUsage();
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
        PrintUsage();
    }
    return 1;
}
