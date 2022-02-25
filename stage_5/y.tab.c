/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "explc.y" /* yacc.c:339  */

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
    extern int localVariableCount;

    void Compile(struct ASTNode *node);

#line 102 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
    RETURN = 278,
    LT = 279,
    GT = 280,
    LT_EQ = 281,
    GT_EQ = 282,
    EQUAL_EQ = 283,
    NOT_EQ = 284,
    EQ = 285,
    PLUS = 286,
    MINUS = 287,
    MUL = 288,
    DIV = 289,
    MOD = 290,
    ADDR_OF = 291
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
#define RETURN 278
#define LT 279
#define GT 280
#define LT_EQ 281
#define GT_EQ 282
#define EQUAL_EQ 283
#define NOT_EQ 284
#define EQ 285
#define PLUS 286
#define MINUS 287
#define MUL 288
#define DIV 289
#define MOD 290
#define ADDR_OF 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 37 "explc.y" /* yacc.c:355  */

    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct ASTNodeList *nodeList;
    int type;

#line 223 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 240 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   422

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    88,    89,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   103,   107,   112,   115,   118,   122,
     125,   128,   131,   134,   137,   138,   141,   142,   144,   145,
     148,   160,   168,   171,   179,   187,   195,   199,   208,   209,
     212,   366,   383,   384,   387,   394,   395,   398,   407,   410,
     419,   426,   429,   436,   437,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   461,   464,   469,   474,   475,   476,   480
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_LITERAL", "STRING_LITERAL",
  "IDENTIFIER", "INT", "STR", "DECL", "ENDDECL", "BEGIN_TOKEN",
  "END_TOKEN", "READ_TOKEN", "WRITE_TOKEN", "IF", "THEN", "ELSE", "ENDIF",
  "WHILE", "DO", "ENDWHILE", "BREAK", "CONTINUE", "RETURN", "LT", "GT",
  "LT_EQ", "GT_EQ", "EQUAL_EQ", "NOT_EQ", "EQ", "PLUS", "MINUS", "MUL",
  "DIV", "MOD", "ADDR_OF", "';'", "'('", "')'", "','", "'['", "']'", "'{'",
  "'}'", "$accept", "program", "stmt_list", "statement", "read_stmt",
  "write_stmt", "assign_stmt", "if_stmt", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "TYPE", "global_decl_block",
  "global_decl_list", "global_decl", "global_id_list", "global_id",
  "function_def_block", "function_def", "param_list", "param",
  "local_decl_block", "local_decl_list", "local_decl", "local_id_list",
  "local_id", "function_body", "expr", "arg_list", "l_value", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    59,    40,    41,
      44,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF -144

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-144)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,    63,    35,    91,  -144,  -144,  -144,    19,    68,  -144,
    -144,     3,    91,  -144,   -26,    19,    16,  -144,  -144,  -144,
     -18,  -144,    91,    34,  -144,  -144,    19,    91,    46,    66,
    -144,    13,  -144,   117,  -144,  -144,    91,    27,    23,  -144,
      70,    76,    60,   124,    99,  -144,  -144,   107,   142,  -144,
     114,    71,  -144,    20,  -144,  -144,  -144,  -144,  -144,    48,
    -144,    96,   102,   108,   122,    92,   128,    29,    29,    26,
      29,   150,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,   334,   136,  -144,  -144,   107,    25,    29,     0,    29,
      29,    29,  -144,  -144,   348,  -144,  -144,   126,  -144,   270,
    -144,  -144,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,  -144,    29,  -144,  -144,   376,   119,   246,
     130,    26,   286,   302,   318,  -144,  -144,   387,   110,   387,
     110,    89,    89,    45,    45,  -144,  -144,  -144,   362,  -144,
      29,   129,   137,   138,   139,   160,   159,  -144,   376,    29,
    -144,   147,  -144,   231,   231,   258,  -144,    78,   177,  -144,
     231,   148,   155,   204,  -144,  -144,   156,  -144
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    24,    25,    27,     0,     0,    29,
       1,     0,     2,    39,    33,     0,     0,    32,    26,    28,
       0,    38,    43,     0,    36,    30,     0,    43,     0,     0,
      42,     0,    31,     0,    44,    37,     0,    34,     0,    41,
       0,     0,     0,     0,     0,    35,    46,     0,     0,    48,
       0,     0,    52,     0,    51,    45,    47,    67,    68,    75,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     0,    69,    40,    49,     0,     0,     0,     0,     0,
       0,     0,    21,    22,     0,    69,    78,    75,    70,     0,
      53,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,     0,    50,    72,    74,     0,     0,
       0,     0,     0,     0,     0,    23,    66,    60,    62,    61,
      63,    64,    65,    55,    56,    57,    58,    59,     0,    71,
       0,    76,     0,     0,     0,     0,     0,    17,    73,     0,
      15,     0,    16,     0,     0,     0,    14,     0,     0,    77,
       0,     0,     0,     0,    19,    20,     0,    18
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -143,   -70,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,     6,  -144,  -144,   171,  -144,   -13,  -144,   175,
     167,   165,  -144,  -144,   154,  -144,   111,  -144,   -64,  -144,
     -50
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    28,     3,     8,     9,    16,    17,    12,    13,
      29,    30,    44,    48,    49,    53,    54,    51,    81,   118,
      95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      82,   101,    24,    94,    96,   120,    99,     7,    20,    11,
     157,   158,    22,    32,     7,    23,     1,   163,    11,    98,
      27,    82,   117,   119,    14,   122,   123,   124,    57,    58,
      59,    97,    57,    58,    59,    10,   121,    31,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,    47,
     138,    34,    15,    25,    47,    37,    26,    84,    68,    68,
      85,    69,    68,    70,   116,    69,    41,    70,    40,     4,
       5,   143,     6,    42,     4,     5,   148,    18,   110,   111,
     112,    57,    58,    59,    43,   155,    86,   101,   101,    87,
      61,    62,    63,   101,   160,   161,    64,     4,     5,    65,
      66,    67,    45,    82,    82,    35,    36,    82,    82,    50,
      82,    68,    52,    82,    69,    83,    70,    57,    58,    59,
     108,   109,   110,   111,   112,    60,    61,    62,    63,    92,
       4,     5,    64,    46,    88,    65,    66,    67,   106,   107,
      89,   108,   109,   110,   111,   112,    90,    68,     4,     5,
      69,    55,    70,    57,    58,    59,    38,    36,   139,   140,
      91,   100,    61,    62,    63,    93,   114,    87,    64,   142,
     149,    65,    66,    67,   150,   153,   152,   151,   154,    19,
      57,    58,    59,    68,   156,   164,    69,    21,    70,    61,
      62,    63,   165,   167,    33,    64,   115,   162,    65,    66,
      67,    39,    56,     0,     0,     0,     0,    57,    58,    59,
      68,     0,     0,    69,     0,    70,    61,    62,    63,     0,
       0,   166,    64,     0,     0,    65,    66,    67,     0,     0,
       0,     0,     0,     0,    57,    58,    59,    68,     0,     0,
      69,     0,    70,    61,    62,    63,     0,     0,     0,    64,
       0,     0,    65,    66,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    68,     0,     0,    69,     0,    70,
     102,   103,   104,   105,   106,   107,     0,   108,   109,   110,
     111,   112,   102,   103,   104,   105,   106,   107,   141,   108,
     109,   110,   111,   112,   102,   103,   104,   105,   106,   107,
     159,   108,   109,   110,   111,   112,     0,     0,     0,   126,
     102,   103,   104,   105,   106,   107,     0,   108,   109,   110,
     111,   112,     0,     0,     0,   144,   102,   103,   104,   105,
     106,   107,     0,   108,   109,   110,   111,   112,     0,     0,
       0,   145,   102,   103,   104,   105,   106,   107,     0,   108,
     109,   110,   111,   112,     0,     0,     0,   146,   102,   103,
     104,   105,   106,   107,     0,   108,   109,   110,   111,   112,
       0,   113,   102,   103,   104,   105,   106,   107,     0,   108,
     109,   110,   111,   112,     0,   125,   102,   103,   104,   105,
     106,   107,     0,   108,   109,   110,   111,   112,     0,   147,
     102,   103,   104,   105,   106,   107,     0,   108,   109,   110,
     111,   112,   103,     0,   105,   106,   107,     0,   108,   109,
     110,   111,   112
};

static const yytype_int16 yycheck[] =
{
      50,    71,    15,    67,    68,     5,    70,     1,     5,     3,
     153,   154,    38,    26,     8,    41,     8,   160,    12,    69,
      38,    71,    86,    87,     5,    89,    90,    91,     3,     4,
       5,     5,     3,     4,     5,     0,    36,     3,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,    43,
     114,     5,    33,    37,    48,    42,    40,    37,    33,    33,
      40,    36,    33,    38,    39,    36,    43,    38,    41,     6,
       7,   121,     9,     3,     6,     7,   140,     9,    33,    34,
      35,     3,     4,     5,     8,   149,    38,   157,   158,    41,
      12,    13,    14,   163,    16,    17,    18,     6,     7,    21,
      22,    23,    42,   153,   154,    39,    40,   157,   158,    10,
     160,    33,     5,   163,    36,    44,    38,     3,     4,     5,
      31,    32,    33,    34,    35,    11,    12,    13,    14,    37,
       6,     7,    18,     9,    38,    21,    22,    23,    28,    29,
      38,    31,    32,    33,    34,    35,    38,    33,     6,     7,
      36,     9,    38,     3,     4,     5,    39,    40,    39,    40,
      38,    11,    12,    13,    14,    37,    30,    41,    18,    39,
      41,    21,    22,    23,    37,    15,    37,    39,    19,     8,
       3,     4,     5,    33,    37,    37,    36,    12,    38,    12,
      13,    14,    37,    37,    27,    18,    85,    20,    21,    22,
      23,    36,    48,    -1,    -1,    -1,    -1,     3,     4,     5,
      33,    -1,    -1,    36,    -1,    38,    12,    13,    14,    -1,
      -1,    17,    18,    -1,    -1,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    33,    -1,    -1,
      36,    -1,    38,    12,    13,    14,    -1,    -1,    -1,    18,
      -1,    -1,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    36,    -1,    38,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    24,    25,    26,    27,    28,    29,    42,    31,
      32,    33,    34,    35,    24,    25,    26,    27,    28,    29,
      42,    31,    32,    33,    34,    35,    -1,    -1,    -1,    39,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    39,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    39,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    39,    24,    25,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      -1,    37,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    -1,    37,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    -1,    37,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    25,    -1,    27,    28,    29,    -1,    31,    32,
      33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    46,    58,     6,     7,     9,    57,    59,    60,
       0,    57,    63,    64,     5,    33,    61,    62,     9,    60,
       5,    64,    38,    41,    62,    37,    40,    38,    57,    65,
      66,     3,    62,    65,     5,    39,    40,    42,    39,    66,
      41,    43,     3,     8,    67,    42,     9,    57,    68,    69,
      10,    72,     5,    70,    71,     9,    69,     3,     4,     5,
      11,    12,    13,    14,    18,    21,    22,    23,    33,    36,
      38,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    73,    75,    44,    37,    40,    38,    41,    38,    38,
      38,    38,    37,    37,    73,    75,    73,     5,    75,    73,
      11,    48,    24,    25,    26,    27,    28,    29,    31,    32,
      33,    34,    35,    37,    30,    71,    39,    73,    74,    73,
       5,    36,    73,    73,    73,    37,    39,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    39,
      40,    42,    39,    75,    39,    39,    39,    37,    73,    41,
      37,    39,    37,    15,    19,    73,    37,    47,    47,    42,
      16,    17,    20,    47,    37,    37,    17,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    49,    49,    50,    51,    52,    52,
      53,    54,    55,    56,    57,    57,    58,    58,    59,    59,
      60,    61,    61,    62,    62,    62,    62,    62,    63,    63,
      64,    65,    65,    65,    66,    67,    67,    68,    68,    69,
      70,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    74,    74,    75,    75,    75,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     6,     5,     5,     4,    10,     8,
       8,     2,     2,     3,     1,     1,     3,     2,     2,     1,
       3,     3,     1,     1,     4,     7,     2,     4,     2,     1,
       9,     3,     1,     0,     2,     3,     2,     2,     1,     3,
       3,     1,     1,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       2,     4,     3,     3,     1,     1,     4,     7,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 75 "explc.y" /* yacc.c:1646  */
    {
        printf("Global Symbol Table: \n");
        PrintGlobalSymbolTable(globalSymbolTable);

        fprintf(output, "$%d\n", globalSymbolTable.staticAddressOffset);

        if(!entryPointFound)
        {
            printf("[WARNING] couldn't found definition of 'main'\n");
        }
    }
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 88 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 89 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 92 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 93 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 94 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 95 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 96 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 97 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 98 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 99 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 100 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 103 "explc.y" /* yacc.c:1646  */
    { 
        struct ASTNode *addrNode = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[-2].astNode), 0);
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, addrNode, 0);
    }
#line 1568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 107 "explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, (yyvsp[-2].astNode), 0);
    }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 112 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WRITE_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 115 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 118 "explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *branch = CreateASTNode(0, 0, BRANCH_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-2].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-7].astNode), branch);
    }
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 122 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 125 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WHILE_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 128 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, BREAK_NODE, 0, 0, 0); }
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 131 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 134 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, RETURN_NODE, 0, (yyvsp[-1].astNode), 0); }
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 137 "explc.y" /* yacc.c:1646  */
    { (yyval.type) = INTEGER_TYPE; }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 138 "explc.y" /* yacc.c:1646  */
    { (yyval.type) = STRING_TYPE; }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 148 "explc.y" /* yacc.c:1646  */
    { 
        for(int n = 0; n < (yyvsp[-1].globalSymbolTable)->size; n++)
        {
            struct GlobalSymbol symbol = (yyvsp[-1].globalSymbolTable)->symbols[n];
            symbol.type += (yyvsp[-2].type);
            InstallGlobalSymbol(&globalSymbolTable, symbol.name, symbol.type, symbol.size);
            symbol.binding = globalSymbolTable.symbols[globalSymbolTable.size - 1].binding;
            globalSymbolTable.symbols[globalSymbolTable.size - 1] = symbol;
        }
    }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 160 "explc.y" /* yacc.c:1646  */
    {
        struct GlobalSymbol symbol = (yyvsp[0].globalSymbolTable)->symbols[0];
        InstallGlobalSymbol((yyvsp[-2].globalSymbolTable), symbol.name, symbol.type, symbol.size);
        (yyvsp[-2].globalSymbolTable)->symbols[(yyvsp[-2].globalSymbolTable)->size - 1] = symbol;
        free((yyvsp[0].globalSymbolTable)->symbols);
        free((yyvsp[0].globalSymbolTable));
        (yyval.globalSymbolTable) = (yyvsp[-2].globalSymbolTable);
    }
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 168 "explc.y" /* yacc.c:1646  */
    { (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable); }
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 171 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[0].astNode)->varName, 0, 1);
        (yyval.globalSymbolTable)->symbols[0].colSize = 0;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 0;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 179 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-3].astNode)->varName, 0, (yyvsp[-1].astNode)->val);
        (yyval.globalSymbolTable)->symbols[0].colSize = 0;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 1;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 187 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-6].astNode)->varName, 0, (yyvsp[-4].astNode)->val * (yyvsp[-1].astNode)->val);
        (yyval.globalSymbolTable)->symbols[0].colSize = (yyvsp[-1].astNode)->val;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 2;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 195 "explc.y" /* yacc.c:1646  */
    {
        (yyvsp[0].globalSymbolTable)->symbols[0].type = 2;
        (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable);
    }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 199 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-3].astNode)->varName, 0, 0);
        (yyval.globalSymbolTable)->symbols[0].functionLabel = functionLabelCounter++;
        (yyval.globalSymbolTable)->symbols[0].paramList = (yyvsp[-1].paramList);
    }
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 212 "explc.y" /* yacc.c:1646  */
    {

        localVariableCount = 0;        
        struct GlobalSymbol *symbol = 0;

        if(!strcmp("main\0", (yyvsp[-7].astNode)->varName))
        {
            if(entryPointFound)
            {
                printf("[ERROR] redefinition of 'int main()' !\n");
                exit(1);
            }

            if((yyvsp[-8].type) != INTEGER_TYPE)
            {
                printf("[ERROR] function 'main' must return 'int' !\n");
                exit(1);
            }

            if((yyvsp[-5].paramList))
            {
                printf("[ERROR] function 'main' takes 0 parameter but found %d parameters!\n", (yyvsp[-5].paramList)->size);
                exit(1);
            }

            entryPointFound = true;
            returnType = INTEGER_TYPE;
        }
        else
        {
            symbol = LookUpGlobalSymbolTable(globalSymbolTable, (yyvsp[-7].astNode)->varName);

            if(!symbol)
            {
                printf("[ERROR] found definition of undeclared function -> '%s' !\n", (yyvsp[-7].astNode)->varName);
                exit(1);
            }

            if(symbol->functionLabel <= -1)
            {
                printf("[ERROR] found definition undeclared function -> '%s' !\n", (yyvsp[-7].astNode)->varName);
                exit(1);
            }

            if(symbol->type != (yyvsp[-8].type))
            {
                printf("[ERROR] return type conflict in definition and declaration of function -> '%s' !\n", (yyvsp[-7].astNode)->varName);
                exit(1);
            }

            if(symbol->paramList && !(yyvsp[-5].paramList))
            {
                printf("[ERROR] function ->'%s' has 0 parameter in its definition!\n", (yyvsp[-7].astNode)->varName);
                exit(1);
            }

            if(!symbol->paramList && (yyvsp[-5].paramList))
            {
                printf("[ERROR] function ->'%s' has 0 parameter in its declaration!\n", (yyvsp[-7].astNode)->varName);
                exit(1);
            }

            if(symbol->paramList && (yyvsp[-5].paramList))
            {
                if(symbol->paramList->size != (yyvsp[-5].paramList)->size)
                {
                    printf("[ERROR] parameter count different in declaration and definition of function -> '%s' !\n", (yyvsp[-7].astNode)->varName);
                    exit(1);
                }

                for(int n = 0; n < (yyvsp[-5].paramList)->size; n++)
                {
                    if(symbol->paramList->params[n].type != (yyvsp[-5].paramList)->params[n].type)
                    {
                        printf("[ERROR] parameter %d type conflict in declaration and definition of function -> '%s' !\n", n, (yyvsp[-7].astNode)->varName);
                        exit(1);
                    }

                    if (strcmp(symbol->paramList->params[n].name, (yyvsp[-5].paramList)->params[n].name))
                    {
                        printf("[ERROR] parameter %d name conflict in declaration and definition of function -> '%s' !\n", n, (yyvsp[-7].astNode)->varName);
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
        if((yyvsp[-2].localSymbolTable))
        { 
            for(int n = 0; n < (yyvsp[-2].localSymbolTable)->size; n++)
            {
                struct LocalSymbol symbol = (yyvsp[-2].localSymbolTable)->symbols[n];
                InstallLocalSymbol(&localSymbolTable, symbol.name, symbol.type);
                localSymbolTable.symbols[localSymbolTable.size - 1].binding = n + 1;
            }
        }

        printf("function -> '%s'\n", (yyvsp[-7].astNode)->varName);
        PrintLocalSymbolTable(localSymbolTable);
        
        // semantic analysis
        returnType = (yyvsp[-8].type);
        if((yyvsp[-1].astNode))
        {
            PrintAST((yyvsp[-1].astNode), 0);
            CheckSemantics((yyvsp[-1].astNode));
        }

        char *funcLabel = (char*)malloc(strlen((yyvsp[-7].astNode)->varName) + 2);
        funcLabel[0] = '#';
        funcLabel[strlen((yyvsp[-7].astNode)->varName) + 1] = 0;
        strcat(funcLabel, (yyvsp[-7].astNode)->varName);       
        fprintf(output, "%s\n", funcLabel);
        fprintf(output, "PUSH BP\n");
        fprintf(output, "MOV BP, SP\n");
        free(funcLabel);
        
        // allocating space for local variables in the stack
        if((yyvsp[-2].localSymbolTable))
        {
            fprintf(output, "ADD SP, %d\n", (yyvsp[-2].localSymbolTable)->size);
            localVariableCount = (yyvsp[-2].localSymbolTable)->size;
        }

        //generating code for function
        if((yyvsp[-1].astNode))
        {
            GenerateCode((yyvsp[-1].astNode), output);
        }                        
        
        // freeing symbols and resetting local symbol table
        free(localSymbolTable.symbols);
        localSymbolTable.symbols = 0;
        localSymbolTable.size = 0;
        
        // TODO (abhicv): free nodes of function body AST
    }
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 366 "explc.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].paramList)) 
        {
            if((yyvsp[0].paramList))
            {
                InstallParam((yyvsp[-2].paramList), (yyvsp[0].paramList)->params[0].name, (yyvsp[0].paramList)->params[0].type);
                free((yyvsp[0].paramList)->params);
                free((yyvsp[0].paramList));
            }

            (yyval.paramList) = (yyvsp[-2].paramList);
        }
        else
        {
            (yyval.paramList) = 0;
        }
    }
#line 1912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 383 "explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[0].paramList); }
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 384 "explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = 0; }
#line 1924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 387 "explc.y" /* yacc.c:1646  */
    {
        (yyval.paramList) = (struct ParamList*)malloc(sizeof(struct ParamList));
        (yyval.paramList)->size = 0;
        InstallParam((yyval.paramList), (yyvsp[0].astNode)->varName, (yyvsp[-1].type));
    }
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 394 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable); }
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 395 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = 0; }
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 398 "explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[0].localSymbolTable)->size; n++)
        {
            struct LocalSymbol symbol = (yyvsp[0].localSymbolTable)->symbols[n];
            InstallLocalSymbol((yyvsp[-1].localSymbolTable), symbol.name, symbol.type);
        }
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
    }
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 407 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 410 "explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[-1].localSymbolTable)->size; n++)
        {
            (yyvsp[-1].localSymbolTable)->symbols[n].type = (yyvsp[-2].type);
        }
        (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable);
    }
#line 1978 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 419 "explc.y" /* yacc.c:1646  */
    {
        struct LocalSymbol symbol = (yyvsp[0].localSymbolTable)->symbols[0];
        InstallLocalSymbol((yyvsp[-2].localSymbolTable), symbol.name, 0);
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
        (yyval.localSymbolTable) = (yyvsp[-2].localSymbolTable);
    }
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 426 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 429 "explc.y" /* yacc.c:1646  */
    {
        (yyval.localSymbolTable) = (struct LocalSymbolTable*)malloc(sizeof(struct LocalSymbolTable));
        (yyval.localSymbolTable)->size = 0;
        InstallLocalSymbol((yyval.localSymbolTable), (yyvsp[0].astNode)->varName, 0);
    }
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 436 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 437 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = 0; }
#line 2018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 440 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, PLUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));      }
#line 2024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 441 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MINUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 442 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MUL_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 443 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DIV_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 444 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MOD_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 445 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 446 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 447 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 448 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 449 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQUAL_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));  }
#line 2078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 450 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, NOT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));    }
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 451 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 452 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 453 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 454 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 455 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[0].astNode), 0); }
#line 2114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 456 "explc.y" /* yacc.c:1646  */
    { 
        (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-3].astNode), 0); 
        (yyval.astNode)->argList = (yyvsp[-1].nodeList)->nodes;
        (yyval.astNode)->argCount = (yyvsp[-1].nodeList)->size;
    }
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 461 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 2130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 464 "explc.y" /* yacc.c:1646  */
    {
        InsertASTNode((yyvsp[-2].nodeList), *(yyvsp[0].astNode));
        (yyval.nodeList) = (yyvsp[-2].nodeList);
        free((yyvsp[0].astNode));
    }
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 469 "explc.y" /* yacc.c:1646  */
    { 
        (yyval.nodeList) = (struct ASTNodeList*)malloc(sizeof(struct ASTNodeList));
        InsertASTNode((yyval.nodeList), *(yyvsp[0].astNode));
    }
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 474 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 475 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 2161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 476 "explc.y" /* yacc.c:1646  */
    { 
            struct ASTNode *index = CreateASTNode(0, 0, INDEX_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-1].astNode)); 
            (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-6].astNode), index);
        }
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 480 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DEREF_NODE, 0, (yyvsp[0].astNode), 0);  }
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2180 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 481 "explc.y" /* yacc.c:1906  */


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
