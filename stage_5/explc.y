%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    
    #include "ast.h"
    #include "ast.c"
    
    #include "eval.c"
    #include "symbol.c"

    //#include "backends/gen_c_code.c"
    // #include "backends/gen_asm_x86.c"

    extern int yylex();
    extern FILE *yyin;
    extern int yylineno;
    extern char *yytext;
    int yyerror(char const *s);

    extern int line;

    FILE *output = 0;
    int compilerMode = 3;
    int type = 0;
    bool entryPointFound = false;

    int functionLabelCounter = 0;
    extern struct GlobalSymbolTable globalSymbolTable;
    extern struct LocalSymbolTable localSymbolTable;
    extern int returnType;

    struct ASTNode *GetRightIfNode(struct ASTNode *node);
    void Compile(struct ASTNode *node);
%}

%union {
    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct ASTNodeList *nodeList;
    int type;
};

%token INTEGER_LITERAL STRING_LITERAL IDENTIFIER
%token INT STR
%token DECL ENDDECL
%token BEGIN_TOKEN END_TOKEN
%token READ_TOKEN WRITE_TOKEN
%token IF THEN ELSE ELIF ENDIF
%token WHILE DO ENDWHILE
%token BREAK CONTINUE
%token RETURN
%token AND OR
%token LT GT LT_EQ GT_EQ EQUAL_EQ NOT_EQ EQ
%token PLUS MINUS MUL DIV MOD
%token ADDR_OF

%type<astNode> statement stmt_list read_stmt write_stmt assign_stmt if_stmt while_stmt break_stmt continue_stmt expr INTEGER_LITERAL STRING_LITERAL IDENTIFIER BREAK CONTINUE l_value function_body return_stmt elif_stmt elif_stmt_list
%type<globalSymbolTable> global_id_list global_id
%type<localSymbolTable> local_id_list local_id local_decl local_decl_block local_decl_list
%type<paramList> param_list param
%type<nodeList> arg_list
%type<type> TYPE

%left EQ
%left AND OR
%left EQUAL_EQ NOT_EQ
%left LT LT_EQ GT GT_EQ
%left PLUS MINUS
%left MUL DIV MOD
%right ADDR_OF
%%

program : global_decl_block function_def_block {

        if(globalSymbolTable.size > 0)
        {
            printf("Global Symbol Table: \n");
            PrintGlobalSymbolTable(globalSymbolTable);
            fprintf(output, "$%d\n", globalSymbolTable.staticAddressOffset);
        }

        if(!entryPointFound)
        {
            printf("[WARNING] no definition of function 'main'\n");
        }
    }
    ;

stmt_list: stmt_list statement { $$ = CreateASTNode(0, 0, CONNECTOR_NODE, 0, $1, $2); }
    | statement                { $$ = $1; }
    ;

statement: read_stmt  { $$ = $1; }
    | write_stmt      { $$ = $1; }
    | assign_stmt     { $$ = $1; }
    | if_stmt         { $$ = $1; }
    | while_stmt      { $$ = $1; }
    | break_stmt      { $$ = $1; }
    | continue_stmt   { $$ = $1; }
    | return_stmt     { $$ = $1; }
    | expr ';'        { $$ = $1; }
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

if_stmt: IF '(' expr ')' THEN stmt_list elif_stmt_list ENDIF ';' { 
        $$ = CreateASTNode(0, 0, IF_NODE, 0, $3, $6);
        $7->left = $6; 
        $$->right = $7;
    }
    | IF '(' expr ')' THEN stmt_list elif_stmt_list ELSE stmt_list ENDIF ';' { 
        $$ = CreateASTNode(0, 0, IF_NODE, 0, $3, $6);
        struct ASTNode *ifNode = GetRightIfNode($7);
        ifNode->right = CreateASTNode(0, 0, BRANCH_NODE, 0, ifNode->right, $9);
        $7->left = $6; 
        $$->right = $7;
    }
    | IF '(' expr ')' THEN stmt_list ELSE stmt_list ENDIF ';' {
        struct ASTNode *branch = CreateASTNode(0, 0, BRANCH_NODE, 0, $6, $8);
        $$ = CreateASTNode(0, 0, IF_NODE, 0, $3, branch);
    }
    | IF '(' expr ')' THEN stmt_list ENDIF ';' { $$ = CreateASTNode(0, 0, IF_NODE, 0, $3, $6); }
    ;

elif_stmt_list: elif_stmt_list elif_stmt {
        struct ASTNode *ifNode = GetRightIfNode($1);
        $2->left = ifNode->right; 
        ifNode->right = $2; 
        $$ = $1;
    }
    | elif_stmt { $$ = $1; }
    ;

elif_stmt: ELIF '(' expr ')' THEN stmt_list { 
        struct ASTNode *ifNode = CreateASTNode(0, 0, IF_NODE, 0, $3, $6);
        $$ = CreateASTNode(0, 0, BRANCH_NODE, 0, 0, ifNode); 
    }
    ;

while_stmt: WHILE '(' expr ')' DO stmt_list ENDWHILE ';' { $$ = CreateASTNode(0, 0, WHILE_NODE, 0, $3, $6); }
    ;

break_stmt: BREAK ';' { $$ = CreateASTNode(0, 0, BREAK_NODE, 0, 0, 0); }
    ;

continue_stmt: CONTINUE ';' { $$ = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }
    ;

return_stmt: RETURN expr ';' { $$ = CreateASTNode(0, 0, RETURN_NODE, 0, $2, 0); }
    ;

TYPE: INT { $$ = INTEGER_TYPE; }
    | STR { $$ = STRING_TYPE; }
    ;

global_decl_block: DECL global_decl_list ENDDECL 
    | DECL ENDDECL

global_decl_list: global_decl_list global_decl
    | global_decl
    ;

global_decl: TYPE global_id_list ';' { 
        for(int n = 0; n < $2->size; n++)
        {
            struct GlobalSymbol symbol = $2->symbols[n];
            symbol.type += $1;
            InstallGlobalSymbol(&globalSymbolTable, symbol.name, symbol.type, symbol.size);
            symbol.binding = globalSymbolTable.symbols[globalSymbolTable.size - 1].binding;
            globalSymbolTable.symbols[globalSymbolTable.size - 1] = symbol;
        }
    }
    ;

global_id_list: global_id_list ',' global_id {
        struct GlobalSymbol symbol = $3->symbols[0];
        InstallGlobalSymbol($1, symbol.name, symbol.type, symbol.size);
        $1->symbols[$1->size - 1] = symbol;
        free($3->symbols);
        free($3);
        $$ = $1;
    }
    | global_id { $$ = $1; }
    ;

global_id: IDENTIFIER  {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        InstallGlobalSymbol($$, $1->varName, 0, 1);
        $$->symbols[0].colSize = 0;
        $$->symbols[0].arrayDim = 0;
        $$->symbols[0].functionLabel = -1;
    }
    | IDENTIFIER '[' INTEGER_LITERAL ']' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        InstallGlobalSymbol($$, $1->varName, 0, $3->val);
        $$->symbols[0].colSize = 0;
        $$->symbols[0].arrayDim = 1;
        $$->symbols[0].functionLabel = -1;
    }
    | IDENTIFIER '[' INTEGER_LITERAL ']' '[' INTEGER_LITERAL ']' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        InstallGlobalSymbol($$, $1->varName, 0, $3->val * $6->val);
        $$->symbols[0].colSize = $6->val;
        $$->symbols[0].arrayDim = 2;
        $$->symbols[0].functionLabel = -1;
    }
    | MUL global_id  {
        $2->symbols[0].type = 2;
        $$ = $2;
    }
    | IDENTIFIER '(' param_list ')' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        InstallGlobalSymbol($$, $1->varName, 0, 0);
        $$->symbols[0].functionLabel = functionLabelCounter++;
        $$->symbols[0].paramList = $3;
    }
    ;

function_def_block: function_def_block function_def
    | function_def
    ;

function_def: TYPE IDENTIFIER '(' param_list ')' '{' local_decl_block function_body '}' {

        struct GlobalSymbol *symbol = 0;

        if(!strcmp("main\0", $2->varName))
        {
            if(entryPointFound)
            {
                printf("[ERROR] redefinition of 'int main()' !\n");
                exit(1);
            }

            if($1 != INTEGER_TYPE)
            {
                printf("[ERROR] function 'main' must return 'int' !\n");
                exit(1);
            }

            if($4)
            {
                printf("[ERROR] function 'main' takes 0 parameter but found %d parameters!\n", $4->size);
                exit(1);
            }

            entryPointFound = true;
            returnType = INTEGER_TYPE;
        }
        else
        {
            symbol = LookUpGlobalSymbolTable(globalSymbolTable, $2->varName);

            if(!symbol)
            {
                printf("[ERROR] found definition of undeclared function -> '%s' !\n", $2->varName);
                exit(1);
            }

            if(symbol->functionLabel <= -1)
            {
                printf("[ERROR] found definition of undeclared function -> '%s' !\n", $2->varName);
                exit(1);
            }

            if(symbol->type != $1)
            {
                printf("[ERROR] return type conflict in definition and declaration of function -> '%s' !\n", $2->varName);
                exit(1);
            }

            if(symbol->paramList && !$4)
            {
                printf("[ERROR] function ->'%s' has 0 parameter in its definition!\n", $2->varName);
                exit(1);
            }

            if(!symbol->paramList && $4)
            {
                printf("[ERROR] function ->'%s' has 0 parameter in its declaration!\n", $2->varName);
                exit(1);
            }

            if(symbol->paramList && $4)
            {
                if(symbol->paramList->size != $4->size)
                {
                    printf("[ERROR] parameter count different in declaration and definition of function -> '%s' !\n", $2->varName);
                    exit(1);
                }

                for(int n = 0; n < $4->size; n++)
                {
                    if(symbol->paramList->params[n].type != $4->params[n].type)
                    {
                        printf("[ERROR] parameter %d type conflict in declaration and definition of function -> '%s' !\n", n, $2->varName);
                        exit(1);
                    }

                    if (strcmp(symbol->paramList->params[n].name, $4->params[n].name))
                    {
                        printf("[ERROR] parameter %d name conflict in declaration and definition of function -> '%s' !\n", n, $2->varName);
                        exit(1);
                    }
                }
            }
        }
        
        // installing parameters into local symbol table
        if(symbol)
        {
            if(symbol->paramList)
            {
                struct ParamList *paramList = symbol->paramList; 
                for(int n = 0; n < paramList->size; n++)
                {
                    InstallLocalSymbol(&localSymbolTable, paramList->params[n].name, paramList->params[n].type);
                    localSymbolTable.symbols[localSymbolTable.size - 1].binding = -(n + 3);
                }
            }
        }
        
        //installing local variables into local symbol table
        if($7)
        { 
            for(int n = 0; n < $7->size; n++)
            {
                struct LocalSymbol symbol = $7->symbols[n];
                InstallLocalSymbol(&localSymbolTable, symbol.name, symbol.type);
                localSymbolTable.symbols[localSymbolTable.size - 1].binding = n + 1;
            }
        }

        printf("function -> '%s'\n", $2->varName);
        PrintLocalSymbolTable(localSymbolTable);
        
        // semantic analysis
        returnType = $1;
        if($8)
        {
            // PrintAST($8, 0);
            CheckSemantics($8);
        }

        char *funcLabel = (char*)malloc(strlen($2->varName) + 2);
        funcLabel[0] = '#';
        funcLabel[strlen($2->varName) + 1] = 0;
        strcat(funcLabel, $2->varName);       
        fprintf(output, "%s\n", funcLabel);
        free(funcLabel);
        
        fprintf(output, "PUSH BP\n");
        fprintf(output, "MOV BP, SP\n");
        
        // allocating space for local variables in the stack
        if($7)
        {
            fprintf(output, "ADD SP, %d\n", $7->size);
        }

        //generating code for function
        if($8)
        {
            GenerateCode($8, output);
        }

        // adding return statement in case the user forget to put a return 
        fprintf(output, "MOV SP, BP\n");
        fprintf(output, "POP BP\n");
        fprintf(output, "RET\n");
        
        // freeing symbols and resetting local symbol table
        free(localSymbolTable.symbols);
        localSymbolTable.symbols = 0;
        localSymbolTable.size = 0;
        
        // TODO (abhicv): free nodes of function body AST
    }
    ;

param_list: param_list ',' param {
        if($1 && $3) 
        {
            InstallParam($1, $3->params[0].name, $3->params[0].type);
            free($3->params);
            free($3);
        }
        $$ = $1;
    }
    | param  { $$ = $1; }
    | %empty { $$ = 0;  }
    ;

param: TYPE IDENTIFIER {
        $$ = (struct ParamList*)malloc(sizeof(struct ParamList));
        $$->size = 0;
        InstallParam($$, $2->varName, $1);
    }
    | TYPE MUL IDENTIFIER {
        $$ = (struct ParamList*)malloc(sizeof(struct ParamList));
        $$->size = 0;
        InstallParam($$, $3->varName, $1 + 2);
    }
    ;

local_decl_block: DECL local_decl_list ENDDECL { $$ = $2; }
    | DECL ENDDECL { $$ = 0; }
    ;

local_decl_list: local_decl_list local_decl {
        for(int n = 0; n < $2->size; n++)
        {
            struct LocalSymbol symbol = $2->symbols[n];
            InstallLocalSymbol($1, symbol.name, symbol.type);
        }
        free($2->symbols);
        free($2);
    }
    | local_decl { $$ = $1; }
    ;

local_decl: TYPE local_id_list ';' {
        for(int n = 0; n < $2->size; n++)
        {
            $2->symbols[n].type = $1;
        }
        $$ = $2;
    }
    ;

local_id_list: local_id_list ',' local_id {
        struct LocalSymbol symbol = $3->symbols[0];
        InstallLocalSymbol($1, symbol.name, 0);
        free($3->symbols);
        free($3);
        $$ = $1;
    }
    | local_id { $$ = $1; }
    ;

local_id: IDENTIFIER {
        $$ = (struct LocalSymbolTable*)malloc(sizeof(struct LocalSymbolTable));
        $$->size = 0;
        InstallLocalSymbol($$, $1->varName, 0);
    }
    ;

function_body: BEGIN_TOKEN stmt_list END_TOKEN { $$ = $2; }
    | BEGIN_TOKEN END_TOKEN { $$ = 0; }
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
    | expr AND expr       { $$ = CreateASTNode(0, 0, AND_NODE, BOOLEAN_TYPE, $1, $3);          }
    | expr OR expr        { $$ = CreateASTNode(0, 0, OR_NODE, BOOLEAN_TYPE, $1, $3);           }
    | '(' expr ')'        { $$ = $2; }
    | INTEGER_LITERAL     { $$ = $1; }
    | STRING_LITERAL      { $$ = $1; }
    | l_value             { $$ = $1; }
    | ADDR_OF l_value     { $$ = CreateASTNode(0, 0, ADDR_OF_NODE, 0, $2, 0); }
    | IDENTIFIER '(' arg_list ')' { 
        $$ = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, $1, 0); 
        $$->argList = $3->nodes;
        $$->argCount = $3->size;
    }
    | IDENTIFIER '(' ')' { $$ = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, $1, 0); }
    ;

arg_list: arg_list ',' expr  {
        InsertASTNode($1, *$3);
        $$ = $1;
        free($3);
    }
    | expr { 
        $$ = (struct ASTNodeList*)malloc(sizeof(struct ASTNodeList));
        InsertASTNode($$, *$1);
    }

l_value: IDENTIFIER                        { $$ = $1; }
    | IDENTIFIER '[' expr ']'              { $$ = CreateASTNode(0, 0, ARRAY_NODE, 0, $1, $3); }
    | IDENTIFIER '[' expr ']' '[' expr ']' { 
            struct ASTNode *index = CreateASTNode(0, 0, INDEX_NODE, 0, $3, $6); 
            $$ = CreateASTNode(0, 0, ARRAY_NODE, 0, $1, index);
        }
    | MUL expr { $$ = CreateASTNode(0, 0, DEREF_NODE, 0, $2, 0);  }
%%

// gets right most IF node
struct ASTNode *GetRightIfNode(struct ASTNode *node)
{
    if(node->nodeType == BRANCH_NODE)
    {
        return GetRightIfNode(node->right);
    }
    else if(node->nodeType == IF_NODE)
    {
        if(node->right->nodeType == BRANCH_NODE)
        {
            return GetRightIfNode(node->right);
        }
        else
        {
            return node;
        }
    }
    else
    {
        return 0;
    }
}

int yyerror(char const *s)
{
    printf("line:%d -> %s, yytext= '%s'\n", line-1, s, yytext);
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

/* void Compile(struct ASTNode *node)
{
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
} */

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
            
            output = fopen("out.xsm", "w");
            if(output)
            {
                yyparse();
            }
            else
            {
                printf("[ERROR] Failed to create output file!\n");
                exit(1);
            }
            fclose(output);
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