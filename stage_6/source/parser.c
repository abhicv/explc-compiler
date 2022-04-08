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

#line 107 "source/parser.c" /* yacc.c:339  */

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
#line 42 "source/explc.y" /* yacc.c:355  */

    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct FieldList *fieldList;
    struct ASTNodeList *nodeList;

#line 242 "source/parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SOURCE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 259 "source/parser.c" /* yacc.c:358  */

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   484

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

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
      47,    48,     2,     2,    49,     2,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    92,   101,   112,   115,   117,   118,   120,
     147,   153,   155,   165,   166,   169,   170,   171,   172,   173,
     174,   175,   176,   179,   183,   188,   191,   194,   197,   200,
     201,   202,   203,   206,   211,   218,   222,   225,   231,   234,
     240,   243,   246,   249,   252,   253,   256,   257,   260,   278,
     284,   287,   296,   306,   317,   321,   332,   333,   336,   378,
     387,   388,   391,   404,   418,   419,   422,   430,   433,   448,
     454,   457,   465,   466,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   493,   496,   501,   507,   508,   509,
     513,   514,   516,   517
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_LITERAL", "STRING_LITERAL",
  "IDENTIFIER", "NULL_TOKEN", "DECL", "ENDDECL", "TYPE_TOKEN",
  "ENDTYPE_TOKEN", "BEGIN_TOKEN", "END_TOKEN", "READ_TOKEN", "WRITE_TOKEN",
  "INIT_TOKEN", "ALLOC_TOKEN", "FREE_TOKEN", "IF", "THEN", "ELSE", "ELIF",
  "ENDIF", "WHILE", "DO", "ENDWHILE", "BREAK", "CONTINUE", "RETURN", "AND",
  "OR", "LT", "GT", "LT_EQ", "GT_EQ", "EQUAL_EQ", "NOT_EQ", "EQ", "PLUS",
  "MINUS", "MUL", "DIV", "MOD", "ADDR_OF", "'{'", "'}'", "';'", "'('",
  "')'", "','", "'['", "']'", "'.'", "$accept", "program", "TYPE",
  "type_def_block", "type_def_list", "type_def", "field_decl_list",
  "field_decl", "stmt_list", "statement", "read_stmt", "write_stmt",
  "init_stmt", "alloc_stmt", "free_stmt", "assign_stmt", "if_stmt",
  "elif_stmt_list", "elif_stmt", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "global_decl_block", "global_decl_list",
  "global_decl", "global_id_list", "global_id", "function_def_block",
  "function_def", "param_list", "param", "local_decl_block",
  "local_decl_list", "local_decl", "local_id_list", "local_id",
  "function_body", "expr", "arg_list", "l_value", "field", YY_NULLPTR
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
     295,   296,   297,   298,   123,   125,    59,    40,    41,    44,
      91,    93,    46
};
# endif

#define YYPACT_NINF -114

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-114)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      30,  -114,    46,    23,    36,    50,    73,    88,    88,  -114,
    -114,    -2,    67,  -114,   -25,    19,  -114,  -114,    34,    88,
      88,  -114,    32,    -2,    43,  -114,  -114,  -114,    88,  -114,
    -114,    88,    88,    88,    84,  -114,  -114,    -2,    97,    -3,
    -114,     3,    25,  -114,    68,    57,  -114,    59,  -114,  -114,
    -114,   114,    94,    88,  -114,    62,  -114,  -114,   121,  -114,
     136,    86,   142,   103,  -114,   158,    93,  -114,   157,   122,
    -114,  -114,    54,  -114,  -114,  -114,    82,  -114,   129,   130,
     135,   139,   133,   152,    10,    10,   176,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,   131,   149,  -114,  -114,
     158,    10,   206,     4,    10,    10,    10,  -114,  -114,  -114,
    -114,   -27,  -114,    12,    10,   382,  -114,  -114,  -114,  -114,
      80,   207,  -114,   234,  -114,   165,    12,   262,   282,   302,
       1,  -114,   322,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,  -114,   173,   174,   184,
     172,   186,   187,   400,  -114,   192,   191,   195,   200,   228,
     224,  -114,   418,    77,  -114,   430,   430,   107,   107,   107,
     107,   442,   442,   132,   132,  -114,  -114,  -114,   202,   203,
      10,  -114,  -114,  -114,  -114,    10,  -114,   209,  -114,   231,
     231,  -114,    10,  -114,  -114,   342,   248,  -114,   138,   182,
     418,  -114,  -114,   231,   213,   210,   171,  -114,   215,   201,
      10,  -114,   231,   216,  -114,  -114,   259,   362,   212,  -114,
    -114,   287,   261,   231,  -114,   231
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     0,     0,     0,     0,     4,    57,
      45,     0,     0,    47,     0,     0,     8,     1,     0,     0,
       3,    56,    51,     0,     0,    50,    44,    46,     0,     6,
       7,    61,     2,    61,     0,    54,    48,     0,     0,     0,
      11,     0,     0,    60,     0,     0,    49,     0,     9,    10,
      62,     0,     0,     0,    55,    52,    12,    63,     0,    59,
       0,     0,     0,     0,    65,     0,     0,    67,     0,     0,
      53,    71,     0,    70,    64,    66,    97,    73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,   101,    58,    68,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    89,
      90,    97,    87,     0,     0,     0,    91,   100,    72,    13,
       0,     0,    69,     0,   103,     0,     0,     0,     0,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,   102,    98,     0,     0,     0,     0,
       0,    94,    96,     0,    88,    85,    86,    79,    81,    80,
      82,    83,    84,    74,    75,    76,    77,    78,     0,     0,
       0,    30,    31,    32,    29,     0,    24,     0,    25,     0,
       0,    93,     0,    26,    27,     0,     0,    23,     0,     0,
      95,    28,    99,     0,     0,     0,     0,    38,     0,     0,
       0,    36,     0,     0,    37,    40,     0,     0,     0,    33,
      35,     0,     0,     0,    34,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,    76,  -114,  -114,   238,  -114,   269,  -113,   -85,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   113,  -114,
    -114,  -114,  -114,   303,  -114,   313,  -114,   -11,    14,     2,
     293,   274,  -114,  -114,   263,  -114,   239,  -114,   -74,  -114,
     -68,  -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    15,    16,    39,    40,    86,    87,
      88,    89,   150,   151,   152,    90,    91,   206,   207,    92,
      93,    94,    95,     7,    12,    13,    24,    25,     8,     9,
      42,    43,    62,    66,    67,    72,    73,    69,   115,   163,
     116,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      96,   119,     1,    22,   109,   110,   111,   112,    50,   125,
      21,   117,    35,   109,   110,   111,   112,    76,    96,    28,
     130,    20,    21,   101,    14,   102,    46,   123,    14,    29,
     127,   128,   129,    32,    21,     1,    17,     2,    23,     3,
     132,    85,    48,    51,   113,   131,   153,   126,   114,   161,
      85,     1,    85,   113,    10,    18,   162,   114,   157,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,     1,    52,    53,    26,   198,   199,    11,    33,
       2,    31,    34,   109,   110,   111,   112,    45,    11,    36,
     209,     1,    37,     1,    64,   147,   148,   149,     1,   218,
      99,    74,    47,   100,    38,    56,   195,    41,    55,    41,
     225,   196,    60,   119,   119,    38,    54,    53,   200,    57,
      85,    96,    96,   113,   119,   191,   192,   114,    61,    41,
      96,    96,   101,   119,   102,    96,   217,    65,    58,    63,
     119,    96,    65,    76,    96,   141,   142,   143,   144,   145,
      96,    78,    79,    68,    70,    96,    80,    96,   203,   204,
     205,    81,    76,    71,    82,    83,    84,    98,   120,    77,
      78,    79,   143,   144,   145,    80,   103,   104,    85,   107,
      81,    76,   105,    82,    83,    84,   106,    76,   118,    78,
      79,   212,   204,   213,    80,    78,    79,    85,   108,    81,
      80,   121,    82,    83,    84,    81,    76,   208,    82,    83,
      84,   124,   154,   156,    78,    79,    85,    76,   181,    80,
     178,   179,    85,   216,    81,    78,    79,    82,    83,    84,
      80,   180,   182,   183,   222,    81,    76,   186,    82,    83,
      84,    85,   185,   187,    78,    79,   188,   189,   190,    80,
     193,   194,    85,    30,    81,   197,   211,    82,    83,    84,
     210,   215,   219,   133,   134,   135,   136,   137,   138,   139,
     140,    85,   141,   142,   143,   144,   145,   133,   134,   135,
     136,   137,   138,   139,   140,   155,   141,   142,   143,   144,
     145,   133,   134,   135,   136,   137,   138,   139,   140,   202,
     141,   142,   143,   144,   145,   220,   223,   224,    49,    19,
     158,   133,   134,   135,   136,   137,   138,   139,   140,   214,
     141,   142,   143,   144,   145,    27,    44,    59,     0,    75,
     159,   133,   134,   135,   136,   137,   138,   139,   140,   122,
     141,   142,   143,   144,   145,     0,     0,     0,     0,     0,
     160,   133,   134,   135,   136,   137,   138,   139,   140,     0,
     141,   142,   143,   144,   145,     0,     0,     0,     0,     0,
     164,   133,   134,   135,   136,   137,   138,   139,   140,     0,
     141,   142,   143,   144,   145,     0,     0,     0,     0,     0,
     201,   133,   134,   135,   136,   137,   138,   139,   140,     0,
     141,   142,   143,   144,   145,     0,     0,     0,     0,     0,
     221,   133,   134,   135,   136,   137,   138,   139,   140,     0,
     141,   142,   143,   144,   145,     0,     0,     0,   146,   133,
     134,   135,   136,   137,   138,   139,   140,     0,   141,   142,
     143,   144,   145,     0,     0,     0,   184,   133,   134,   135,
     136,   137,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   135,   136,   137,   138,   139,   140,     0,   141,   142,
     143,   144,   145,   135,   136,   137,   138,     0,     0,     0,
     141,   142,   143,   144,   145
};

static const yytype_int16 yycheck[] =
{
      68,    86,     5,     5,     3,     4,     5,     6,     5,     5,
       8,    85,    23,     3,     4,     5,     6,     5,    86,    44,
      47,     7,    20,    50,     5,    52,    37,   101,     5,    10,
     104,   105,   106,    19,    32,     5,     0,     7,    40,     9,
     114,    40,    45,    40,    43,   113,   120,    43,    47,    48,
      40,     5,    40,    43,     8,     5,   130,    47,   126,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,     5,    48,    49,     8,   189,   190,     2,    47,
       7,    47,    50,     3,     4,     5,     6,     3,    12,    46,
     203,     5,    49,     5,     8,    15,    16,    17,     5,   212,
      46,     8,     5,    49,    28,    46,   180,    31,    51,    33,
     223,   185,    50,   198,   199,    39,    48,    49,   192,     5,
      40,   189,   190,    43,   209,    48,    49,    47,     7,    53,
     198,   199,    50,   218,    52,   203,   210,    61,    44,     3,
     225,   209,    66,     5,   212,    38,    39,    40,    41,    42,
     218,    13,    14,    11,    51,   223,    18,   225,    20,    21,
      22,    23,     5,     5,    26,    27,    28,    45,    37,    12,
      13,    14,    40,    41,    42,    18,    47,    47,    40,    46,
      23,     5,    47,    26,    27,    28,    47,     5,    12,    13,
      14,    20,    21,    22,    18,    13,    14,    40,    46,    23,
      18,    52,    26,    27,    28,    23,     5,    25,    26,    27,
      28,     5,     5,    48,    13,    14,    40,     5,    46,    18,
      47,    47,    40,    22,    23,    13,    14,    26,    27,    28,
      18,    47,    46,    46,    22,    23,     5,    46,    26,    27,
      28,    40,    50,    48,    13,    14,    46,    19,    24,    18,
      48,    48,    40,    15,    23,    46,    46,    26,    27,    28,
      47,    46,    46,    29,    30,    31,    32,    33,    34,    35,
      36,    40,    38,    39,    40,    41,    42,    29,    30,    31,
      32,    33,    34,    35,    36,    51,    38,    39,    40,    41,
      42,    29,    30,    31,    32,    33,    34,    35,    36,    51,
      38,    39,    40,    41,    42,    46,    19,    46,    39,     6,
      48,    29,    30,    31,    32,    33,    34,    35,    36,   206,
      38,    39,    40,    41,    42,    12,    33,    53,    -1,    66,
      48,    29,    30,    31,    32,    33,    34,    35,    36,   100,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      48,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      48,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      48,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      48,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    46,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    46,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    38,    39,    40,    41,
      42,    31,    32,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    31,    32,    33,    34,    -1,    -1,    -1,
      38,    39,    40,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     7,     9,    54,    55,    56,    76,    81,    82,
       8,    55,    77,    78,     5,    57,    58,     0,     5,    76,
      81,    82,     5,    40,    79,    80,     8,    78,    44,    10,
      58,    47,    81,    47,    50,    80,    46,    49,    55,    59,
      60,    55,    83,    84,    83,     3,    80,     5,    45,    60,
       5,    40,    48,    49,    48,    51,    46,     5,    44,    84,
      50,     7,    85,     3,     8,    55,    86,    87,    11,    90,
      51,     5,    88,    89,     8,    87,     5,    12,    13,    14,
      18,    23,    26,    27,    28,    40,    61,    62,    63,    64,
      68,    69,    72,    73,    74,    75,    93,    94,    45,    46,
      49,    50,    52,    47,    47,    47,    47,    46,    46,     3,
       4,     5,     6,    43,    47,    91,    93,    91,    12,    62,
      37,    52,    89,    91,     5,     5,    43,    91,    91,    91,
      47,    93,    91,    29,    30,    31,    32,    33,    34,    35,
      36,    38,    39,    40,    41,    42,    46,    15,    16,    17,
      65,    66,    67,    91,     5,    51,    48,    93,    48,    48,
      48,    48,    91,    92,    48,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    47,    47,
      47,    46,    46,    46,    46,    50,    46,    48,    46,    19,
      24,    48,    49,    48,    48,    91,    91,    46,    61,    61,
      91,    48,    51,    20,    21,    22,    70,    71,    25,    61,
      47,    46,    20,    22,    71,    46,    22,    91,    61,    46,
      46,    48,    22,    19,    46,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    54,    55,    56,    57,    57,    58,
      59,    59,    60,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    65,    66,    67,    68,
      68,    68,    68,    69,    69,    69,    69,    70,    70,    71,
      72,    73,    74,    75,    76,    76,    77,    77,    78,    79,
      79,    80,    80,    80,    80,    80,    81,    81,    82,    83,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    92,    93,    93,    93,
      93,    93,    94,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     1,     1,     3,     2,     1,     4,
       2,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     5,     5,     3,     3,     4,     4,
       4,     4,     4,     9,    11,    10,     8,     2,     1,     6,
       8,     2,     2,     3,     3,     2,     2,     1,     3,     3,
       1,     1,     4,     7,     2,     4,     2,     1,     9,     3,
       1,     0,     2,     3,     3,     2,     2,     1,     3,     3,
       1,     1,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     1,
       1,     1,     2,     4,     3,     3,     1,     1,     4,     7,
       2,     1,     3,     3
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
#line 82 "source/explc.y" /* yacc.c:1646  */
    {
        CheckSemantics((yyvsp[0].astNode));
        Compile((yyvsp[0].astNode));
        PrintTypeTable(typeTable);

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
#line 1557 "source/parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 92 "source/explc.y" /* yacc.c:1646  */
    {
        CheckSemantics((yyvsp[0].astNode));
        Compile((yyvsp[0].astNode));

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
#line 1571 "source/parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 101 "source/explc.y" /* yacc.c:1646  */
    {
        CheckSemantics((yyvsp[0].astNode));
        Compile((yyvsp[0].astNode));

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
#line 1585 "source/parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 112 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1591 "source/parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 120 "source/explc.y" /* yacc.c:1646  */
    {
    struct Type type = {0};
    type.name = (yyvsp[-3].astNode)->varName;
    type.fieldList = *((yyvsp[-1].fieldList));
    type.size = (yyvsp[-1].fieldList)->count;

    if(type.size > 8)
    {
        printf("error: number of fields for a type should be less than or equal to 8\n");
        exit(1);
    }

    InstallType(&typeTable, type);

    for(int n = 0; n < type.fieldList.count; n++)
    {
        int typeIndex = LookUpTypeTableIndex(typeTable, type.fieldList.fields[n].typeName);

        if(typeIndex == -1)
        {
            printf("error: unkwown type for field '%s'\n", type.fieldList.fields[n].name);
            exit(1);
        }
        typeTable.types[typeTable.size - 1].fieldList.fields[n].typeIndex = typeIndex;
    }
}
#line 1622 "source/parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 147 "source/explc.y" /* yacc.c:1646  */
    {
        InstallField((yyvsp[-1].fieldList), (yyvsp[0].fieldList)->fields[0]);
        free((yyvsp[0].fieldList)->fields);
        free((yyvsp[0].fieldList));
        (yyval.fieldList) = (yyvsp[-1].fieldList);
    }
#line 1633 "source/parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "source/explc.y" /* yacc.c:1646  */
    { (yyval.fieldList) = (yyvsp[0].fieldList); }
#line 1639 "source/parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 155 "source/explc.y" /* yacc.c:1646  */
    {
    (yyval.fieldList) = (struct FieldList*)malloc(sizeof(struct FieldList));
    (yyval.fieldList)->count = 0;
    struct Field field = {0};
    field.name = (yyvsp[-1].astNode)->varName;
    field.typeIndex = -1;
    field.typeName = (yyvsp[-2].astNode)->varName;
    InstallField((yyval.fieldList), field);
}
#line 1653 "source/parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 165 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1659 "source/parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 166 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1665 "source/parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 169 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1671 "source/parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 170 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1677 "source/parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 171 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1683 "source/parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 172 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1689 "source/parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 173 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1695 "source/parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 174 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1701 "source/parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 175 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1707 "source/parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 176 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1713 "source/parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 179 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *addrNode = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[-2].astNode), 0);
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, addrNode, 0);
    }
#line 1722 "source/parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 183 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, (yyvsp[-2].astNode), 0);
    }
#line 1730 "source/parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 188 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WRITE_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 1736 "source/parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 191 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, INIT_MEM_NODE, 0, 0, 0); }
#line 1742 "source/parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 194 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ALLOC_MEM_NODE, 0, 0, 0); }
#line 1748 "source/parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 197 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FREE_MEM_NODE, 0, (yyvsp[-1].astNode), 0); }
#line 1754 "source/parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 200 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1760 "source/parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 201 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1766 "source/parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 202 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1772 "source/parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 203 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1778 "source/parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 206 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-6].astNode), (yyvsp[-3].astNode));
        (yyvsp[-2].astNode)->left = (yyvsp[-3].astNode);
        (yyval.astNode)->right = (yyvsp[-2].astNode);
    }
#line 1788 "source/parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 211 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-8].astNode), (yyvsp[-5].astNode));
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-4].astNode));
        ifNode->right = CreateASTNode(0, 0, BRANCH_NODE, 0, ifNode->right, (yyvsp[-2].astNode));
        (yyvsp[-4].astNode)->left = (yyvsp[-5].astNode);
        (yyval.astNode)->right = (yyvsp[-4].astNode);
    }
#line 1800 "source/parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 218 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *branch = CreateASTNode(0, 0, BRANCH_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-2].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-7].astNode), branch);
    }
#line 1809 "source/parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 222 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1815 "source/parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 225 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-1].astNode));
        (yyvsp[0].astNode)->left = ifNode->right;
        ifNode->right = (yyvsp[0].astNode);
        (yyval.astNode) = (yyvsp[-1].astNode);
    }
#line 1826 "source/parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 231 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1832 "source/parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 234 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *ifNode = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-3].astNode), (yyvsp[0].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, BRANCH_NODE, 0, 0, ifNode);
    }
#line 1841 "source/parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 240 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WHILE_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1847 "source/parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 243 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, BREAK_NODE, 0, 0, 0); }
#line 1853 "source/parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 246 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }
#line 1859 "source/parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 249 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, RETURN_NODE, 0, (yyvsp[-1].astNode), 0); }
#line 1865 "source/parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 260 "source/explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[-1].globalSymbolTable)->size; n++)
        {
            (yyvsp[-1].globalSymbolTable)->symbols[n].typeIndex = LookUpTypeTableIndex(typeTable, (yyvsp[-2].astNode)->varName);

            if((yyvsp[-1].globalSymbolTable)->symbols[n].typeIndex == -1)
            {
                printf("error: unkwown type '%s'\n", (yyvsp[-2].astNode)->varName);
                exit(1);
            }

            InstallGlobalSymbol(&globalSymbolTable, (yyvsp[-1].globalSymbolTable)->symbols[n]);
        }
        free((yyvsp[-1].globalSymbolTable)->symbols);
        free((yyvsp[-1].globalSymbolTable));
    }
#line 1886 "source/parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 278 "source/explc.y" /* yacc.c:1646  */
    {
        InstallGlobalSymbol((yyvsp[-2].globalSymbolTable), (yyvsp[0].globalSymbolTable)->symbols[0]);
        free((yyvsp[0].globalSymbolTable)->symbols);
        free((yyvsp[0].globalSymbolTable));
        (yyval.globalSymbolTable) = (yyvsp[-2].globalSymbolTable);
    }
#line 1897 "source/parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 284 "source/explc.y" /* yacc.c:1646  */
    { (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable); }
#line 1903 "source/parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 287 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[0].astNode)->varName;
        symbol.size = 1;
        symbol.functionLabel = -1;
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1917 "source/parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 296 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[-3].astNode)->varName;
        symbol.size = (yyvsp[-1].astNode)->val;
        symbol.arrayDim = 1;
        symbol.functionLabel = -1;
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1932 "source/parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 306 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[-6].astNode)->varName;
        symbol.size = (yyvsp[-4].astNode)->val * (yyvsp[-1].astNode)->val;
        symbol.colSize = (yyvsp[-1].astNode)->val;
        symbol.arrayDim = 2;
        symbol.functionLabel = -1;
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1948 "source/parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 317 "source/explc.y" /* yacc.c:1646  */
    {
        (yyvsp[0].globalSymbolTable)->symbols[0].typeIndex = -1;
        (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable);
    }
#line 1957 "source/parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 321 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[-3].astNode)->varName;
        symbol.functionLabel = functionLabelCounter++;
        symbol.paramList = (yyvsp[-1].paramList);
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1971 "source/parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 332 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1977 "source/parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 333 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1983 "source/parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 336 "source/explc.y" /* yacc.c:1646  */
    {

        (yyval.astNode) = CreateASTNode(0, (yyvsp[-7].astNode)->varName, FUNCTION_DEF_NODE, 0, (yyvsp[-1].astNode), 0);
        (yyval.astNode)->returnTypeIndex = LookUpTypeTableIndex(typeTable, (yyvsp[-8].astNode)->varName);

        if((yyval.astNode)->returnTypeIndex == -1)
        {
            printf("error: unkwown return type for function '%s'\n", (yyvsp[-7].astNode)->varName);
            exit(1);
        }

        (yyval.astNode)->paramList = (yyvsp[-5].paramList);

        struct LocalSymbolTable *localSymbolTable = (struct LocalSymbolTable *)malloc(sizeof(struct LocalSymbolTable));
        localSymbolTable->size = 0;
        localSymbolTable->symbols = 0;

        // installing parameters into local symbol table
        if((yyvsp[-5].paramList))
        {
            for(int n = 0; n < (yyvsp[-5].paramList)->size; n++)
            {
                struct LocalSymbol symbol = {0};
                symbol.name = (yyvsp[-5].paramList)->params[n].name;
                symbol.typeIndex = (yyvsp[-5].paramList)->params[n].typeIndex;
                symbol.binding = -(n + 3);
                InstallLocalSymbol(localSymbolTable, symbol);
            }
        }

        //installing local variables into local symbol table
        if((yyvsp[-2].localSymbolTable))
        {
            for(int n = 0; n < (yyvsp[-2].localSymbolTable)->size; n++)
            {
                (yyvsp[-2].localSymbolTable)->symbols[n].binding = n + 1;
                InstallLocalSymbol(localSymbolTable, (yyvsp[-2].localSymbolTable)->symbols[n]);
            }
        }
        (yyval.astNode)->localSymbolTable = localSymbolTable;
}
#line 2029 "source/parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 378 "source/explc.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].paramList) && (yyvsp[0].paramList))
        {
            InstallParam((yyvsp[-2].paramList), (yyvsp[0].paramList)->params[0].name, (yyvsp[0].paramList)->params[0].typeIndex);
            free((yyvsp[0].paramList)->params);
            free((yyvsp[0].paramList));
        }
        (yyval.paramList) = (yyvsp[-2].paramList);
    }
#line 2043 "source/parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 387 "source/explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[0].paramList); }
#line 2049 "source/parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 388 "source/explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = 0; }
#line 2055 "source/parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 391 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.paramList) = (struct ParamList*)malloc(sizeof(struct ParamList));
        (yyval.paramList)->size = 0;
        int typeIndex = LookUpTypeTableIndex(typeTable, (yyvsp[-1].astNode)->varName);

        if(typeIndex == -1)
        {
            printf("error: unkwown type '%s'\n", (yyvsp[-1].astNode)->varName);
            exit(1);
        }

        InstallParam((yyval.paramList), (yyvsp[0].astNode)->varName, typeIndex);
    }
#line 2073 "source/parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 404 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.paramList) = (struct ParamList*)malloc(sizeof(struct ParamList));
        (yyval.paramList)->size = 0;
        int typeIndex = LookUpTypeTableIndex(typeTable, (yyvsp[-2].astNode)->varName);

        if(typeIndex == -1)
        {
            printf("error: unkwown type '%s'\n", (yyvsp[-2].astNode)->varName);
            exit(1);
        }
        InstallParam((yyval.paramList), (yyvsp[0].astNode)->varName, typeIndex);
    }
#line 2090 "source/parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 418 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable); }
#line 2096 "source/parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 419 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = 0; }
#line 2102 "source/parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 422 "source/explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[0].localSymbolTable)->size; n++)
        {
            InstallLocalSymbol((yyvsp[-1].localSymbolTable), (yyvsp[0].localSymbolTable)->symbols[n]);
        }
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
    }
#line 2115 "source/parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 430 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 2121 "source/parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 433 "source/explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[-1].localSymbolTable)->size; n++)
        {
            (yyvsp[-1].localSymbolTable)->symbols[n].typeIndex = LookUpTypeTableIndex(typeTable, (yyvsp[-2].astNode)->varName);

            if((yyvsp[-1].localSymbolTable)->symbols[n].typeIndex == -1)
            {
                printf("error: unkwown type '%s'\n", (yyvsp[-2].astNode)->varName);
                exit(1);
            }
        }
        (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable);
    }
#line 2139 "source/parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 448 "source/explc.y" /* yacc.c:1646  */
    {
        InstallLocalSymbol((yyvsp[-2].localSymbolTable), (yyvsp[0].localSymbolTable)->symbols[0]);
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
        (yyval.localSymbolTable) = (yyvsp[-2].localSymbolTable);
    }
#line 2150 "source/parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 454 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 2156 "source/parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 457 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.localSymbolTable) = (struct LocalSymbolTable*)malloc(sizeof(struct LocalSymbolTable));
        struct LocalSymbol symbol = {0};
        symbol.name = (yyvsp[0].astNode)->varName;
        InstallLocalSymbol((yyval.localSymbolTable), symbol);
    }
#line 2167 "source/parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 465 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2173 "source/parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 466 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = 0; }
#line 2179 "source/parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 469 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, PLUS_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));      }
#line 2185 "source/parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 470 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MINUS_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2191 "source/parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 471 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MUL_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2197 "source/parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 472 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DIV_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2203 "source/parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 473 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MOD_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2209 "source/parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 474 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2215 "source/parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 475 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_EQ_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2221 "source/parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 476 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2227 "source/parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 477 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_EQ_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2233 "source/parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 478 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQUAL_EQ_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));  }
#line 2239 "source/parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 479 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, NOT_EQ_OP_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));    }
#line 2245 "source/parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 480 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, AND_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));          }
#line 2251 "source/parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 481 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, OR_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode));           }
#line 2257 "source/parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 482 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, NULL_NODE, 0, 0, 0);           }
#line 2263 "source/parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 483 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2269 "source/parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 484 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2275 "source/parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 485 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2281 "source/parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 486 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2287 "source/parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 487 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[0].astNode), 0); }
#line 2293 "source/parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 488 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-3].astNode), 0);
        (yyval.astNode)->argList = (yyvsp[-1].nodeList)->nodes;
        (yyval.astNode)->argCount = (yyvsp[-1].nodeList)->size;
    }
#line 2303 "source/parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 493 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 2309 "source/parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 496 "source/explc.y" /* yacc.c:1646  */
    {
        InsertASTNode((yyvsp[-2].nodeList), *(yyvsp[0].astNode));
        (yyval.nodeList) = (yyvsp[-2].nodeList);
        free((yyvsp[0].astNode));
    }
#line 2319 "source/parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 501 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.nodeList) = (struct ASTNodeList*)malloc(sizeof(struct ASTNodeList));
        (yyval.nodeList)->size = 0;
        InsertASTNode((yyval.nodeList), *(yyvsp[0].astNode));
    }
#line 2329 "source/parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 507 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2335 "source/parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 508 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 2341 "source/parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 509 "source/explc.y" /* yacc.c:1646  */
    {
            struct ASTNode *index = CreateASTNode(0, 0, INDEX_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-1].astNode));
            (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-6].astNode), index);
        }
#line 2350 "source/parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 513 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DEREF_NODE, 0, (yyvsp[0].astNode), 0);  }
#line 2356 "source/parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 514 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2362 "source/parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 516 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FIELD_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2368 "source/parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 517 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FIELD_NODE, 0, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2374 "source/parser.c" /* yacc.c:1646  */
    break;


#line 2378 "source/parser.c" /* yacc.c:1646  */
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
#line 520 "source/explc.y" /* yacc.c:1906  */


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
