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
    INTEGER = 258,
    IDENTIFIER = 259,
    BEGIN_TOKEN = 260,
    END_TOKEN = 261,
    READ_TOKEN = 262,
    WRITE_TOKEN = 263,
    IF = 264,
    THEN = 265,
    ELSE = 266,
    ENDIF = 267,
    WHILE = 268,
    DO = 269,
    ENDWHILE = 270,
    BREAK = 271,
    CONTINUE = 272,
    LT = 273,
    GT = 274,
    LT_EQ = 275,
    GT_EQ = 276,
    EQUAL_EQ = 277,
    NOT_EQ = 278,
    EQ = 279,
    PLUS = 280,
    MINUS = 281,
    MUL = 282,
    DIV = 283
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define IDENTIFIER 259
#define BEGIN_TOKEN 260
#define END_TOKEN 261
#define READ_TOKEN 262
#define WRITE_TOKEN 263
#define IF 264
#define THEN 265
#define ELSE 266
#define ENDIF 267
#define WHILE 268
#define DO 269
#define ENDWHILE 270
#define BREAK 271
#define CONTINUE 272
#define LT 273
#define GT 274
#define LT_EQ 275
#define GT_EQ 276
#define EQUAL_EQ 277
#define NOT_EQ 278
#define EQ 279
#define PLUS 280
#define MINUS 281
#define MUL 282
#define DIV 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "explc.y" /* yacc.c:1909  */

    struct ASTNode *astNode;

#line 114 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
