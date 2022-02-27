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

#line 103 "y.tab.c" /* yacc.c:339  */

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
#line 38 "explc.y" /* yacc.c:355  */

    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct ASTNodeList *nodeList;
    int type;

#line 230 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 247 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   545

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  189

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
      41,    42,     2,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
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
       0,    77,    77,    93,    94,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   108,   112,   117,   120,   123,   128,
     135,   139,   142,   148,   151,   157,   160,   163,   166,   169,
     170,   173,   174,   176,   177,   180,   192,   200,   203,   211,
     219,   227,   231,   240,   241,   244,   402,   411,   412,   415,
     420,   427,   428,   431,   440,   443,   452,   459,   462,   469,
     470,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     496,   499,   504,   509,   510,   511,   515
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
  "MINUS", "MUL", "DIV", "MOD", "ADDR_OF", "';'", "'('", "')'", "','",
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
      59,    40,    41,    44,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF -153

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-153)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,    87,    43,    20,  -153,  -153,  -153,     1,    96,  -153,
    -153,    71,    20,  -153,    30,     1,    32,  -153,  -153,  -153,
      39,  -153,    20,    82,  -153,  -153,     1,    20,     6,    17,
    -153,    45,  -153,    85,  -153,   105,  -153,    20,    73,    69,
    -153,  -153,   119,   125,    90,   112,   138,  -153,  -153,   132,
     136,  -153,   127,   106,  -153,   104,  -153,  -153,  -153,  -153,
    -153,   111,  -153,   113,   115,   120,   123,   133,   134,   121,
     121,    25,   121,   166,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,   435,   139,  -153,  -153,   132,    -1,   121,
       0,   121,   121,   121,  -153,  -153,   451,  -153,  -153,   131,
    -153,   345,  -153,  -153,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,  -153,   121,  -153,
    -153,   483,   116,   303,   140,    25,   363,   381,   399,  -153,
    -153,   495,   495,    29,    29,    29,    29,   507,   507,   -20,
     -20,  -153,  -153,  -153,   467,  -153,   121,   137,   143,   142,
     146,   150,   147,  -153,   483,   121,  -153,   151,  -153,   286,
     286,   324,  -153,    65,   196,  -153,   286,   135,   152,    81,
    -153,   153,   226,   121,  -153,   286,   154,  -153,  -153,   155,
     417,   256,  -153,  -153,   172,   156,   286,  -153,   286
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    29,    30,    32,     0,     0,    34,
       1,     0,     2,    44,    38,     0,     0,    37,    31,    33,
       0,    43,    48,     0,    41,    35,     0,    48,     0,     0,
      47,     0,    36,     0,    49,     0,    42,     0,    39,     0,
      50,    46,     0,     0,     0,     0,     0,    40,    52,     0,
       0,    54,     0,     0,    58,     0,    57,    51,    53,    75,
      76,    83,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,    77,    45,    55,     0,     0,     0,
       0,     0,     0,     0,    26,    27,     0,    77,    86,    83,
      78,     0,    59,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,     0,    56,
      80,    82,     0,     0,     0,     0,     0,     0,     0,    28,
      74,    72,    73,    66,    68,    67,    69,    70,    71,    61,
      62,    63,    64,    65,     0,    79,     0,    84,     0,     0,
       0,     0,     0,    17,    81,     0,    15,     0,    16,     0,
       0,     0,    14,     0,     0,    85,     0,     0,     0,     0,
      23,     0,     0,     0,    21,     0,     0,    22,    25,     0,
       0,     0,    18,    20,     0,     0,     0,    19,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,  -152,   -72,  -153,  -153,  -153,  -153,  -153,    28,
    -153,  -153,  -153,  -153,    12,  -153,  -153,   190,  -153,    10,
    -153,   191,   177,   169,  -153,  -153,   161,  -153,   126,  -153,
     -60,  -153,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    73,    74,    75,    76,    77,    78,   169,   170,
      79,    80,    81,    82,    28,     3,     8,     9,    16,    17,
      12,    13,    29,    30,    46,    50,    51,    55,    56,    53,
      83,   122,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      84,   103,    59,    60,    61,   124,    14,   163,   164,    96,
      98,    34,   101,     7,   172,    11,   114,   115,   116,   100,
       7,    84,     1,   181,    11,    24,     4,     5,   121,   123,
      99,   126,   127,   128,   188,    70,    32,    15,    71,   125,
      72,   120,    35,    10,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,    49,   144,    36,
      37,    70,    49,   112,   113,   114,   115,   116,    59,    60,
      61,    22,    25,   149,    23,    26,    20,    63,    64,    65,
      27,   166,   167,   168,    66,    31,   154,    67,    68,    69,
      38,   103,   103,     4,     5,   161,     6,   175,   167,   176,
     103,    70,     4,     5,    71,    18,    72,    84,    84,   103,
      40,    84,    84,   180,    84,    43,   103,    42,     4,     5,
      84,    48,    44,    84,    59,    60,    61,    39,    37,    84,
      59,    60,    61,    45,    84,    47,    84,    54,    62,    63,
      64,    65,     4,     5,    86,    57,    66,    87,    52,    67,
      68,    69,    88,    85,    90,    89,    91,    70,   145,   146,
      71,    92,    72,    70,    93,   159,    71,   160,    72,    59,
      60,    61,   118,    94,    95,    89,   173,   102,    63,    64,
      65,   155,   148,   156,   157,    66,   158,   186,    67,    68,
      69,   162,   174,   178,   182,   183,   187,   177,    19,    59,
      60,    61,    70,    21,    33,    71,    41,    72,    63,    64,
      65,    58,     0,   119,     0,    66,     0,   171,    67,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      60,    61,    70,     0,     0,    71,     0,    72,    63,    64,
      65,     0,     0,     0,   179,    66,     0,     0,    67,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      60,    61,    70,     0,     0,    71,     0,    72,    63,    64,
      65,     0,     0,     0,   185,    66,     0,     0,    67,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      60,    61,    70,     0,     0,    71,     0,    72,    63,    64,
      65,     0,     0,     0,     0,    66,     0,     0,    67,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,     0,     0,    71,     0,    72,   104,   105,
     106,   107,   108,   109,   110,   111,     0,   112,   113,   114,
     115,   116,     0,     0,     0,     0,     0,     0,   147,   104,
     105,   106,   107,   108,   109,   110,   111,     0,   112,   113,
     114,   115,   116,     0,     0,     0,     0,     0,     0,   165,
     104,   105,   106,   107,   108,   109,   110,   111,     0,   112,
     113,   114,   115,   116,     0,     0,     0,   130,   104,   105,
     106,   107,   108,   109,   110,   111,     0,   112,   113,   114,
     115,   116,     0,     0,     0,   150,   104,   105,   106,   107,
     108,   109,   110,   111,     0,   112,   113,   114,   115,   116,
       0,     0,     0,   151,   104,   105,   106,   107,   108,   109,
     110,   111,     0,   112,   113,   114,   115,   116,     0,     0,
       0,   152,   104,   105,   106,   107,   108,   109,   110,   111,
       0,   112,   113,   114,   115,   116,     0,     0,     0,   184,
     104,   105,   106,   107,   108,   109,   110,   111,     0,   112,
     113,   114,   115,   116,     0,   117,   104,   105,   106,   107,
     108,   109,   110,   111,     0,   112,   113,   114,   115,   116,
       0,   129,   104,   105,   106,   107,   108,   109,   110,   111,
       0,   112,   113,   114,   115,   116,     0,   153,   104,   105,
     106,   107,   108,   109,   110,   111,     0,   112,   113,   114,
     115,   116,   106,   107,   108,   109,   110,   111,     0,   112,
     113,   114,   115,   116,   106,   107,   108,   109,     0,     0,
       0,   112,   113,   114,   115,   116
};

static const yytype_int16 yycheck[] =
{
      52,    73,     3,     4,     5,     5,     5,   159,   160,    69,
      70,     5,    72,     1,   166,     3,    36,    37,    38,    71,
       8,    73,     8,   175,    12,    15,     6,     7,    88,    89,
       5,    91,    92,    93,   186,    36,    26,    36,    39,    39,
      41,    42,    36,     0,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    45,   118,    42,
      43,    36,    50,    34,    35,    36,    37,    38,     3,     4,
       5,    41,    40,   125,    44,    43,     5,    12,    13,    14,
      41,    16,    17,    18,    19,     3,   146,    22,    23,    24,
      45,   163,   164,     6,     7,   155,     9,    16,    17,    18,
     172,    36,     6,     7,    39,     9,    41,   159,   160,   181,
       5,   163,   164,   173,   166,    46,   188,    44,     6,     7,
     172,     9,     3,   175,     3,     4,     5,    42,    43,   181,
       3,     4,     5,     8,   186,    45,   188,     5,    11,    12,
      13,    14,     6,     7,    40,     9,    19,    43,    10,    22,
      23,    24,    41,    47,    41,    44,    41,    36,    42,    43,
      39,    41,    41,    36,    41,    15,    39,    20,    41,     3,
       4,     5,    33,    40,    40,    44,    41,    11,    12,    13,
      14,    44,    42,    40,    42,    19,    40,    15,    22,    23,
      24,    40,    40,    40,    40,    40,    40,   169,     8,     3,
       4,     5,    36,    12,    27,    39,    37,    41,    12,    13,
      14,    50,    -1,    87,    -1,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    36,    -1,    -1,    39,    -1,    41,    12,    13,
      14,    -1,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    36,    -1,    -1,    39,    -1,    41,    12,    13,
      14,    -1,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    36,    -1,    -1,    39,    -1,    41,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    39,    -1,    41,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    42,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    42,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    42,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    42,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    -1,    -1,    -1,    42,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    -1,    40,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      -1,    40,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    -1,    40,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    27,    28,    29,    30,    -1,    -1,
      -1,    34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    49,    63,     6,     7,     9,    62,    64,    65,
       0,    62,    68,    69,     5,    36,    66,    67,     9,    65,
       5,    69,    41,    44,    67,    40,    43,    41,    62,    70,
      71,     3,    67,    70,     5,    36,    42,    43,    45,    42,
       5,    71,    44,    46,     3,     8,    72,    45,     9,    62,
      73,    74,    10,    77,     5,    75,    76,     9,    74,     3,
       4,     5,    11,    12,    13,    14,    19,    22,    23,    24,
      36,    39,    41,    50,    51,    52,    53,    54,    55,    58,
      59,    60,    61,    78,    80,    47,    40,    43,    41,    44,
      41,    41,    41,    41,    40,    40,    78,    80,    78,     5,
      80,    78,    11,    51,    25,    26,    27,    28,    29,    30,
      31,    32,    34,    35,    36,    37,    38,    40,    33,    76,
      42,    78,    79,    78,     5,    39,    78,    78,    78,    40,
      42,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    42,    43,    45,    42,    80,
      42,    42,    42,    40,    78,    44,    40,    42,    40,    15,
      20,    78,    40,    50,    50,    45,    16,    17,    18,    56,
      57,    21,    50,    41,    40,    16,    18,    57,    40,    18,
      78,    50,    40,    40,    42,    18,    15,    40,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    54,    55,    55,
      55,    55,    56,    56,    57,    58,    59,    60,    61,    62,
      62,    63,    63,    64,    64,    65,    66,    66,    67,    67,
      67,    67,    67,    68,    68,    69,    70,    70,    70,    71,
      71,    72,    72,    73,    73,    74,    75,    75,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    80,    80,    80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     6,     5,     5,     4,     9,    11,
      10,     8,     2,     1,     6,     8,     2,     2,     3,     1,
       1,     3,     2,     2,     1,     3,     3,     1,     1,     4,
       7,     2,     4,     2,     1,     9,     3,     1,     0,     2,
       3,     3,     2,     2,     1,     3,     3,     1,     1,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     2,     4,
       3,     3,     1,     1,     4,     7,     2
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
#line 77 "explc.y" /* yacc.c:1646  */
    {

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
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 93 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 94 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 97 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 98 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 99 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 100 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 101 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 102 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 103 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 104 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 105 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 108 "explc.y" /* yacc.c:1646  */
    { 
        struct ASTNode *addrNode = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[-2].astNode), 0);
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, addrNode, 0);
    }
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 112 "explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, (yyvsp[-2].astNode), 0);
    }
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 117 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WRITE_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 120 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 123 "explc.y" /* yacc.c:1646  */
    { 
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-6].astNode), (yyvsp[-3].astNode));
        (yyvsp[-2].astNode)->left = (yyvsp[-3].astNode); 
        (yyval.astNode)->right = (yyvsp[-2].astNode);
    }
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 128 "explc.y" /* yacc.c:1646  */
    { 
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-8].astNode), (yyvsp[-5].astNode));
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-4].astNode));
        ifNode->right = CreateASTNode(0, 0, BRANCH_NODE, 0, ifNode->right, (yyvsp[-2].astNode));
        (yyvsp[-4].astNode)->left = (yyvsp[-5].astNode); 
        (yyval.astNode)->right = (yyvsp[-4].astNode);
    }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 135 "explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *branch = CreateASTNode(0, 0, BRANCH_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-2].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-7].astNode), branch);
    }
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 142 "explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-1].astNode));
        (yyvsp[0].astNode)->left = ifNode->right; 
        ifNode->right = (yyvsp[0].astNode); 
        (yyval.astNode) = (yyvsp[-1].astNode);
    }
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 148 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 151 "explc.y" /* yacc.c:1646  */
    { 
        struct ASTNode *ifNode = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-3].astNode), (yyvsp[0].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, BRANCH_NODE, 0, 0, ifNode); 
    }
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 157 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WHILE_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 160 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, BREAK_NODE, 0, 0, 0); }
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 163 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 166 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, RETURN_NODE, 0, (yyvsp[-1].astNode), 0); }
#line 1719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 169 "explc.y" /* yacc.c:1646  */
    { (yyval.type) = INTEGER_TYPE; }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 170 "explc.y" /* yacc.c:1646  */
    { (yyval.type) = STRING_TYPE; }
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 180 "explc.y" /* yacc.c:1646  */
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
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 192 "explc.y" /* yacc.c:1646  */
    {
        struct GlobalSymbol symbol = (yyvsp[0].globalSymbolTable)->symbols[0];
        InstallGlobalSymbol((yyvsp[-2].globalSymbolTable), symbol.name, symbol.type, symbol.size);
        (yyvsp[-2].globalSymbolTable)->symbols[(yyvsp[-2].globalSymbolTable)->size - 1] = symbol;
        free((yyvsp[0].globalSymbolTable)->symbols);
        free((yyvsp[0].globalSymbolTable));
        (yyval.globalSymbolTable) = (yyvsp[-2].globalSymbolTable);
    }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 200 "explc.y" /* yacc.c:1646  */
    { (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 203 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[0].astNode)->varName, 0, 1);
        (yyval.globalSymbolTable)->symbols[0].colSize = 0;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 0;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 211 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-3].astNode)->varName, 0, (yyvsp[-1].astNode)->val);
        (yyval.globalSymbolTable)->symbols[0].colSize = 0;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 1;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 219 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-6].astNode)->varName, 0, (yyvsp[-4].astNode)->val * (yyvsp[-1].astNode)->val);
        (yyval.globalSymbolTable)->symbols[0].colSize = (yyvsp[-1].astNode)->val;
        (yyval.globalSymbolTable)->symbols[0].arrayDim = 2;
        (yyval.globalSymbolTable)->symbols[0].functionLabel = -1;
    }
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 227 "explc.y" /* yacc.c:1646  */
    {
        (yyvsp[0].globalSymbolTable)->symbols[0].type = 2;
        (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable);
    }
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 231 "explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        InstallGlobalSymbol((yyval.globalSymbolTable), (yyvsp[-3].astNode)->varName, 0, 0);
        (yyval.globalSymbolTable)->symbols[0].functionLabel = functionLabelCounter++;
        (yyval.globalSymbolTable)->symbols[0].paramList = (yyvsp[-1].paramList);
    }
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 244 "explc.y" /* yacc.c:1646  */
    {

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
                printf("[ERROR] found definition of undeclared function -> '%s' !\n", (yyvsp[-7].astNode)->varName);
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
            // PrintAST($8, 0);
            CheckSemantics((yyvsp[-1].astNode));
        }

        char *funcLabel = (char*)malloc(strlen((yyvsp[-7].astNode)->varName) + 2);
        funcLabel[0] = '#';
        funcLabel[strlen((yyvsp[-7].astNode)->varName) + 1] = 0;
        strcat(funcLabel, (yyvsp[-7].astNode)->varName);       
        fprintf(output, "%s\n", funcLabel);
        free(funcLabel);
        
        fprintf(output, "PUSH BP\n");
        fprintf(output, "MOV BP, SP\n");
        
        // allocating space for local variables in the stack
        if((yyvsp[-2].localSymbolTable))
        {
            fprintf(output, "ADD SP, %d\n", (yyvsp[-2].localSymbolTable)->size);
        }

        //generating code for function
        if((yyvsp[-1].astNode))
        {
            GenerateCode((yyvsp[-1].astNode), output);
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
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 402 "explc.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].paramList) && (yyvsp[0].paramList)) 
        {
            InstallParam((yyvsp[-2].paramList), (yyvsp[0].paramList)->params[0].name, (yyvsp[0].paramList)->params[0].type);
            free((yyvsp[0].paramList)->params);
            free((yyvsp[0].paramList));
        }
        (yyval.paramList) = (yyvsp[-2].paramList);
    }
#line 2000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 411 "explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[0].paramList); }
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 412 "explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = 0;  }
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 415 "explc.y" /* yacc.c:1646  */
    {
        (yyval.paramList) = (struct ParamList*)malloc(sizeof(struct ParamList));
        (yyval.paramList)->size = 0;
        InstallParam((yyval.paramList), (yyvsp[0].astNode)->varName, (yyvsp[-1].type));
    }
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 420 "explc.y" /* yacc.c:1646  */
    {
        (yyval.paramList) = (struct ParamList*)malloc(sizeof(struct ParamList));
        (yyval.paramList)->size = 0;
        InstallParam((yyval.paramList), (yyvsp[0].astNode)->varName, (yyvsp[-2].type) + 2);
    }
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 427 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable); }
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 428 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = 0; }
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 431 "explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[0].localSymbolTable)->size; n++)
        {
            struct LocalSymbol symbol = (yyvsp[0].localSymbolTable)->symbols[n];
            InstallLocalSymbol((yyvsp[-1].localSymbolTable), symbol.name, symbol.type);
        }
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
    }
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 440 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 443 "explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[-1].localSymbolTable)->size; n++)
        {
            (yyvsp[-1].localSymbolTable)->symbols[n].type = (yyvsp[-2].type);
        }
        (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable);
    }
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 452 "explc.y" /* yacc.c:1646  */
    {
        struct LocalSymbol symbol = (yyvsp[0].localSymbolTable)->symbols[0];
        InstallLocalSymbol((yyvsp[-2].localSymbolTable), symbol.name, 0);
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
        (yyval.localSymbolTable) = (yyvsp[-2].localSymbolTable);
    }
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 459 "explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 462 "explc.y" /* yacc.c:1646  */
    {
        (yyval.localSymbolTable) = (struct LocalSymbolTable*)malloc(sizeof(struct LocalSymbolTable));
        (yyval.localSymbolTable)->size = 0;
        InstallLocalSymbol((yyval.localSymbolTable), (yyvsp[0].astNode)->varName, 0);
    }
#line 2104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 469 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 470 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = 0; }
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 473 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, PLUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));      }
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 474 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MINUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 475 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MUL_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 476 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DIV_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 477 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MOD_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2146 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 478 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 479 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 480 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 481 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 482 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQUAL_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));  }
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 483 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, NOT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));    }
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 484 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, AND_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));          }
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 485 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, OR_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));           }
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 486 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 487 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 488 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 489 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 490 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[0].astNode), 0); }
#line 2224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 491 "explc.y" /* yacc.c:1646  */
    { 
        (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-3].astNode), 0); 
        (yyval.astNode)->argList = (yyvsp[-1].nodeList)->nodes;
        (yyval.astNode)->argCount = (yyvsp[-1].nodeList)->size;
    }
#line 2234 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 496 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 2240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 499 "explc.y" /* yacc.c:1646  */
    {
        InsertASTNode((yyvsp[-2].nodeList), *(yyvsp[0].astNode));
        (yyval.nodeList) = (yyvsp[-2].nodeList);
        free((yyvsp[0].astNode));
    }
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 504 "explc.y" /* yacc.c:1646  */
    { 
        (yyval.nodeList) = (struct ASTNodeList*)malloc(sizeof(struct ASTNodeList));
        InsertASTNode((yyval.nodeList), *(yyvsp[0].astNode));
    }
#line 2259 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 509 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 510 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 511 "explc.y" /* yacc.c:1646  */
    { 
            struct ASTNode *index = CreateASTNode(0, 0, INDEX_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-1].astNode)); 
            (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-6].astNode), index);
        }
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 515 "explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DEREF_NODE, 0, (yyvsp[0].astNode), 0);  }
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2290 "y.tab.c" /* yacc.c:1646  */
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
#line 516 "explc.y" /* yacc.c:1906  */


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
