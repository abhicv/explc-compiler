%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    #include "ast.h"
    #include "ast.c"
    #include "symbol.c"

    // #include "eval.c"
    // #include "backends/gen_asm_x86.c"
    // #include "backends/gen_c_code.c"

    extern FILE *yyin;
    extern int yylineno;
    extern char *yytext;
    extern int line;
    extern bool entryPointFound;
    extern struct GlobalSymbolTable globalSymbolTable;
    extern struct TypeTable typeTable;

    extern int yylex();
    int yyerror(char const *s);
    struct ASTNode *GetRightIfNode(struct ASTNode *node);
    void Compile(struct ASTNode *node);

    enum CompilerMode
    {
        PRINT_AST,
        COMPILE_FOR_XSM,
        COMPILE_FOR_X86,
        COMPILE_TO_C,
    };

    int compilerMode = COMPILE_FOR_XSM;
    char *inputFileName = 0;
    char *outputFileName = 0;
    int functionLabelCounter = 0;
%}

%union {
    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct FieldList *fieldList;
    struct ASTNodeList *nodeList;
    unsigned int type;
};

%token INTEGER_LITERAL STRING_LITERAL IDENTIFIER
%token DECL ENDDECL
%token TYPE_TOKEN ENDTYPE_TOKEN
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

%type<astNode> TYPE statement stmt_list read_stmt write_stmt assign_stmt if_stmt elif_stmt elif_stmt_list while_stmt break_stmt continue_stmt expr INTEGER_LITERAL STRING_LITERAL IDENTIFIER BREAK CONTINUE l_value function_body return_stmt function_def function_def_block
%type<globalSymbolTable> global_id_list global_id
%type<localSymbolTable> local_id_list local_id local_decl local_decl_block local_decl_list
%type<paramList> param_list param
%type<nodeList> arg_list
%type<fieldList> field_decl_list field_decl

%left EQ
%left AND OR
%left EQUAL_EQ NOT_EQ
%left LT LT_EQ GT GT_EQ
%left PLUS MINUS
%left MUL DIV MOD
%right ADDR_OF

%%

program: type_def_block global_decl_block function_def_block {
        CheckSemantics($3);
        // Compile($3);
        PrintTypeTable(typeTable);

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
    | global_decl_block function_def_block {
        CheckSemantics($2);
        // Compile($2);

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
    | function_def_block {
        CheckSemantics($1);
        // Compile($1);

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
    ;

TYPE: IDENTIFIER { $$ = $1; }
    ;

type_def_block: TYPE_TOKEN type_def_list ENDTYPE_TOKEN

type_def_list: type_def_list type_def
    | type_def

type_def: IDENTIFIER '{' field_decl_list '}' {
    struct Type type = {0};
    type.name = $1->varName;
    type.size = 0;
    type.fieldList = *($3);

    for(int n = 0; n < $3->count; n++)
    {
        type.size += typeTable.types[$3->fields[n].typeIndex].size;
    }

    InstallType(&typeTable, type);
}

field_decl_list: field_decl_list field_decl {
        InstallField($1, $2->fields[0]);
        free($2->fields);
        free($2);
        $$ = $1;
    }
    | field_decl { $$ = $1; }

field_decl: TYPE IDENTIFIER ';' {
    $$ = (struct FieldList*)malloc(sizeof(struct FieldList));
    $$->count = 0;

    struct Field field = {0};
    field.name = $2->varName;
    field.typeIndex = LookUpTypeTableIndex(typeTable, $1->varName);

    if(field.typeIndex == -1)
    {
        printf("error: unkwown type '%s' for field '%s'\n", $1->varName, $2->varName);
        exit(1);
    }

    InstallField($$, field);
}

field : field '.' IDENTIFIER {}
    | IDENTIFIER '.' IDENTIFIER

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

global_decl_block: DECL global_decl_list ENDDECL
    | DECL ENDDECL
    ;

global_decl_list: global_decl_list global_decl
    | global_decl
    ;

global_decl: TYPE global_id_list ';' {
        for(int n = 0; n < $2->size; n++)
        {
            $2->symbols[n].typeIndex = LookUpTypeTableIndex(typeTable, $1->varName);

            if($2->symbols[n].typeIndex == -1)
            {
                printf("error: unkwown type '%s'\n", $1->varName);
                exit(1);
            }

            InstallGlobalSymbol(&globalSymbolTable, $2->symbols[n]);
        }
        free($2->symbols);
        free($2);
    }
    ;

global_id_list: global_id_list ',' global_id {
        InstallGlobalSymbol($1, $3->symbols[0]);
        free($3->symbols);
        free($3);
        $$ = $1;
    }
    | global_id { $$ = $1; }
    ;

global_id: IDENTIFIER  {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = $1->varName;
        symbol.functionLabel = -1;
        InstallGlobalSymbol($$, symbol);
    }
    | IDENTIFIER '[' INTEGER_LITERAL ']' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = $1->varName;
        symbol.arrayDim = 1;
        symbol.functionLabel = -1;
        InstallGlobalSymbol($$, symbol);
    }
    | IDENTIFIER '[' INTEGER_LITERAL ']' '[' INTEGER_LITERAL ']' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = $1->varName;
        symbol.colSize = $6->val;
        symbol.arrayDim = 2;
        symbol.functionLabel = -1;
        InstallGlobalSymbol($$, symbol);
    }
    | MUL global_id  {
        $2->symbols[0].typeIndex = -1;
        $$ = $2;
    }
    | IDENTIFIER '(' param_list ')' {
        $$ = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        $$->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = $1->varName;
        symbol.functionLabel = functionLabelCounter++;
        symbol.paramList = $3;
        InstallGlobalSymbol($$, symbol);
    }
    ;

function_def_block: function_def_block function_def { $$ = CreateASTNode(0, 0, CONNECTOR_NODE, 0, $1, $2); }
    | function_def { $$ = $1; }
    ;

function_def: TYPE IDENTIFIER '(' param_list ')' '{' local_decl_block function_body '}' {

        $$ = CreateASTNode(0, $2->varName, FUNCTION_DEF_NODE, 0, $8, 0);
        $$->returnTypeIndex = LookUpTypeTableIndex(typeTable, $1->varName);
        $$->paramList = $4;

        struct LocalSymbolTable *localSymbolTable = (struct LocalSymbolTable *)malloc(sizeof(struct LocalSymbolTable));
        localSymbolTable->size = 0;
        localSymbolTable->symbols = 0;

        // installing parameters into local symbol table
        if($4)
        {
            for(int n = 0; n < $4->size; n++)
            {
                struct LocalSymbol symbol = {0};
                symbol.name = $4->params[n].name;
                symbol.typeIndex = $4->params[n].typeIndex;
                symbol.binding = -(n + 3);
                InstallLocalSymbol(localSymbolTable, symbol);
            }
        }

        //installing local variables into local symbol table
        if($7)
        {
            for(int n = 0; n < $7->size; n++)
            {
                $7->symbols[n].binding = n + 1;
                InstallLocalSymbol(localSymbolTable, $7->symbols[n]);
            }
        }
        $$->localSymbolTable = localSymbolTable;
}

param_list: param_list ',' param {
        if($1 && $3)
        {
            InstallParam($1, $3->params[0].name, $3->params[0].typeIndex);
            free($3->params);
            free($3);
        }
        $$ = $1;
    }
    | param  { $$ = $1; }
    | %empty { $$ = 0; }
    ;

param: TYPE IDENTIFIER {
        $$ = (struct ParamList*)malloc(sizeof(struct ParamList));
        $$->size = 0;
        int typeIndex = LookUpTypeTableIndex(typeTable, $1->varName);

        if(typeIndex == -1)
        {
            printf("error: unkwown type '%s'\n", $1->varName);
            exit(1);
        }

        InstallParam($$, $2->varName, typeIndex);
    }
    | TYPE MUL IDENTIFIER {
        $$ = (struct ParamList*)malloc(sizeof(struct ParamList));
        $$->size = 0;
        int typeIndex = LookUpTypeTableIndex(typeTable, $1->varName);

        if(typeIndex == -1)
        {
            printf("error: unkwown type '%s'\n", $1->varName);
            exit(1);
        }

        InstallParam($$, $3->varName, typeIndex);
    }
    ;

local_decl_block: DECL local_decl_list ENDDECL { $$ = $2; }
    | DECL ENDDECL { $$ = 0; }
    ;

local_decl_list: local_decl_list local_decl {
        for(int n = 0; n < $2->size; n++)
        {
            InstallLocalSymbol($1, $2->symbols[n]);
        }
        free($2->symbols);
        free($2);
    }
    | local_decl { $$ = $1; }
    ;

local_decl: TYPE local_id_list ';' {
        for(int n = 0; n < $2->size; n++)
        {
            $2->symbols[n].typeIndex = LookUpTypeTableIndex(typeTable, $1->varName);

            if($2->symbols[n].typeIndex == -1)
            {
                printf("error: unkwown type '%s'\n", $1->varName);
                exit(1);
            }
        }
        $$ = $2;
    }
    ;

local_id_list: local_id_list ',' local_id {
        InstallLocalSymbol($1, $3->symbols[0]);
        free($3->symbols);
        free($3);
        $$ = $1;
    }
    | local_id { $$ = $1; }
    ;

local_id: IDENTIFIER {
        $$ = (struct LocalSymbolTable*)malloc(sizeof(struct LocalSymbolTable));
        struct LocalSymbol symbol = {0};
        symbol.name = $1->varName;
        InstallLocalSymbol($$, symbol);
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
        $$->size = 0;
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
    printf("line:%d '%s', yytext: '%s'\n", line - 1, s, yytext);
    return 1;
}

void Compile(struct ASTNode *node)
{
    if(compilerMode == PRINT_AST)
    {
        PrintAST(node, 0);

        if(globalSymbolTable.size > 0)
        {
            printf("Global Symbol Table:\n");
            PrintGlobalSymbolTable(globalSymbolTable);
            printf("static address offset: %d\n", globalSymbolTable.staticAddressOffset);
        }
    }
    else if(compilerMode == COMPILE_FOR_XSM)
    {
        printf("info: generating xsm assembly ...\n");

        if(!outputFileName)
        {
            outputFileName = strdup("out.xsm");
        }

        FILE *output = fopen(outputFileName, "w");
        if(output)
        {
            GenerateCode(node, output);
            fprintf(output, "$%d\n", globalSymbolTable.staticAddressOffset);
        }
        else
        {
            printf("error: failed to create output file!\n");
            exit(1);
        }
        fclose(output);

        printf("info: compilation finished, output file -> '%s'\n", outputFileName);
    }
    else if(compilerMode == COMPILE_FOR_X86)
    {
        /* printf("info: generating x86 32 bit nasm assembly ...\n"); */

        if(!outputFileName)
        {
            outputFileName = strdup("out_x86.asm");
        }

        FILE *output = fopen(outputFileName, "w");
        if(output)
        {
            /* x86AssemblyBackend_32bit(node, output); */
        }
        else
        {
            printf("error: failed to create output file!\n");
            exit(1);
        }

        fclose(output);

        /* printf("info: compilation finished, output file -> '%s'\n", outputFileName);  */
    }
    else if(compilerMode == COMPILE_TO_C)
    {
        /* printf("info: generating c code ...\n"); */

        if(!outputFileName)
        {
            outputFileName = strdup("out.c");
        }

        FILE *output = fopen(outputFileName, "w");
        if(output)
        {
            /* C_backend(node, output); */
        }
        else
        {
            printf("error: failed to create output file!\n");
            exit(1);
        }
        fclose(output);

        /* printf("info: compilation finished, output file -> '%s'\n", outputFileName); */
    }
}

void PrintUsage()
{
    printf("usage: explc [options] input file\n");
    printf("[options]\n");
    printf("  -mode: compiler mode, supported mode: [print|c|x86|xsm]\n");
    printf("     print: print abstract syntax tree\n");
    printf("     c: compile to c\n");
    printf("     xsm: compile to xsm assembly\n");
    printf("     x86: compile to x86 32 bit nasm assembly\n");
    printf("  -o <file>: place output file into <file>\n");
    printf("  -h, --help: print this help\n");
}

int main(int argc, char *argv[])
{
    InitializeTypeTable(&typeTable);

    if(argc == 1)
    {
        printf("error: no input file\n");
        return 1;
    }

    bool inputFileFound = false;

    if(argc > 1)
    {
        for(int n = 1; n < argc; n++)
        {
            if(!strcmp(argv[n], "-mode"))
            {
                if(n < (argc - 1))
                {
                    if(!strcmp(argv[n + 1], "xsm"))
                    {
                        compilerMode = COMPILE_FOR_XSM;
                    }
                    else if(!strcmp(argv[n + 1], "x86"))
                    {
                        compilerMode = COMPILE_FOR_X86;
                    }
                    else if(!strcmp(argv[n + 1], "c"))
                    {
                        compilerMode = COMPILE_TO_C;
                    }
                    else if(!strcmp(argv[n + 1], "print"))
                    {
                        compilerMode = PRINT_AST;
                    }
                    else
                    {
                        printf("error: unknown compiler mode '%s'\n", argv[n + 1]);
                        printf("info: default compiler mode 'xsm'\n");
                    }
                    n++;
                }
                else
                {
                    printf("error: missing compiler mode after '-mode'\n");
                }
            }
            else if(!strcmp(argv[n], "-o"))
            {
                if(n < (argc - 1))
                {
                    outputFileName = strdup(argv[n + 1]);
                    n++;
                }
                else
                {
                    printf("error: missing file name after '-o'\n");
                }
            }
            else if(!strcmp(argv[n], "-h") || !strcmp(argv[n], "--help"))
            {
                PrintUsage();
                return 1;
            }
            else
            {
                if(!inputFileFound)
                {
                    inputFileName = strdup(argv[n]);
                    inputFileFound = true;
                }
                else
                {
                    printf("warning: only a single input file supported, ignoring '%s'\n", argv[n]);
                }
            }
        }

        if(inputFileFound)
        {
            if(outputFileName && !strcmp(inputFileName, outputFileName))
            {
                printf("error: input and output file names are the same\n");
                return 1;
            }

            yyin = fopen(inputFileName, "r");

            if(yyin)
            {
                yyparse();
            }
            else
            {
                printf("error: failed to open input file '%s'\n", inputFileName);
                return 1;
            }
        }
        else
        {
            printf("error: no input file\n");
            return 1;
        }
    }

    free(outputFileName);
    free(inputFileName);

    return 0;
}
