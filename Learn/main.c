#include "lexer.c"
#include "parser.c"
#include "ast.c"

void PrintNode(AST ast, Index index, int indent)
{
    for(int n = 0; n < indent; n++) printf("   ");
    printf("+- ");
    indent++;

    Node node = ast.nodeList[index];

    switch(node.type)
    {
        case NODE_PROGRAM:
        {
            printf("program:\n");
            
            for(int n = 0; n < node.indexCount; n++)
            {
                PrintNode(ast, node.indexList[n], indent);
            }
        };
        break;

        case NODE_STRUCT_DEF:
        {
            printf("struct def: '%s'\n", node.structName);

            for(int n = 0; n < node.fieldIndexCount; n++)
            {
                PrintNode(ast, node.fieldIndexList[n], indent);
            }
        };
        break;

        case NODE_PROC_DEF:
        {
            printf("procedure def: '%s'\n", node.procName);
            
            for(int n = 0; n < node.parameterIndexCount; n++)
            {
                PrintNode(ast, node.parameterIndexList[n], indent);
            }
            
            for(int n = 0; n < node.returnIndexCount; n++)
            {
                PrintNode(ast, node.returnIndexList[n], indent);
            }
        }
        break;

        case NODE_FIELD:
        {
            printf("field: id: '%s', type: '%s'\n", ast.nodeList[node.left].identifier, ast.nodeList[node.right].identifier);
        }
        break;

        case NODE_BIN_OP:
        {
            if(node.binOpType == BIN_OP_ADD)
            {
                printf("bin_op: '+'\n");
            }
            else if(node.binOpType == BIN_OP_SUB)
            {
                printf("bin_op: '-'\n");
            }
            else if(node.binOpType == BIN_OP_MUL)
            {
                printf("bin_op: '*'\n");
            }
            else if(node.binOpType == BIN_OP_DIV)
            {
                printf("bin_op: '/'\n");
            }

            PrintNode(ast, node.left, indent);
            PrintNode(ast, node.right, indent);
        }
        break;

        case NODE_IDENTIFIER:
        {
            printf("id: '%s'\n", node.identifier);
        }
        break;

        case NODE_INTEGER_CONSTANT:
        {
            printf("int: '%d'\n", node.value);
        }
        break;

        default: 
        {
            printf("not implemented\n");
        }
        break;
    }
}

int main(int argc, char *argv[argc])
{
    AST ast = {0};
    InitAST(&ast);

    if(argc > 1)
    {
        char *source = LoadFileNullTerminated(argv[1]);

        if(source)
        {
            Parser parser = {0};
            parser.fileName = argv[1];
            parser.source = source;            
            parser.tokenList = TokenizeSource(source);

            printf("token count: %u\n", parser.tokenList.count);

            // for(int n = 0; n < parser.tokenList.count; n++)
            // {
            //     PrintTokenInfo(parser.tokenList.tokens[n]);
            // }

            Index index = ParseProgram(&ast, &parser);
            PrintNode(ast, index, 0);
            
            free(source);
        }
    }
    else
    {
        Parser parser = {0};
        parser.fileName = "source";

        char *source = "20 + (a + b) * (c / d) * 10";
        parser.source = source;
        parser.tokenList = TokenizeSource(source);
        printf("token count: %u\n", parser.tokenList.count);
        
        Index index = ParseExpression(&ast, &parser);
    
        printf("index: %u\n", index);
        printf("node count: %u\n", ast.nodeCount);

        PrintNode(ast, index, 0);
    }

    return 0;
}