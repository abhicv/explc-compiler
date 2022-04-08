/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SOURCE_PARSER_H_INCLUDED
# define YY_YY_SOURCE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER_LITERAL = 258,
    STRING_LITERAL = 259,
    IDENTIFIER = 260,
    NULL_TOKEN = 261,
    DECL = 262,
    ENDDECL = 263,
    TYPE_TOKEN = 264,
    ENDTYPE_TOKEN = 265,
    BEGIN_TOKEN = 266,
    END_TOKEN = 267,
    READ_TOKEN = 268,
    WRITE_TOKEN = 269,
    INIT_TOKEN = 270,
    ALLOC_TOKEN = 271,
    FREE_TOKEN = 272,
    IF = 273,
    THEN = 274,
    ELSE = 275,
    ELIF = 276,
    ENDIF = 277,
    WHILE = 278,
    DO = 279,
    ENDWHILE = 280,
    BREAK = 281,
    CONTINUE = 282,
    RETURN = 283,
    AND = 284,
    OR = 285,
    LT = 286,
    GT = 287,
    LT_EQ = 288,
    GT_EQ = 289,
    EQUAL_EQ = 290,
    NOT_EQ = 291,
    EQ = 292,
    PLUS = 293,
    MINUS = 294,
    MUL = 295,
    DIV = 296,
    MOD = 297,
    ADDR_OF = 298
  };
#endif
/* Tokens.  */
#define INTEGER_LITERAL 258
#define STRING_LITERAL 259
#define IDENTIFIER 260
#define NULL_TOKEN 261
#define DECL 262
#define ENDDECL 263
#define TYPE_TOKEN 264
#define ENDTYPE_TOKEN 265
#define BEGIN_TOKEN 266
#define END_TOKEN 267
#define READ_TOKEN 268
#define WRITE_TOKEN 269
#define INIT_TOKEN 270
#define ALLOC_TOKEN 271
#define FREE_TOKEN 272
#define IF 273
#define THEN 274
#define ELSE 275
#define ELIF 276
#define ENDIF 277
#define WHILE 278
#define DO 279
#define ENDWHILE 280
#define BREAK 281
#define CONTINUE 282
#define RETURN 283
#define AND 284
#define OR 285
#define LT 286
#define GT 287
#define LT_EQ 288
#define GT_EQ 289
#define EQUAL_EQ 290
#define NOT_EQ 291
#define EQ 292
#define PLUS 293
#define MINUS 294
#define MUL 295
#define DIV 296
#define MOD 297
#define ADDR_OF 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 42 "source/explc.y" /* yacc.c:1909  */

    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct FieldList *fieldList;
    struct ASTNodeList *nodeList;

#line 149 "source/parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SOURCE_PARSER_H_INCLUDED  */
