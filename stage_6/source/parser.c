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
    DECL = 261,
    ENDDECL = 262,
    TYPE_TOKEN = 263,
    ENDTYPE_TOKEN = 264,
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
#define DECL 261
#define ENDDECL 262
#define TYPE_TOKEN 263
#define ENDTYPE_TOKEN 264
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
#line 42 "source/explc.y" /* yacc.c:355  */

    struct ASTNode *astNode;
    struct GlobalSymbolTable *globalSymbolTable;
    struct LocalSymbolTable *localSymbolTable;
    struct ParamList *paramList;
    struct FieldList *fieldList;
    struct ASTNodeList *nodeList;
    unsigned int type;

#line 235 "source/parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SOURCE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 252 "source/parser.c" /* yacc.c:358  */

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
#define YYLAST   453

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

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
      44,    45,     2,     2,    46,     2,    43,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
       0,    83,    83,    93,   102,   113,   116,   118,   119,   121,
     135,   141,   143,   163,   164,   167,   168,   169,   170,   171,
     172,   173,   174,   177,   181,   186,   189,   192,   197,   204,
     208,   211,   217,   220,   226,   229,   232,   235,   238,   239,
     242,   243,   246,   264,   270,   273,   281,   290,   300,   304,
     315,   316,   319,   354,   363,   364,   367,   380,   395,   396,
     399,   407,   410,   425,   431,   434,   442,   443,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   469,   472,   477,
     483,   484,   485,   489
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_LITERAL", "STRING_LITERAL",
  "IDENTIFIER", "DECL", "ENDDECL", "TYPE_TOKEN", "ENDTYPE_TOKEN",
  "BEGIN_TOKEN", "END_TOKEN", "READ_TOKEN", "WRITE_TOKEN", "IF", "THEN",
  "ELSE", "ELIF", "ENDIF", "WHILE", "DO", "ENDWHILE", "BREAK", "CONTINUE",
  "RETURN", "AND", "OR", "LT", "GT", "LT_EQ", "GT_EQ", "EQUAL_EQ",
  "NOT_EQ", "EQ", "PLUS", "MINUS", "MUL", "DIV", "MOD", "ADDR_OF", "'{'",
  "'}'", "';'", "'.'", "'('", "')'", "','", "'['", "']'", "$accept",
  "program", "TYPE", "type_def_block", "type_def_list", "type_def",
  "field_decl_list", "field_decl", "stmt_list", "statement", "read_stmt",
  "write_stmt", "assign_stmt", "if_stmt", "elif_stmt_list", "elif_stmt",
  "while_stmt", "break_stmt", "continue_stmt", "return_stmt",
  "global_decl_block", "global_decl_list", "global_decl", "global_id_list",
  "global_id", "function_def_block", "function_def", "param_list", "param",
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
     123,   125,    59,    46,    40,    41,    44,    91,    93
};
# endif

#define YYPACT_NINF -159

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-159)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      73,  -159,    84,    12,    54,    85,    92,   102,   102,  -159,
    -159,     5,   101,  -159,    72,     6,  -159,  -159,    76,   102,
     102,  -159,    53,     5,   -20,  -159,  -159,  -159,   102,  -159,
    -159,   102,   102,   102,   113,  -159,  -159,     5,   126,    -2,
    -159,    14,   -37,  -159,   -21,    86,  -159,    94,  -159,  -159,
    -159,   135,   105,   102,  -159,   106,  -159,  -159,   149,  -159,
     154,   118,   148,   112,  -159,   161,   122,  -159,    63,   127,
    -159,  -159,    27,  -159,  -159,  -159,   120,  -159,   132,   133,
     134,   138,   129,   141,    44,    44,   151,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,   136,  -159,  -159,   161,
      44,    -3,    44,    44,    44,  -159,  -159,  -159,  -159,    70,
      15,    44,   355,  -159,  -159,  -159,  -159,    44,  -159,   220,
     139,    15,   250,   271,   292,     1,  -159,   313,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,  -159,   373,   155,   143,   153,   162,   193,   192,  -159,
     391,    25,  -159,   403,   403,   159,   159,   159,   159,   415,
     415,   114,   114,  -159,  -159,  -159,  -159,    44,  -159,   171,
    -159,   217,   217,  -159,    44,   235,  -159,   125,   167,   391,
    -159,   217,   173,   176,    17,  -159,   177,   187,    44,  -159,
     217,   185,  -159,  -159,   186,   334,   202,  -159,  -159,   218,
     190,   217,  -159,   217
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     0,     0,     0,     0,     4,    51,
      39,     0,     0,    41,     0,     0,     8,     1,     0,     0,
       3,    50,    45,     0,     0,    44,    38,    40,     0,     6,
       7,    55,     2,    55,     0,    48,    42,     0,     0,     0,
      11,     0,     0,    54,     0,     0,    43,     0,     9,    10,
      56,     0,     0,     0,    49,    46,    12,    57,     0,    53,
       0,     0,     0,     0,    59,     0,     0,    61,     0,     0,
      47,    65,     0,    64,    58,    60,    90,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,    52,    62,     0,
       0,     0,     0,     0,     0,    35,    36,    82,    83,    90,
       0,     0,     0,    84,    93,    66,    13,     0,    63,     0,
       0,     0,     0,     0,     0,     0,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,    91,     0,     0,     0,     0,     0,    87,
      89,     0,    81,    79,    80,    73,    75,    74,    76,    77,
      78,    68,    69,    70,    71,    72,    26,     0,    24,     0,
      25,     0,     0,    86,     0,     0,    23,     0,     0,    88,
      92,     0,     0,     0,     0,    32,     0,     0,     0,    30,
       0,     0,    31,    34,     0,     0,     0,    27,    29,     0,
       0,     0,    28,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,    93,  -159,  -159,   219,  -159,   196,  -158,   -85,
    -159,  -159,  -159,  -159,  -159,    58,  -159,  -159,  -159,  -159,
     231,  -159,   232,  -159,   -16,     9,    64,   210,   206,  -159,
    -159,   208,  -159,   191,  -159,   -73,  -159,   -68
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    15,    16,    39,    40,    86,    87,
      88,    89,    90,    91,   184,   185,    92,    93,    94,    95,
       7,    12,    13,    24,    25,     8,     9,    42,    43,    62,
      66,    67,    72,    73,    69,   112,   151,   113
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      96,   116,   120,     1,   107,   108,   109,    35,    52,    53,
      22,    14,   114,   177,   178,    29,    20,    14,    96,    50,
      76,    46,    36,   187,    54,    53,    37,   119,    32,   122,
     123,   124,   196,   190,   182,   191,   121,    85,   127,    48,
     110,    23,   126,   203,   142,   111,   149,   107,   108,   109,
      51,    85,   150,   145,    17,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    76,    98,
     173,   174,    21,    99,    77,    78,    79,    80,     1,     2,
      85,     3,    81,   110,    21,    82,    83,    84,   111,     1,
      18,    10,   116,   116,   175,    11,    21,    33,     2,    85,
      34,   179,   116,    96,    96,    11,     1,     1,    26,    96,
      96,   116,    28,    96,   125,   195,    45,   100,   116,    96,
      31,    38,    96,     1,    41,    64,    41,     1,    96,    74,
      76,    47,    38,    96,    55,    96,    56,    78,    79,    80,
      57,   181,   182,   183,    81,    58,    41,    82,    83,    84,
     138,   139,   140,    60,    65,    61,    76,    63,    68,    65,
      70,    85,   115,    78,    79,    80,    71,   100,    97,   117,
      81,   105,    76,    82,    83,    84,   101,   102,   103,    78,
      79,    80,   104,   106,   144,   168,    81,    85,   186,    82,
      83,    84,    76,   136,   137,   138,   139,   140,   169,    78,
      79,    80,   167,    85,   170,   194,    81,    76,   171,    82,
      83,    84,   172,   176,    78,    79,    80,   188,   189,   193,
     200,    81,    76,    85,    82,    83,    84,   197,   198,    78,
      79,    80,   202,   201,    30,    49,    81,    19,    85,    82,
      83,    84,   192,    44,    27,   128,   129,   130,   131,   132,
     133,   134,   135,    85,   136,   137,   138,   139,   140,    59,
     128,   129,   130,   131,   132,   133,   134,   135,   143,   136,
     137,   138,   139,   140,    75,   128,   129,   130,   131,   132,
     133,   134,   135,   180,   136,   137,   138,   139,   140,     0,
     118,     0,     0,     0,     0,   146,   128,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
       0,     0,     0,     0,     0,     0,   147,   128,   129,   130,
     131,   132,   133,   134,   135,     0,   136,   137,   138,   139,
     140,     0,     0,     0,     0,     0,     0,   148,   128,   129,
     130,   131,   132,   133,   134,   135,     0,   136,   137,   138,
     139,   140,     0,     0,     0,     0,     0,     0,   152,   128,
     129,   130,   131,   132,   133,   134,   135,     0,   136,   137,
     138,   139,   140,     0,     0,     0,     0,     0,     0,   199,
     128,   129,   130,   131,   132,   133,   134,   135,     0,   136,
     137,   138,   139,   140,     0,     0,     0,   141,   128,   129,
     130,   131,   132,   133,   134,   135,     0,   136,   137,   138,
     139,   140,     0,     0,     0,   166,   128,   129,   130,   131,
     132,   133,   134,   135,     0,   136,   137,   138,   139,   140,
     130,   131,   132,   133,   134,   135,     0,   136,   137,   138,
     139,   140,   130,   131,   132,   133,     0,     0,     0,   136,
     137,   138,   139,   140
};

static const yytype_int16 yycheck[] =
{
      68,    86,     5,     5,     3,     4,     5,    23,    45,    46,
       5,     5,    85,   171,   172,     9,     7,     5,    86,     5,
       5,    37,    42,   181,    45,    46,    46,   100,    19,   102,
     103,   104,   190,    16,    17,    18,    39,    36,   111,    41,
      39,    36,   110,   201,   117,    44,    45,     3,     4,     5,
      36,    36,   125,   121,     0,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     5,    42,
      45,    46,     8,    46,    11,    12,    13,    14,     5,     6,
      36,     8,    19,    39,    20,    22,    23,    24,    44,     5,
       5,     7,   177,   178,   167,     2,    32,    44,     6,    36,
      47,   174,   187,   171,   172,    12,     5,     5,     7,   177,
     178,   196,    40,   181,    44,   188,     3,    47,   203,   187,
      44,    28,   190,     5,    31,     7,    33,     5,   196,     7,
       5,     5,    39,   201,    48,   203,    42,    12,    13,    14,
       5,    16,    17,    18,    19,    40,    53,    22,    23,    24,
      36,    37,    38,    47,    61,     6,     5,     3,    10,    66,
      48,    36,    11,    12,    13,    14,     5,    47,    41,    33,
      19,    42,     5,    22,    23,    24,    44,    44,    44,    12,
      13,    14,    44,    42,    45,    42,    19,    36,    21,    22,
      23,    24,     5,    34,    35,    36,    37,    38,    45,    12,
      13,    14,    47,    36,    42,    18,    19,     5,    15,    22,
      23,    24,    20,    42,    12,    13,    14,    44,    42,    42,
      18,    19,     5,    36,    22,    23,    24,    42,    42,    12,
      13,    14,    42,    15,    15,    39,    19,     6,    36,    22,
      23,    24,   184,    33,    12,    25,    26,    27,    28,    29,
      30,    31,    32,    36,    34,    35,    36,    37,    38,    53,
      25,    26,    27,    28,    29,    30,    31,    32,    48,    34,
      35,    36,    37,    38,    66,    25,    26,    27,    28,    29,
      30,    31,    32,    48,    34,    35,    36,    37,    38,    -1,
      99,    -1,    -1,    -1,    -1,    45,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    42,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    42,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    27,    28,    29,    30,    -1,    -1,    -1,    34,
      35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     8,    50,    51,    52,    69,    74,    75,
       7,    51,    70,    71,     5,    53,    54,     0,     5,    69,
      74,    75,     5,    36,    72,    73,     7,    71,    40,     9,
      54,    44,    74,    44,    47,    73,    42,    46,    51,    55,
      56,    51,    76,    77,    76,     3,    73,     5,    41,    56,
       5,    36,    45,    46,    45,    48,    42,     5,    40,    77,
      47,     6,    78,     3,     7,    51,    79,    80,    10,    83,
      48,     5,    81,    82,     7,    80,     5,    11,    12,    13,
      14,    19,    22,    23,    24,    36,    57,    58,    59,    60,
      61,    62,    65,    66,    67,    68,    86,    41,    42,    46,
      47,    44,    44,    44,    44,    42,    42,     3,     4,     5,
      39,    44,    84,    86,    84,    11,    58,    33,    82,    84,
       5,    39,    84,    84,    84,    44,    86,    84,    25,    26,
      27,    28,    29,    30,    31,    32,    34,    35,    36,    37,
      38,    42,    84,    48,    45,    86,    45,    45,    45,    45,
      84,    85,    45,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    42,    47,    42,    45,
      42,    15,    20,    45,    46,    84,    42,    57,    57,    84,
      48,    16,    17,    18,    63,    64,    21,    57,    44,    42,
      16,    18,    64,    42,    18,    84,    57,    42,    42,    45,
      18,    15,    42,    57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    50,    51,    52,    53,    53,    54,
      55,    55,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    59,    60,    61,    62,    62,    62,
      62,    63,    63,    64,    65,    66,    67,    68,    69,    69,
      70,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      74,    74,    75,    76,    76,    76,    77,    77,    78,    78,
      79,    79,    80,    81,    81,    82,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     1,     1,     3,     2,     1,     4,
       2,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     5,     5,     4,     9,    11,    10,
       8,     2,     1,     6,     8,     2,     2,     3,     3,     2,
       2,     1,     3,     3,     1,     1,     4,     7,     2,     4,
       2,     1,     9,     3,     1,     0,     2,     3,     3,     2,
       2,     1,     3,     3,     1,     1,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     2,     4,     3,     3,     1,
       1,     4,     7,     2
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
        // Compile($3);
        PrintTypeTable(typeTable);

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
#line 1530 "source/parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 93 "source/explc.y" /* yacc.c:1646  */
    {
        CheckSemantics((yyvsp[0].astNode));
        // Compile($2);

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
#line 1544 "source/parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 102 "source/explc.y" /* yacc.c:1646  */
    {
        CheckSemantics((yyvsp[0].astNode));
        // Compile($1);

        if(!entryPointFound)
        {
            printf("warning: no definition of function 'main'\n");
        }
    }
#line 1558 "source/parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 113 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1564 "source/parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 121 "source/explc.y" /* yacc.c:1646  */
    {
    struct Type type = {0};
    type.name = (yyvsp[-3].astNode)->varName;
    type.size = 0;
    type.fieldList = *((yyvsp[-1].fieldList));

    for(int n = 0; n < (yyvsp[-1].fieldList)->count; n++)
    {
        type.size += typeTable.types[(yyvsp[-1].fieldList)->fields[n].typeIndex].size;
    }

    InstallType(&typeTable, type);
}
#line 1582 "source/parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 135 "source/explc.y" /* yacc.c:1646  */
    {
        InstallField((yyvsp[-1].fieldList), (yyvsp[0].fieldList)->fields[0]);
        free((yyvsp[0].fieldList)->fields);
        free((yyvsp[0].fieldList));
        (yyval.fieldList) = (yyvsp[-1].fieldList);
    }
#line 1593 "source/parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 141 "source/explc.y" /* yacc.c:1646  */
    { (yyval.fieldList) = (yyvsp[0].fieldList); }
#line 1599 "source/parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 143 "source/explc.y" /* yacc.c:1646  */
    {
    (yyval.fieldList) = (struct FieldList*)malloc(sizeof(struct FieldList));
    (yyval.fieldList)->count = 0;

    struct Field field = {0};
    field.name = (yyvsp[-1].astNode)->varName;
    field.typeIndex = LookUpTypeTableIndex(typeTable, (yyvsp[-2].astNode)->varName);

    if(field.typeIndex == -1)
    {
        printf("error: unkwown type '%s' for field '%s'\n", (yyvsp[-2].astNode)->varName, (yyvsp[-1].astNode)->varName);
        exit(1);
    }

    InstallField((yyval.fieldList), field);
}
#line 1620 "source/parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 163 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1626 "source/parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 164 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1632 "source/parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 167 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1638 "source/parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 168 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1644 "source/parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 169 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1650 "source/parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 170 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1656 "source/parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 171 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1662 "source/parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 172 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1668 "source/parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 173 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1674 "source/parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 174 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1680 "source/parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 177 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *addrNode = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[-2].astNode), 0);
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, addrNode, 0);
    }
#line 1689 "source/parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 181 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, READ_NODE, 0, (yyvsp[-2].astNode), 0);
    }
#line 1697 "source/parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 186 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WRITE_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 1703 "source/parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 189 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQ_OP_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 1709 "source/parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 192 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-6].astNode), (yyvsp[-3].astNode));
        (yyvsp[-2].astNode)->left = (yyvsp[-3].astNode);
        (yyval.astNode)->right = (yyvsp[-2].astNode);
    }
#line 1719 "source/parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 197 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-8].astNode), (yyvsp[-5].astNode));
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-4].astNode));
        ifNode->right = CreateASTNode(0, 0, BRANCH_NODE, 0, ifNode->right, (yyvsp[-2].astNode));
        (yyvsp[-4].astNode)->left = (yyvsp[-5].astNode);
        (yyval.astNode)->right = (yyvsp[-4].astNode);
    }
#line 1731 "source/parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 204 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *branch = CreateASTNode(0, 0, BRANCH_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-2].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-7].astNode), branch);
    }
#line 1740 "source/parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 208 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1746 "source/parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 211 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *ifNode = GetRightIfNode((yyvsp[-1].astNode));
        (yyvsp[0].astNode)->left = ifNode->right;
        ifNode->right = (yyvsp[0].astNode);
        (yyval.astNode) = (yyvsp[-1].astNode);
    }
#line 1757 "source/parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 217 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1763 "source/parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 220 "source/explc.y" /* yacc.c:1646  */
    {
        struct ASTNode *ifNode = CreateASTNode(0, 0, IF_NODE, 0, (yyvsp[-3].astNode), (yyvsp[0].astNode));
        (yyval.astNode) = CreateASTNode(0, 0, BRANCH_NODE, 0, 0, ifNode);
    }
#line 1772 "source/parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 226 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, WHILE_NODE, 0, (yyvsp[-5].astNode), (yyvsp[-2].astNode)); }
#line 1778 "source/parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 229 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, BREAK_NODE, 0, 0, 0); }
#line 1784 "source/parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 232 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONTINUE_NODE, 0, 0, 0); }
#line 1790 "source/parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 235 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, RETURN_NODE, 0, (yyvsp[-1].astNode), 0); }
#line 1796 "source/parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 246 "source/explc.y" /* yacc.c:1646  */
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
#line 1817 "source/parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 264 "source/explc.y" /* yacc.c:1646  */
    {
        InstallGlobalSymbol((yyvsp[-2].globalSymbolTable), (yyvsp[0].globalSymbolTable)->symbols[0]);
        free((yyvsp[0].globalSymbolTable)->symbols);
        free((yyvsp[0].globalSymbolTable));
        (yyval.globalSymbolTable) = (yyvsp[-2].globalSymbolTable);
    }
#line 1828 "source/parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 270 "source/explc.y" /* yacc.c:1646  */
    { (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable); }
#line 1834 "source/parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 273 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[0].astNode)->varName;
        symbol.functionLabel = -1;
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1847 "source/parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 281 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[-3].astNode)->varName;
        symbol.arrayDim = 1;
        symbol.functionLabel = -1;
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1861 "source/parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 290 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[-6].astNode)->varName;
        symbol.colSize = (yyvsp[-1].astNode)->val;
        symbol.arrayDim = 2;
        symbol.functionLabel = -1;
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1876 "source/parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 300 "source/explc.y" /* yacc.c:1646  */
    {
        (yyvsp[0].globalSymbolTable)->symbols[0].typeIndex = -1;
        (yyval.globalSymbolTable) = (yyvsp[0].globalSymbolTable);
    }
#line 1885 "source/parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 304 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.globalSymbolTable) = (struct GlobalSymbolTable*)malloc(sizeof(struct GlobalSymbolTable));
        (yyval.globalSymbolTable)->size = 0;
        struct GlobalSymbol symbol = {0};
        symbol.name = (yyvsp[-3].astNode)->varName;
        symbol.functionLabel = functionLabelCounter++;
        symbol.paramList = (yyvsp[-1].paramList);
        InstallGlobalSymbol((yyval.globalSymbolTable), symbol);
    }
#line 1899 "source/parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 315 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, CONNECTOR_NODE, 0, (yyvsp[-1].astNode), (yyvsp[0].astNode)); }
#line 1905 "source/parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 316 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1911 "source/parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 319 "source/explc.y" /* yacc.c:1646  */
    {

        (yyval.astNode) = CreateASTNode(0, (yyvsp[-7].astNode)->varName, FUNCTION_DEF_NODE, 0, (yyvsp[-1].astNode), 0);
        (yyval.astNode)->returnTypeIndex = LookUpTypeTableIndex(typeTable, (yyvsp[-8].astNode)->varName);
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
#line 1950 "source/parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 354 "source/explc.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].paramList) && (yyvsp[0].paramList))
        {
            InstallParam((yyvsp[-2].paramList), (yyvsp[0].paramList)->params[0].name, (yyvsp[0].paramList)->params[0].typeIndex);
            free((yyvsp[0].paramList)->params);
            free((yyvsp[0].paramList));
        }
        (yyval.paramList) = (yyvsp[-2].paramList);
    }
#line 1964 "source/parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 363 "source/explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[0].paramList); }
#line 1970 "source/parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 364 "source/explc.y" /* yacc.c:1646  */
    { (yyval.paramList) = 0; }
#line 1976 "source/parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 367 "source/explc.y" /* yacc.c:1646  */
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
#line 1994 "source/parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 380 "source/explc.y" /* yacc.c:1646  */
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
#line 2012 "source/parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 395 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[-1].localSymbolTable); }
#line 2018 "source/parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 396 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = 0; }
#line 2024 "source/parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 399 "source/explc.y" /* yacc.c:1646  */
    {
        for(int n = 0; n < (yyvsp[0].localSymbolTable)->size; n++)
        {
            InstallLocalSymbol((yyvsp[-1].localSymbolTable), (yyvsp[0].localSymbolTable)->symbols[n]);
        }
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
    }
#line 2037 "source/parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 407 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 2043 "source/parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 410 "source/explc.y" /* yacc.c:1646  */
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
#line 2061 "source/parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 425 "source/explc.y" /* yacc.c:1646  */
    {
        InstallLocalSymbol((yyvsp[-2].localSymbolTable), (yyvsp[0].localSymbolTable)->symbols[0]);
        free((yyvsp[0].localSymbolTable)->symbols);
        free((yyvsp[0].localSymbolTable));
        (yyval.localSymbolTable) = (yyvsp[-2].localSymbolTable);
    }
#line 2072 "source/parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 431 "source/explc.y" /* yacc.c:1646  */
    { (yyval.localSymbolTable) = (yyvsp[0].localSymbolTable); }
#line 2078 "source/parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 434 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.localSymbolTable) = (struct LocalSymbolTable*)malloc(sizeof(struct LocalSymbolTable));
        struct LocalSymbol symbol = {0};
        symbol.name = (yyvsp[0].astNode)->varName;
        InstallLocalSymbol((yyval.localSymbolTable), symbol);
    }
#line 2089 "source/parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 442 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2095 "source/parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 443 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = 0; }
#line 2101 "source/parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 446 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, PLUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));      }
#line 2107 "source/parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 447 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MINUS_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2113 "source/parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 448 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MUL_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2119 "source/parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 449 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DIV_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2125 "source/parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 450 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, MOD_OP_NODE, INTEGER_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));       }
#line 2131 "source/parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 451 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2137 "source/parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 452 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, LT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2143 "source/parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 453 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));        }
#line 2149 "source/parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 454 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, GT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));     }
#line 2155 "source/parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 455 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, EQUAL_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));  }
#line 2161 "source/parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 456 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, NOT_EQ_OP_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));    }
#line 2167 "source/parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 457 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, AND_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));          }
#line 2173 "source/parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 458 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, OR_NODE, BOOLEAN_TYPE, (yyvsp[-2].astNode), (yyvsp[0].astNode));           }
#line 2179 "source/parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 459 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2185 "source/parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 460 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2191 "source/parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 461 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2197 "source/parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 462 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2203 "source/parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 463 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ADDR_OF_NODE, 0, (yyvsp[0].astNode), 0); }
#line 2209 "source/parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 464 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-3].astNode), 0);
        (yyval.astNode)->argList = (yyvsp[-1].nodeList)->nodes;
        (yyval.astNode)->argCount = (yyvsp[-1].nodeList)->size;
    }
#line 2219 "source/parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 469 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, FUNCTION_CALL_NODE, 0, (yyvsp[-2].astNode), 0); }
#line 2225 "source/parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 472 "source/explc.y" /* yacc.c:1646  */
    {
        InsertASTNode((yyvsp[-2].nodeList), *(yyvsp[0].astNode));
        (yyval.nodeList) = (yyvsp[-2].nodeList);
        free((yyvsp[0].astNode));
    }
#line 2235 "source/parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 477 "source/explc.y" /* yacc.c:1646  */
    {
        (yyval.nodeList) = (struct ASTNodeList*)malloc(sizeof(struct ASTNodeList));
        (yyval.nodeList)->size = 0;
        InsertASTNode((yyval.nodeList), *(yyvsp[0].astNode));
    }
#line 2245 "source/parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 483 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2251 "source/parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 484 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-3].astNode), (yyvsp[-1].astNode)); }
#line 2257 "source/parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 485 "source/explc.y" /* yacc.c:1646  */
    {
            struct ASTNode *index = CreateASTNode(0, 0, INDEX_NODE, 0, (yyvsp[-4].astNode), (yyvsp[-1].astNode));
            (yyval.astNode) = CreateASTNode(0, 0, ARRAY_NODE, 0, (yyvsp[-6].astNode), index);
        }
#line 2266 "source/parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 489 "source/explc.y" /* yacc.c:1646  */
    { (yyval.astNode) = CreateASTNode(0, 0, DEREF_NODE, 0, (yyvsp[0].astNode), 0);  }
#line 2272 "source/parser.c" /* yacc.c:1646  */
    break;


#line 2276 "source/parser.c" /* yacc.c:1646  */
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
#line 490 "source/explc.y" /* yacc.c:1906  */


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
