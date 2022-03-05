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
#line 1 "source/explc.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    
    #include "ast.h"
    #include "ast.c"
    
    #include "eval.c"
    #include "symbol.c"

    #include "backends/gen_asm_x86.c"
    #include "backends/gen_c_code.c"

    extern int yylex();
    extern FILE *yyin;
    extern int yylineno;
    extern char *yytext;
    int yyerror(char const *s);

    extern int line;

    int compilerMode = 3;
    int functionLabelCounter = 0;
    char *inputFileName = 0;

    extern bool entryPointFound;
    extern struct GlobalSymbolTable globalSymbolTable;

    struct ASTNode *GetRightIfNode(struct ASTNode *node);

    void Compile(struct ASTNode *node);

    enum CompilerMode
    {
        PRINT_AST,
        COMPILE_FOR_XSM,
        COMPILE_FOR_X86,
        COMPILE_TO_C,
    };

#line 109 "source/parser.c" /* yacc.c:339  */

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
   by #include "parser.h".  */
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
    ELIF = 272,
    ENDIF = 273,
    WHILE = 274,
    DO = 275,
    ENDWHILE = 276,
    BREAK = 277,
    CONTINUE = 278,
    RETURN = 279,
    AND = 280,
    OR = 281,
    LT = 282,
    GT = 283,
    LT_EQ = 284,
    GT_EQ = 285,
    EQUAL_EQ = 286,
    NOT_EQ = 287,
    EQ = 288,
    PLUS = 289,
    MINUS = 290,
    MUL = 291,
    DIV = 292,
    MOD = 293,
    ADDR_OF = 294
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
#define ELIF 272
#define ENDIF 273
#define WHILE 274
#define DO 275
#define ENDWHILE 276
#define BREAK 277
#define CONTINUE 278
#define RETURN 279
#define AND 280
#define OR 281
#define LT 282
#define GT 283
#define LT_EQ 284
#define GT_EQ 285
#define EQUAL_EQ 286
#define NOT_EQ 287
#define EQ 288
#define PLUS 289
#define MINUS 290
#define MUL 291
#define DIV 292
#define MOD 293
#define ADDR_OF 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 44 "source/explc.y" /* yacc.c:355  */

    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct ASTNodeList *nodeList;
    int type;

#line 236 "source/parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SOURCE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 253 "source/parser.c" /* yacc.c:358  */

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
#define YYLAST   446

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      40,    41,     2,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    83,    83,    95,    96,    99,   100,   101,   102,   103,
     104,   105,   106,   109,   113,   118,   121,   124,   129,   136,
     140,   143,   149,   152,   158,   161,   164,   167,   170,   171,
     174,   175,   177,   178,   181,   193,   201,   204,   212,   220,
     228,   232,   241,   242,   245,   277,   286,   287,   290,   295,
     302,   303,   306,   315,   318,   327,   334,   337,   344,   345,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   371,
     374,   379,   384,   385,   386,   390
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_LITERAL", "STRING_LITERAL",
  "IDENTIFIER", "INT", "STR", "DECL", "ENDDECL", "BEGIN_TOKEN",
  "END_TOKEN", "READ_TOKEN", "WRITE_TOKEN", "IF", "THEN", "ELSE", "ELIF",
  "ENDIF", "WHILE", "DO", "ENDWHILE", "BREAK", "CONTINUE", "RETURN", "AND",
  "OR", "LT", "GT", "LT_EQ", "GT_EQ", "EQUAL_EQ", "NOT_EQ", "EQ", "PLUS",
  "MINUS", "MUL", "DIV", "MOD", "ADDR_OF", "'('", "')'", "';'", "','",
  "'['", "']'", "'{'", "'}'", "$accept", "program", "stmt_list",
  "statement", "read_stmt", "write_stmt", "assign_stmt", "if_stmt",
  "elif_stmt_list", "elif_stmt", "while_stmt", "break_stmt",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      40,    41,    59,    44,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF -84

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-84)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,    61,    31,    17,   -84,   -84,   -84,    -3,    69,   -84,
     -84,    29,    17,   -84,   -35,    -3,     4,   -84,   -84,   -84,
      13,   -84,    17,    41,   -84,   -84,    -3,    17,     2,    -1,
     -84,    28,   -84,    48,   -84,    72,   -84,    17,    54,    46,
     -84,   -84,   113,   116,    80,    73,   119,   -84,   -84,   121,
      90,   -84,   138,    84,   -84,    68,   -84,   -84,   -84,    86,
     -84,    93,    98,   104,   108,   111,   112,    83,    83,   153,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   122,
     -84,   -84,   121,    83,    -4,    83,    83,    83,   -84,   -84,
     -84,   -84,   -34,     3,    83,   263,   -84,   -84,   -84,   -84,
      83,   -84,   221,   115,     3,   299,   316,   333,     9,   -84,
     350,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,   -84,   281,   124,   127,   129,   131,
     148,   151,   -84,   384,    74,   -84,   396,   396,   -16,   -16,
     -16,   -16,   408,   408,    47,    47,   -84,   -84,   -84,   -84,
      83,   -84,   137,   -84,   218,   218,   -84,    83,   242,   -84,
     123,   173,   384,   -84,   218,   140,   139,    89,   -84,   141,
     188,    83,   -84,   218,   142,   -84,   -84,   146,   367,   203,
     -84,   -84,   167,   149,   218,   -84,   218
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    28,    29,    31,     0,     0,    33,
       1,     0,     2,    43,    37,     0,     0,    36,    30,    32,
       0,    42,    47,     0,    40,    34,     0,    47,     0,     0,
      46,     0,    35,     0,    48,     0,    41,     0,    38,     0,
      49,    45,     0,     0,     0,     0,     0,    39,    51,     0,
       0,    53,     0,     0,    57,     0,    56,    50,    52,    82,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     0,
      44,    54,     0,     0,     0,     0,     0,     0,    25,    26,
      74,    75,    82,     0,     0,     0,    76,    85,    58,     3,
       0,    55,     0,     0,     0,     0,     0,     0,     0,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,    83,     0,     0,     0,
       0,     0,    79,    81,     0,    73,    71,    72,    65,    67,
      66,    68,    69,    70,    60,    61,    62,    63,    64,    16,
       0,    14,     0,    15,     0,     0,    78,     0,     0,    13,
       0,     0,    80,    84,     0,     0,     0,     0,    22,     0,
       0,     0,    20,     0,     0,    21,    24,     0,     0,     0,
      17,    19,     0,     0,     0,    18,    23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,   -83,   -66,   -84,   -84,   -84,   -84,   -84,    23,
     -84,   -84,   -84,   -84,    24,   -84,   -84,   190,   -84,   -11,
     -84,   187,   176,   168,   -84,   -84,   154,   -84,   132,   -84,
     -57,   -84,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    69,    70,    71,    72,    73,    74,   167,   168,
      75,    76,    77,    78,    28,     3,     8,     9,    16,    17,
      12,    13,    29,    30,    46,    50,    51,    55,    56,    53,
      95,   134,    96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      79,   103,    14,    99,    24,    22,   108,    34,    59,    23,
      83,    97,    90,    91,    92,    32,     1,    79,   119,   120,
     121,   122,   123,     4,     5,     7,   102,    11,   105,   106,
     107,    10,     7,    15,    20,   104,    11,   110,    35,    68,
      36,   109,    37,   125,    31,    68,    25,    26,    93,    94,
     132,   133,   128,    27,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     4,     5,    49,
       6,   160,   161,    38,    49,     4,     5,    40,    18,     4,
       5,   170,    48,   121,   122,   123,    90,    91,    92,    39,
     179,    37,    43,   158,    99,    99,     4,     5,    42,    57,
     162,   186,    79,    79,    99,   173,   165,   174,    79,    79,
      81,    82,    79,    99,   178,   156,    44,   157,    79,    68,
      99,    79,    93,    94,    45,    47,    54,    79,    59,    52,
      83,    80,    79,    84,    79,    61,    62,    63,    85,   164,
     165,   166,    64,    59,    86,    65,    66,    67,    87,    60,
      61,    62,    63,    88,    89,   100,   127,    64,    59,    68,
      65,    66,    67,   154,    98,    61,    62,    63,   150,   151,
     152,   155,    64,   153,    68,    65,    66,    67,    59,   159,
     171,   172,   184,   176,   180,    61,    62,    63,   181,    68,
     175,   185,    64,    59,   169,    65,    66,    67,    19,    21,
      61,    62,    63,    33,    58,    41,   177,    64,    59,    68,
      65,    66,    67,     0,   101,    61,    62,    63,     0,     0,
       0,   183,    64,    59,    68,    65,    66,    67,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,     0,    68,
      65,    66,    67,     0,     0,     0,   111,   112,   113,   114,
     115,   116,   117,   118,    68,   119,   120,   121,   122,   123,
       0,     0,     0,     0,     0,     0,   126,   111,   112,   113,
     114,   115,   116,   117,   118,     0,   119,   120,   121,   122,
     123,     0,     0,     0,     0,     0,     0,   163,   111,   112,
     113,   114,   115,   116,   117,   118,     0,   119,   120,   121,
     122,   123,     0,     0,     0,   124,   111,   112,   113,   114,
     115,   116,   117,   118,     0,   119,   120,   121,   122,   123,
       0,     0,     0,   149,   111,   112,   113,   114,   115,   116,
     117,   118,     0,   119,   120,   121,   122,   123,     0,     0,
     129,   111,   112,   113,   114,   115,   116,   117,   118,     0,
     119,   120,   121,   122,   123,     0,     0,   130,   111,   112,
     113,   114,   115,   116,   117,   118,     0,   119,   120,   121,
     122,   123,     0,     0,   131,   111,   112,   113,   114,   115,
     116,   117,   118,     0,   119,   120,   121,   122,   123,     0,
       0,   135,   111,   112,   113,   114,   115,   116,   117,   118,
       0,   119,   120,   121,   122,   123,     0,     0,   182,   111,
     112,   113,   114,   115,   116,   117,   118,     0,   119,   120,
     121,   122,   123,   113,   114,   115,   116,   117,   118,     0,
     119,   120,   121,   122,   123,   113,   114,   115,   116,     0,
       0,     0,   119,   120,   121,   122,   123
};

static const yytype_int16 yycheck[] =
{
      52,     5,     5,    69,    15,    40,    40,     5,     5,    44,
      44,    68,     3,     4,     5,    26,     8,    69,    34,    35,
      36,    37,    38,     6,     7,     1,    83,     3,    85,    86,
      87,     0,     8,    36,     5,    39,    12,    94,    36,    36,
      41,    93,    43,   100,     3,    36,    42,    43,    39,    40,
      41,   108,   104,    40,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,     6,     7,    45,
       9,   154,   155,    45,    50,     6,     7,     5,     9,     6,
       7,   164,     9,    36,    37,    38,     3,     4,     5,    41,
     173,    43,    46,   150,   160,   161,     6,     7,    44,     9,
     157,   184,   154,   155,   170,    16,    17,    18,   160,   161,
      42,    43,   164,   179,   171,    41,     3,    43,   170,    36,
     186,   173,    39,    40,     8,    45,     5,   179,     5,    10,
      44,    47,   184,    40,   186,    12,    13,    14,    40,    16,
      17,    18,    19,     5,    40,    22,    23,    24,    40,    11,
      12,    13,    14,    42,    42,    33,    41,    19,     5,    36,
      22,    23,    24,    15,    11,    12,    13,    14,    44,    42,
      41,    20,    19,    42,    36,    22,    23,    24,     5,    42,
      40,    42,    15,    42,    42,    12,    13,    14,    42,    36,
     167,    42,    19,     5,    21,    22,    23,    24,     8,    12,
      12,    13,    14,    27,    50,    37,    18,    19,     5,    36,
      22,    23,    24,    -1,    82,    12,    13,    14,    -1,    -1,
      -1,    18,    19,     5,    36,    22,    23,    24,    -1,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    -1,    36,
      22,    23,    24,    -1,    -1,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    36,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    42,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    42,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      41,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    41,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    41,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    41,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    -1,    -1,    41,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    27,    28,    29,    30,    -1,
      -1,    -1,    34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    49,    63,     6,     7,     9,    62,    64,    65,
       0,    62,    68,    69,     5,    36,    66,    67,     9,    65,
       5,    69,    40,    44,    67,    42,    43,    40,    62,    70,
      71,     3,    67,    70,     5,    36,    41,    43,    45,    41,
       5,    71,    44,    46,     3,     8,    72,    45,     9,    62,
      73,    74,    10,    77,     5,    75,    76,     9,    74,     5,
      11,    12,    13,    14,    19,    22,    23,    24,    36,    50,
      51,    52,    53,    54,    55,    58,    59,    60,    61,    80,
      47,    42,    43,    44,    40,    40,    40,    40,    42,    42,
       3,     4,     5,    39,    40,    78,    80,    78,    11,    51,
      33,    76,    78,     5,    39,    78,    78,    78,    40,    80,
      78,    25,    26,    27,    28,    29,    30,    31,    32,    34,
      35,    36,    37,    38,    42,    78,    45,    41,    80,    41,
      41,    41,    41,    78,    79,    41,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    42,
      44,    42,    41,    42,    15,    20,    41,    43,    78,    42,
      50,    50,    78,    45,    16,    17,    18,    56,    57,    21,
      50,    40,    42,    16,    18,    57,    42,    18,    78,    50,
      42,    42,    41,    18,    15,    42,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    53,    54,    55,    55,    55,
      55,    56,    56,    57,    58,    59,    60,    61,    62,    62,
      63,    63,    64,    64,    65,    66,    66,    67,    67,    67,
      67,    67,    68,    68,    69,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    74,    75,    75,    76,    77,    77,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      79,    79,    80,    80,    80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     5,     5,     4,     9,    11,    10,
       8,     2,     1,     6,     8,     2,     2,     3,     1,     1,
       3,     2,     2,     1,     3,     3,     1,     1,     4,     7,
       2,     4,     2,     1,     9,     3,     1,     0,     2,     3,
       3,     2,     2,     1,     3,     3,     1,     1,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     2,     4,     3,
       3,     1,     1,     4,     7,     2
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
#line 83 "source/explc.y" /* yacc.c:1646  */
    {

        CheckSemantics((yyvsp[0].astNode));
        Compile((yyvsp[0].astNode));

        if(!entryPointFound)
        {
            printf("[WARNING] no definition of function 'main'\n");
        }
    }
#line 1519 "source/parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 95 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1525 "source/parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 96 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1531 "source/parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 99 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1537 "source/parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 100 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1543 "source/parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 101 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1549 "source/parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 102 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1555 "source/parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 103 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1561 "source/parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 104 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1567 "source/parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 105 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1573 "source/parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 106 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1579 "source/parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 109 "source/explc.y" /* yacc.c:1646  */
    { 
        struct ASTNode *addrNode = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[-2].astNode), 0);
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, addrNode, 0);
    }
#line 1588 "source/parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 113 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, (yyvsp[-2].astNode), 0);
    }
#line 1596 "source/parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 118 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WRITE_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 1602 "source/parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 121 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1608 "source/parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 124 "source/explc.y" /* yacc.c:1646  */
    { 
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-6].astNode), (yyvsp[-3].astNode));
        (yyvsp[-2].astNode)->left = (yyvsp[-3].astNode); 
        (yyval.astNode)->right = (yyvsp[-2].astNode);
    }
#line 1618 "source/parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 129 "source/explc.y" /* yacc.c:1646  */
    { 
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-8].astNode), (yyvsp[-5].astNode));
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-4].astNode));
        ifNode->right = CreateASTNode(0, 0, BRANCH_NODE, 0, ifNode->right, (yyvsp[-2].astNode));
        (yyvsp[-4].astNode)->left = (yyvsp[-5].astNode); 
        (yyval.astNode)->right = (yyvsp[-4].astNode);
    }
#line 1630 "source/parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 136 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *branch = CreateASTNode(0, 0, BRANCH_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-2].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-7].astNode), branch);
    }
#line 1639 "source/parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 140 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1645 "source/parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 143 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-1].astNode));
        (yyvsp[0].astNode)->left = ifNode->right; 
        ifNode->right = (yyvsp[0].astNode); 
        (yyval.astNode) = (yyvsp[-1].astNode);
    }
#line 1656 "source/parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 149 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1662 "source/parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 152 "source/explc.y" /* yacc.c:1646  */
    { 
        struct ASTNode *ifNode = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-3].astNode), (yyvsp[0].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, BRANCH_NODE, 0, 0, ifNode); 
    }
#line 1671 "source/parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 158 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WHILE_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1677 "source/parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 161 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, BREAK_NODE, 0, 0, 0); }
#line 1683 "source/parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 164 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }
#line 1689 "source/parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, RETURN_NODE, 0, (yyvsp[-1].astNode), 0); }
#line 1695 "source/parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 170 "source/explc.y" /* yacc.c:1646  */
    { (yyval.type) = INTEGER_TYPE; }
#line 1701 "source/parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 171 "source/explc.y" /* yacc.c:1646  */
    { (yyval.type) = STRING_TYPE; }
#line 1707 "source/parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 181 "source/explc.y" /* yacc.c:1646  */
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
#line 1722 "source/parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 193 "source/explc.y" /* yacc.c:1646  */
    {
        struct GlobalSymbol symbol = (yyvsp[0].globalSymbolTable)->symbols[0];
        InstallGlobalSymbol((yyvsp[-2].globalSymbolTable), symbol.name, symbol.type, symbol.size);
        (yyvsp[-2].globalSymbolTable)->symbols[(yyvsp[-2].globalSymbolTable)->size - 1] = symbol;
        free((yyvsp[0].globalSymbolTable)->symbols);
        free((yyvsp[0].globalSymbolTable));
        (yyval.globalSymbolTable) = (yyvsp[-2].globalSymbolTable);
    }
#line 1735 "source/parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 201 "source/explc.y" /* yacc.c:1646  */
    { (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable); }
#line 1741 "source/parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 204 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[0].astNode)->varName, 0, 1);
        (yyval.globalSymbolTable)->symbols[0].colSize = 0;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 0;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1754 "source/parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 212 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-3].astNode)->varName, 0, (yyvsp[-1].astNode)->val);
        (yyval.globalSymbolTable)->symbols[0].colSize = 0;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 1;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1767 "source/parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 220 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-6].astNode)->varName, 0, (yyvsp[-4].astNode)->val * (yyvsp[-1].astNode)->val);
        (yyval.globalSymbolTable)->symbols[0].colSize = (yyvsp[-1].astNode)->val;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 2;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1780 "source/parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 228 "source/explc.y" /* yacc.c:1646  */
    {
        (yyvsp[0].globalSymbolTable)->symbols[0].type = 2;
        (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable);
    }
#line 1789 "source/parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 232 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-3].astNode)->varName, 0, 0);
        (yyval.globalSymbolTable)->symbols[0].functionLabel = functionLabelCounter++;
        (yyval.globalSymbolTable)->symbols[0].paramList = (yyvsp[-1].paramList);
    }
#line 1801 "source/parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 241 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1807 "source/parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 242 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1813 "source/parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 245 "source/explc.y" /* yacc.c:1646  */
    {

        (yyval.astNode) = CreateASTNode(0, (yyvsp[-7].astNode)->varName, FUNCTION_DEF_NODE, 0, (yyvsp[-1].astNode), 0);
        (yyval.astNode)->returnType = (yyvsp[-8].type);
        (yyval.astNode)->paramList = (yyvsp[-5].paramList);

        struct LocalSymbolTable *localSymbolTable = (struct LocalSymbolTable *)malloc(sizeof(struct LocalSymbolTable));
        
        // installing parameters into local symbol table
        if((yyvsp[-5].paramList))
        { 
            for(int n = 0; n < (yyvsp[-5].paramList)->size; n++)
            {
                InstallLocalSymbol(localSymbolTable, (yyvsp[-5].paramList)->params[n].name, (yyvsp[-5].paramList)->params[n].type);
                localSymbolTable->symbols[localSymbolTable->size - 1].binding = -(n + 3);
            }
        }
        
        //installing local variables into local symbol table
        if((yyvsp[-2].localSymbolTable))
        { 
            for(int n = 0; n < (yyvsp[-2].localSymbolTable)->size; n++)
            {
                struct LocalSymbol symbol = (yyvsp[-2].localSymbolTable)->symbols[n];
                InstallLocalSymbol(localSymbolTable, symbol.name, symbol.type);
                localSymbolTable->symbols[localSymbolTable->size - 1].binding = n + 1;
            }
        }

        (yyval.astNode)->localSymbolTable = localSymbolTable;
}
#line 1849 "source/parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 277 "source/explc.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].paramList) && (yyvsp[0].paramList)) 
        {
            InstallParam((yyvsp[-2].paramList), (yyvsp[0].paramList)->params[0].name, (yyvsp[0].paramList)->params[0].type);
            free((yyvsp[0].paramList)->params);
            free((yyvsp[0].paramList));
        }
        (yyval.paramList) = (yyvsp[-2].paramList);
    }
#line 1863 "source/parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 286 "source/explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[0].paramList); }
#line 1869 "source/parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 287 "source/explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = 0;  }
#line 1875 "source/parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 290 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.paramList) = (struct ParamList*)malloc(sizeof(struct ParamList));
        (yyval.paramList)->size = 0;
        InstallParam((yyval.paramList), (yyvsp[0].astNode)->varName, (yyvsp[-1].type));
    }
#line 1885 "source/parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 295 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.paramList) = (struct ParamList*)malloc(sizeof(struct ParamList));
        (yyval.paramList)->size = 0;
        InstallParam((yyval.paramList), (yyvsp[0].astNode)->varName, (yyvsp[-2].type) + 2);
    }
#line 1895 "source/parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 302 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable); }
#line 1901 "source/parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 303 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = 0; }
#line 1907 "source/parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 306 "source/explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[0].localSymbolTable)->size; n++)
        {
            struct LocalSymbol symbol = (yyvsp[0].localSymbolTable)->symbols[n];
            InstallLocalSymbol((yyvsp[-1].localSymbolTable), symbol.name, symbol.type);
        }
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
    }
#line 1921 "source/parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 315 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 1927 "source/parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 318 "source/explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[-1].localSymbolTable)->size; n++)
        {
            (yyvsp[-1].localSymbolTable)->symbols[n].type = (yyvsp[-2].type);
        }
        (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable);
    }
#line 1939 "source/parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 327 "source/explc.y" /* yacc.c:1646  */
    {
        struct LocalSymbol symbol = (yyvsp[0].localSymbolTable)->symbols[0];
        InstallLocalSymbol((yyvsp[-2].localSymbolTable), symbol.name, 0);
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
        (yyval.localSymbolTable) = (yyvsp[-2].localSymbolTable);
    }
#line 1951 "source/parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 334 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 1957 "source/parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 337 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.localSymbolTable) = (struct LocalSymbolTable*)malloc(sizeof(struct LocalSymbolTable));
        (yyval.localSymbolTable)->size = 0;
        InstallLocalSymbol((yyval.localSymbolTable), (yyvsp[0].astNode)->varName, 0);
    }
#line 1967 "source/parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 344 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 1973 "source/parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 345 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = 0; }
#line 1979 "source/parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 348 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, PLUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));      }
#line 1985 "source/parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 349 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MINUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 1991 "source/parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 350 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MUL_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 1997 "source/parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 351 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DIV_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2003 "source/parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 352 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MOD_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2009 "source/parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 353 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2015 "source/parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 354 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2021 "source/parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 355 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2027 "source/parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 356 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2033 "source/parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 357 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQUAL_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));  }
#line 2039 "source/parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 358 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, NOT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));    }
#line 2045 "source/parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 359 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, AND_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));          }
#line 2051 "source/parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 360 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, OR_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));           }
#line 2057 "source/parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 361 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2063 "source/parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 362 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2069 "source/parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 363 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2075 "source/parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 364 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2081 "source/parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 365 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[0].astNode), 0); }
#line 2087 "source/parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 366 "source/explc.y" /* yacc.c:1646  */
    { 
        (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-3].astNode), 0); 
        (yyval.astNode)->argList = (yyvsp[-1].nodeList)->nodes;
        (yyval.astNode)->argCount = (yyvsp[-1].nodeList)->size;
    }
#line 2097 "source/parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 371 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 2103 "source/parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 374 "source/explc.y" /* yacc.c:1646  */
    {
        InsertASTNode((yyvsp[-2].nodeList), *(yyvsp[0].astNode));
        (yyval.nodeList) = (yyvsp[-2].nodeList);
        free((yyvsp[0].astNode));
    }
#line 2113 "source/parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 379 "source/explc.y" /* yacc.c:1646  */
    { 
        (yyval.nodeList) = (struct ASTNodeList*)malloc(sizeof(struct ASTNodeList));
        InsertASTNode((yyval.nodeList), *(yyvsp[0].astNode));
    }
#line 2122 "source/parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 384 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2128 "source/parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 385 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 2134 "source/parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 386 "source/explc.y" /* yacc.c:1646  */
    {
            struct ASTNode *index = CreateASTNode(0, 0, INDEX_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-1].astNode)); 
            (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-6].astNode), index);
        }
#line 2143 "source/parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 390 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DEREF_NODE, 0, (yyvsp[0].astNode), 0);  }
#line 2149 "source/parser.c" /* yacc.c:1646  */
    break;


#line 2153 "source/parser.c" /* yacc.c:1646  */
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
#line 391 "source/explc.y" /* yacc.c:1906  */


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
    printf("line:%d [%s], yytext: '%s'\n", line - 1, s, yytext);
    return 1;
}

char *ExtractFileName(const char *fileName)
{
    int len = strlen(fileName);

    int startPos = 0;
    int endPos = len - 1;

    int n = 1;
    while(n <= len)
    {
        if(fileName[len - n] == '.')
        {
            endPos = len - n - 1;
        }
        else if(fileName[len - n] == '/')
        {
            startPos = len - n + 1;
            break;
        }
        n++;
    }

    int finalLen = endPos - startPos + 1;
    char *result = malloc(finalLen + 1);
    strncpy(result, &fileName[startPos], finalLen);
    result[finalLen] = 0;

    return result;
}

char *AddFileExtension(const char *fileName, const char *extension)
{
    int len = strlen(fileName) + strlen(extension) + 2;
    char *result = malloc(len);
    strncpy(result, fileName, strlen(fileName));
    result[strlen(fileName)] = '.';
    strncpy(result + strlen(fileName) + 1, extension, strlen(extension));
    result[len - 1] = 0;
    return result;
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
        printf("[INFO] generating xsm machine code ...\n");

        char *outFile = "out.xsm";

        FILE *output = fopen(outFile, "w");
        if(output)
        {
            GenerateCode(node, output);
            fprintf(output, "$%d\n", globalSymbolTable.staticAddressOffset);
        }
        else
        {
            printf("[ERROR] failed to create output file!\n");
            exit(1);
        }
        fclose(output);

        printf("[INFO] compilation finished, output file -> '%s'\n", outFile);
    }
    else if(compilerMode == COMPILE_FOR_X86)
    {
        printf("[INFO] generating x86 machine code ...\n");
        
        char *inFile = ExtractFileName(inputFileName);
        char *outFile = AddFileExtension(inFile  , "asm");
        free(inFile);
        FILE *output = fopen(outFile, "w");
        if(output)
        {
            x86AssemblyBackend_32bit(node, output);
        }
        else
        {
            printf("[ERROR] failed to create output file!\n");
            exit(1);
        }
        fclose(output);

        printf("[INFO] compilation finished, output file -> '%s'\n", outFile);
    }
    else if(compilerMode == COMPILE_TO_C)
    {
        printf("[INFO] generating c code ...\n");

        char *inFile = ExtractFileName(inputFileName);
        char *outFile = AddFileExtension(inFile  , "c");
        free(inFile);

        FILE *output = fopen(outFile, "w");
        if(output)
        {
            C_backend(node, output);
        }
        else
        {
            printf("[ERROR] failed to create output file!\n");
            exit(1);
        }
        fclose(output);

        printf("[INFO] compilation finished, output file -> '%s'\n", outFile);
    }
}

void PrintUsage()
{
    printf("Usage: ./explc [options] source file\n");
    printf("[options]\n");
    printf("  -p: print abstract syntax tree\n");
    printf("  -xsm: compiles to xsm machine code\n");
    printf("  -x86: compiles to x86 32 bit nasm assembly\n");
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
                compilerMode = PRINT_AST;
            }
            else if(!strcmp(argv[1], "-xsm"))
            {
                compilerMode = COMPILE_FOR_XSM;
            }
            else if(!strcmp(argv[1], "-x86"))
            {
                compilerMode = COMPILE_FOR_X86;
            }
            else if(!strcmp(argv[1], "-c"))
            {
                compilerMode = COMPILE_TO_C;
            }
            else
            {
                printf("[ERROR] unknown option : '%s' !\n", argv[1]);
                PrintUsage();
                return 1;
            }

            inputFileName = strdup(argv[2]);
            printf("[SOURCE] '%s'\n", inputFileName);


            yyparse();
            
            free(inputFileName);
        }
        else
        {
            printf("[ERROR] failed to open source file : '%s'\n", argv[2]);
        }
    }
    else 
    {
        PrintUsage();
    }

    return 0;
}
