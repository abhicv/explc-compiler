#include "parser.h"

Token GetNextToken(Parser *parser)
{
    return parser->tokenList.tokens[parser->tokenIndex++];
}

Token PeekNextToken(Parser *parser)
{
    return parser->tokenList.tokens[parser->tokenIndex];
}

bool AcceptToken(Parser *parser, unsigned int tokenType)
{
    Token token = PeekNextToken(parser);

    if(token.type == tokenType)
    {
        GetNextToken(parser);
        return true;
    }

    return false;
}

Token ExpectToken(Parser *parser, unsigned int tokenType)
{
    Token token = PeekNextToken(parser);

    if(token.type == tokenType)
    {
        return GetNextToken(parser);
    }
    else
    {
        printf("%s:%u:%u: error: expected '%s' but found '%s'\n", parser->fileName, token.line+1, token.column+1, TokenTypeToString(tokenType), TokenTypeToString(token.type));
        exit(1);
    }
}

Index ParseExpression(AST *ast, Parser *parser);
Index ParseTerm(AST *ast, Parser *parser);
Index ParseFactor(AST *ast, Parser *parser);

Index ParseExpression(AST *ast, Parser *parser)
{
    Index left = ParseTerm(ast, parser);

    if(AcceptToken(parser, TOKEN_PLUS))
    {
        Node node = {0};
        node.type = NODE_BIN_OP;
        node.binOpType = BIN_OP_ADD;
        node.left = left;
        node.right = ParseExpression(ast, parser);
        return PushNode(ast, node);
    }
    else if(AcceptToken(parser, TOKEN_MINUS))
    {
        Node node = {0};
        node.type = NODE_BIN_OP;
        node.binOpType = BIN_OP_SUB;
        node.left = left;
        node.right = ParseExpression(ast, parser);
        return PushNode(ast, node);
    }

    return left;
}

Index ParseTerm(AST *ast, Parser *parser)
{
    Index left = ParseFactor(ast, parser);

    if(AcceptToken(parser, TOKEN_MULTIPLY))
    {
        Node node = {0};
        node.type = NODE_BIN_OP;
        node.binOpType = BIN_OP_MUL;
        node.left = left;
        node.right = ParseTerm(ast, parser);
        return PushNode(ast, node);
    }
    else if(AcceptToken(parser, TOKEN_DIVIDE))
    {
        Node node = {0};
        node.type = NODE_BIN_OP;
        node.binOpType = BIN_OP_DIV;
        node.left = left;
        node.right = ParseTerm(ast, parser);
        return PushNode(ast, node);
    }

    return left;
}

Index ParseFactor(AST *ast, Parser *parser)
{
    if(AcceptToken(parser, TOKEN_IDENTIFIER))
    {
        Node node = {0};
        node.type = NODE_IDENTIFIER;
        node.identifier = parser->tokenList.tokens[parser->tokenIndex - 1].identifier;
        return PushNode(ast, node);

        // TODO parse function call too..
    }
    else if(AcceptToken(parser, TOKEN_INTEGER_CONSTANT))
    {
        Node node = {0};
        node.type = NODE_INTEGER_CONSTANT;
        node.value = parser->tokenList.tokens[parser->tokenIndex - 1].integerValue;
        return PushNode(ast, node);
    }
    else if(AcceptToken(parser, TOKEN_OPEN_BRACKET))
    {
        Index index = ParseExpression(ast, parser);
        ExpectToken(parser, TOKEN_CLOSE_BRACKET);
        return index;
    }
}

Index ParseStruct(AST *ast, Parser *parser)
{
    Token structId = ExpectToken(parser, TOKEN_IDENTIFIER);
    ExpectToken(parser, TOKEN_DOUBLE_COLON);
    ExpectToken(parser, TOKEN_KEYWORD_STRUCT);
    ExpectToken(parser, TOKEN_OPEN_CURLY_BRACKET);

    Node node = {0};
    node.type = NODE_STRUCT_DEF;
    node.structName = structId.identifier;
    node.fieldIndexCount = 0;
    node.fieldIndexList = 0;

    // parsing struct fields
    while(true)
    {
        Token token = PeekNextToken(parser);
        if(token.type == TOKEN_CLOSE_CURLY_BRACKET) break;
        else if(token.type == TOKEN_PROGRAM_END) break;

        Token fieldId = ExpectToken(parser, TOKEN_IDENTIFIER);
        ExpectToken(parser, TOKEN_COLON);
        Token typeID = ExpectToken(parser, TOKEN_IDENTIFIER);
        ExpectToken(parser, TOKEN_SEMICOLON);

        Node id = {0};
        id.identifier = fieldId.identifier;
        id.type = NODE_IDENTIFIER;

        Node type = {0};
        type.identifier = typeID.identifier;
        type.type = NODE_IDENTIFIER;

        Node field = {0};
        field.type = NODE_FIELD;
        field.left = PushNode(ast, id);
        field.right = PushNode(ast, type);

        Index fieldIndex = PushNode(ast, field);

        PushIndex(&node.fieldIndexList, &node.fieldIndexCount, fieldIndex);
    }

    ExpectToken(parser, TOKEN_CLOSE_CURLY_BRACKET);

    return PushNode(ast, node);
}

Index ParseAssignStatement(AST *ast, Parser *parser)
{
    Node node = {0};
    node.type = NODE_ASSIGN_STATEMENT;
}

Index ParseStatement(AST *ast, Parser *parser)
{
    //parse assignment statement
    if(AcceptToken(parser, TOKEN_IDENTIFIER))
    {
        if(AcceptToken(parser, TOKEN_EQUAL))
        {
            
        }
    }
}

Index ParseProcedure(AST *ast, Parser *parser)
{
    Node node = {0};
    node.type = NODE_PROC_DEF;

    Token procId = ExpectToken(parser, TOKEN_IDENTIFIER);
    ExpectToken(parser, TOKEN_DOUBLE_COLON);
    ExpectToken(parser, TOKEN_KEYWORD_PROC);
    ExpectToken(parser, TOKEN_OPEN_BRACKET);

    //parse parameters
    while(true)
    {
        Token token = PeekNextToken(parser);
        if(token.type == TOKEN_PROGRAM_END) break;
        else if(token.type == TOKEN_CLOSE_BRACKET) break;

        if(node.parameterIndexCount > 0)
        {
            ExpectToken(parser, TOKEN_COMMA);
        }

        Token paramId = ExpectToken(parser, TOKEN_IDENTIFIER);
        ExpectToken(parser, TOKEN_COLON);
        Token paramType = ExpectToken(parser, TOKEN_IDENTIFIER);

        Node id = {0};
        id.identifier = paramId.identifier;
        id.type = NODE_IDENTIFIER;

        Node type = {0};
        type.identifier = paramType.identifier;
        type.type = NODE_IDENTIFIER;

        Node field = {0};
        field.type = NODE_FIELD;
        field.left = PushNode(ast, id);
        field.right = PushNode(ast, type);

        Index index = PushNode(ast, field);
        PushIndex(&node.parameterIndexList, &node.parameterIndexCount, index);
    }

    ExpectToken(parser, TOKEN_CLOSE_BRACKET);

    //parse return types
    if(AcceptToken(parser, TOKEN_COLON))
    {
        while(true)
        {
            Token token = PeekNextToken(parser);
            if(token.type == TOKEN_PROGRAM_END) break;
            else if(token.type == TOKEN_OPEN_CURLY_BRACKET) break;

            if(node.returnIndexCount > 0)
            {
                ExpectToken(parser, TOKEN_COMMA);
            }

            Token returnId = ExpectToken(parser, TOKEN_IDENTIFIER);
            
            Node id = {0};
            id.identifier = returnId.identifier;
            id.type = NODE_IDENTIFIER;

            Index index = PushNode(ast, id);
            PushIndex(&node.returnIndexList, &node.returnIndexCount, index);
        }
    }

    ExpectToken(parser, TOKEN_OPEN_CURLY_BRACKET);

    // parse function body

    ExpectToken(parser, TOKEN_CLOSE_CURLY_BRACKET);

    node.procName = procId.identifier;
    return PushNode(ast, node);
}


Index ParseProgram(AST *ast, Parser *parser)
{
    Node node = {0};
    node.type = NODE_PROGRAM;
    node.indexList = 0;
    node.indexCount = 0;

    while(true)
    {
        Token token = PeekNextToken(parser);
        if(token.type == TOKEN_PROGRAM_END) break;

        ExpectToken(parser, TOKEN_IDENTIFIER);
        ExpectToken(parser, TOKEN_DOUBLE_COLON);

        if(AcceptToken(parser, TOKEN_KEYWORD_STRUCT))
        {
            parser->tokenIndex -= 3;
            Index index = ParseStruct(ast, parser);
            PushIndex(&node.indexList, &node.indexCount, index);
        }
        else if(AcceptToken(parser, TOKEN_KEYWORD_PROC))
        {
            parser->tokenIndex -= 3;
            Index index = ParseProcedure(ast, parser);
            PushIndex(&node.indexList, &node.indexCount, index);
        }
        else
        {
            GetNextToken(parser);
        }
    }

    return PushNode(ast, node);
}
