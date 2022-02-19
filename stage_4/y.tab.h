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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    INT = 261,
    STR = 262,
    DECL = 263,
    ENDDECL = 264,
    BEGIN_TOKEN = 265,
    END_TOKEN = 266,
    READ_TOKEN = 267,
    WRITE_TOKEN = 268,
    IF = 269,
    THEN = 270,
    ELSE = 271,
    ENDIF = 272,
    WHILE = 273,
    DO = 274,
    ENDWHILE = 275,
    BREAK = 276,
    CONTINUE = 277,
    LT = 278,
    GT = 279,
    LT_EQ = 280,
    GT_EQ = 281,
    EQUAL_EQ = 282,
    NOT_EQ = 283,
    EQ = 284,
    PLUS = 285,
    MINUS = 286,
    MUL = 287,
    DIV = 288,
    MOD = 289,
    ADDR_OF = 290
  };
#endif
/* Tokens.  */
#define INTEGER_LITERAL 258
#define STRING_LITERAL 259
#define IDENTIFIER 260
#define INT 261
#define STR 262
#define DECL 263
#define ENDDECL 264
#define BEGIN_TOKEN 265
#define END_TOKEN 266
#define READ_TOKEN 267
#define WRITE_TOKEN 268
#define IF 269
#define THEN 270
#define ELSE 271
#define ENDIF 272
#define WHILE 273
#define DO 274
#define ENDWHILE 275
#define BREAK 276
#define CONTINUE 277
#define LT 278
#define GT 279
#define LT_EQ 280
#define GT_EQ 281
#define EQUAL_EQ 282
#define NOT_EQ 283
#define EQ 284
#define PLUS 285
#define MINUS 286
#define MUL 287
#define DIV 288
#define MOD 289
#define ADDR_OF 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 30 "explc.y" /* yacc.c:1909  */

    struct ASTNode *astNode;
    struct GlobalSymbolTable *table;

#line 129 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
