/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CASTREF = 258,
     UNARY = 259,
     VOID = 260,
     VAR = 261,
     INT = 262,
     FLOAT = 263,
     BLTIN = 264,
     ID = 265,
     STRING = 266,
     HANDLER = 267,
     tDOWN = 268,
     tELSE = 269,
     tELSIF = 270,
     tEND = 271,
     tEXIT = 272,
     tFRAME = 273,
     tGLOBAL = 274,
     tGO = 275,
     tIF = 276,
     tINTO = 277,
     tLOOP = 278,
     tMACRO = 279,
     tMCI = 280,
     tMCIWAIT = 281,
     tMOVIE = 282,
     tNEXT = 283,
     tOF = 284,
     tPREVIOUS = 285,
     tPUT = 286,
     tREPEAT = 287,
     tSET = 288,
     tTHEN = 289,
     tTO = 290,
     tWITH = 291,
     tWHILE = 292,
     tGE = 293,
     tLE = 294,
     tGT = 295,
     tLT = 296,
     tEQ = 297,
     tNEQ = 298
   };
#endif
/* Tokens.  */
#define CASTREF 258
#define UNARY 259
#define VOID 260
#define VAR 261
#define INT 262
#define FLOAT 263
#define BLTIN 264
#define ID 265
#define STRING 266
#define HANDLER 267
#define tDOWN 268
#define tELSE 269
#define tELSIF 270
#define tEND 271
#define tEXIT 272
#define tFRAME 273
#define tGLOBAL 274
#define tGO 275
#define tIF 276
#define tINTO 277
#define tLOOP 278
#define tMACRO 279
#define tMCI 280
#define tMCIWAIT 281
#define tMOVIE 282
#define tNEXT 283
#define tOF 284
#define tPREVIOUS 285
#define tPUT 286
#define tREPEAT 287
#define tSET 288
#define tTHEN 289
#define tTO 290
#define tWITH 291
#define tWHILE 292
#define tGE 293
#define tLE 294
#define tGT 295
#define tLT 296
#define tEQ 297
#define tNEQ 298




/* Copy the first part of user declarations.  */
#line 49 "engines/director/lingo/lingo-gr.y"

#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "common/hash-str.h"

#include "director/lingo/lingo.h"
#include "director/lingo/lingo-gr.h"

extern int yylex();
extern int yyparse();
void yyerror(char *s) { error("%s", s); }

using namespace Director;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 65 "engines/director/lingo/lingo-gr.y"
{
	Common::String *s;
	int	i;
	float f;
	int code;
	int	narg;	/* number of arguments */
}
/* Line 193 of yacc.c.  */
#line 206 "engines/director/lingo/lingo-gr.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 219 "engines/director/lingo/lingo-gr.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   344

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNRULES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    49,     2,     2,
      51,    52,    47,    45,    55,    46,     2,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      54,    44,    53,     2,     2,     2,     2,     2,     2,     2,
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     9,    10,    12,    14,    16,    18,
      20,    22,    24,    29,    34,    39,    41,    43,    45,    54,
      66,    79,    86,    99,   107,   118,   129,   132,   134,   141,
     146,   148,   152,   156,   159,   163,   165,   167,   168,   169,
     170,   173,   176,   178,   180,   185,   190,   192,   194,   198,
     202,   206,   210,   214,   218,   222,   226,   230,   233,   236,
     240,   243,   246,   249,   251,   253,   256,   258,   262,   265,
     268,   271,   274,   278,   281,   285,   288,   291,   293,   297,
     300,   304,   305,   314,   315,   317,   321,   326,   327,   331,
     332,   334
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    50,    57,    -1,    58,    -1,    -1,
      79,    -1,    74,    -1,    83,    -1,    59,    -1,    61,    -1,
      60,    -1,     1,    -1,    31,    73,    22,    10,    -1,    33,
      10,    44,    73,    -1,    33,    10,    35,    73,    -1,    73,
      -1,    74,    -1,    62,    -1,    66,    51,    65,    52,    72,
      71,    16,    32,    -1,    67,    44,    73,    71,    35,    73,
      71,    72,    71,    16,    32,    -1,    67,    44,    73,    71,
      13,    35,    73,    71,    72,    71,    16,    32,    -1,    68,
      65,    34,    70,    60,    71,    -1,    68,    65,    34,    70,
      60,    71,    50,    14,    70,    60,    71,    50,    -1,    68,
      65,    34,    72,    71,    16,    21,    -1,    68,    65,    34,
      72,    71,    14,    72,    71,    16,    21,    -1,    68,    65,
      34,    72,    71,    70,    63,    71,    16,    21,    -1,    64,
      63,    -1,    64,    -1,    69,    65,    34,    70,    60,    50,
      -1,    69,    65,    34,    72,    -1,    73,    -1,    73,    44,
      73,    -1,    51,    65,    52,    -1,    32,    37,    -1,    32,
      36,    10,    -1,    21,    -1,    15,    -1,    -1,    -1,    -1,
      72,    50,    -1,    72,    60,    -1,     7,    -1,     8,    -1,
       9,    51,    84,    52,    -1,    10,    51,    84,    52,    -1,
      10,    -1,    59,    -1,    73,    45,    73,    -1,    73,    46,
      73,    -1,    73,    47,    73,    -1,    73,    48,    73,    -1,
      73,    53,    73,    -1,    73,    54,    73,    -1,    73,    43,
      73,    -1,    73,    38,    73,    -1,    73,    39,    73,    -1,
      45,    73,    -1,    46,    73,    -1,    51,    73,    52,    -1,
      25,    11,    -1,    26,    10,    -1,    31,    73,    -1,    76,
      -1,    17,    -1,    19,    75,    -1,    10,    -1,    75,    55,
      10,    -1,    20,    23,    -1,    20,    28,    -1,    20,    30,
      -1,    20,    77,    -1,    20,    77,    78,    -1,    20,    78,
      -1,    35,    18,    11,    -1,    18,    11,    -1,    35,    11,
      -1,    11,    -1,    29,    27,    11,    -1,    27,    11,    -1,
      35,    27,    11,    -1,    -1,    24,    10,    80,    70,    81,
      50,    82,    72,    -1,    -1,    10,    -1,    81,    55,    10,
      -1,    81,    50,    55,    10,    -1,    -1,    10,    70,    84,
      -1,    -1,    73,    -1,    84,    55,    73,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    94,    97,    98,    99,   100,   101,   102,
     103,   104,   107,   113,   119,   127,   128,   129,   134,   145,
     161,   175,   183,   195,   202,   211,   222,   223,   226,   232,
     240,   241,   242,   244,   246,   252,   257,   259,   261,   263,
     264,   265,   268,   273,   276,   282,   290,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     308,   309,   310,   311,   312,   314,   317,   318,   329,   330,
     331,   332,   337,   343,   350,   351,   352,   353,   356,   357,
     358,   386,   386,   393,   394,   395,   396,   398,   401,   409,
     410,   411
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CASTREF", "UNARY", "VOID", "VAR", "INT",
  "FLOAT", "BLTIN", "ID", "STRING", "HANDLER", "tDOWN", "tELSE", "tELSIF",
  "tEND", "tEXIT", "tFRAME", "tGLOBAL", "tGO", "tIF", "tINTO", "tLOOP",
  "tMACRO", "tMCI", "tMCIWAIT", "tMOVIE", "tNEXT", "tOF", "tPREVIOUS",
  "tPUT", "tREPEAT", "tSET", "tTHEN", "tTO", "tWITH", "tWHILE", "tGE",
  "tLE", "tGT", "tLT", "tEQ", "tNEQ", "'='", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'\\n'", "'('", "')'", "'>'", "'<'", "','", "$accept", "program",
  "programline", "asgn", "stmt", "stmtoneliner", "ifstmt", "elseifstmt",
  "elseifstmt1", "cond", "repeatwhile", "repeatwith", "if", "elseif",
  "begin", "end", "stmtlist", "expr", "func", "globallist", "gotofunc",
  "gotoframe", "gotomovie", "defn", "@1", "argdef", "argstore", "macro",
  "arglist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    61,    43,    45,    42,    47,    37,
      10,    40,    41,    62,    60,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    58,    58,    58,    58,    58,    58,
      58,    58,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    66,    67,    68,    69,    70,    71,    72,
      72,    72,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      74,    74,    74,    74,    74,    74,    75,    75,    76,    76,
      76,    76,    76,    76,    77,    77,    77,    77,    78,    78,
      78,    80,    79,    81,    81,    81,    81,    82,    83,    84,
      84,    84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     1,     1,     1,     8,    11,
      12,     6,    12,     7,    10,    10,     2,     1,     6,     4,
       1,     3,     3,     2,     3,     1,     1,     0,     0,     0,
       2,     2,     1,     1,     4,     4,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       2,     2,     2,     1,     1,     2,     1,     3,     2,     2,
       2,     2,     3,     2,     3,     2,     2,     1,     3,     2,
       3,     0,     8,     0,     1,     3,     4,     0,     3,     0,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    11,    42,    43,     0,    37,    64,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,    47,    10,     9,    17,     0,     0,     0,    15,     6,
      63,     5,     7,    89,    89,    89,    66,    65,    77,     0,
      68,     0,    69,     0,    70,     0,    71,    73,    81,    60,
      61,    46,     0,    47,    62,     0,    33,     0,    57,    58,
       0,     1,     0,     0,     0,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,     0,     0,
      88,     0,    75,    79,     0,    76,     0,     0,     0,    72,
      37,     0,     0,    34,     0,     0,    59,     2,     0,    38,
       0,     0,    37,     0,    55,    56,    54,    48,    49,    50,
      51,    52,    53,    44,     0,    45,    67,    78,    74,    80,
      83,    12,    14,    13,    39,     0,    32,     0,    38,    31,
      91,    84,     0,    38,     0,     0,    38,     0,    16,    40,
      41,    37,    87,     0,     0,     0,    38,    21,     0,    39,
       0,     0,     0,    39,    85,     0,    38,    39,     0,    39,
      38,    23,    36,    38,    27,     0,    86,    82,    18,    39,
      38,    37,     0,     0,    26,     0,    38,     0,     0,     0,
       0,    37,     0,     0,    38,    24,    25,     0,    29,     0,
      19,     0,     0,    20,    22,    28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    53,   140,    23,    24,   163,   164,    66,
      25,    26,   137,   165,    35,   125,   128,    28,   138,    37,
      30,    46,    47,    31,    90,   132,   153,    32,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int16 yypact[] =
{
     138,   -89,   -89,   -89,   -30,    72,   -89,    -1,     8,   -89,
      17,    23,    34,   166,    19,    40,   166,   166,   166,    57,
      11,     4,   -89,   -89,   -89,    37,    48,   211,   290,   -89,
     -89,   -89,   -89,   166,   166,   166,   -89,    42,   -89,    84,
     -89,    88,   -89,    73,   -89,    21,    52,   -89,   -89,   -89,
     -89,    54,   166,   -89,   242,    97,   -89,   -11,    63,    63,
     266,   -89,   138,   211,   166,   211,    78,   278,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   290,    -6,    30,
      58,   112,   -89,   -89,   113,   -89,   118,   120,   106,   -89,
     -89,   242,   125,   -89,   166,   166,   -89,   -89,    85,   290,
      89,   254,    -9,   166,   290,   290,   290,   229,   229,    63,
      63,   290,   290,   -89,   166,   -89,   -89,   -89,   -89,   -89,
     126,   -89,   290,   290,   -89,     7,   -89,   228,   183,   290,
     290,   -89,   -10,   183,   108,   166,   -89,   211,   -89,   -89,
     -89,     9,    94,   134,   135,   166,   290,   100,   119,   -89,
     131,   139,   146,   -89,   -89,   129,   290,   -89,   151,   -89,
     183,   -89,   -89,   -89,   139,   211,   -89,   183,   -89,   -89,
     183,   -89,   150,   152,   -89,   133,   183,   156,   228,   158,
     159,     2,   161,   149,   -89,   -89,   -89,   228,   183,   153,
     -89,   132,   136,   -89,   -89,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   143,   -89,    10,     0,   -89,   -89,    31,   -89,   -62,
     -89,   -89,    15,   -89,   -88,   -42,   -73,    -5,    16,   -89,
     -89,   -89,   148,   -89,   -89,   -89,   -89,   -89,    39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int16 yytable[] =
{
      22,    98,   120,   100,    -8,   -39,   -39,   -39,    54,    36,
      21,    58,    59,    60,   127,    27,    29,   -39,   -39,    38,
     134,    33,    67,   149,    94,   150,    39,    48,    77,    77,
      77,    40,    85,    95,    49,    41,    42,    43,    44,    86,
     142,   -39,   135,    45,    50,   143,   113,    91,    87,   114,
      57,   133,   -39,   151,    -8,    55,    56,    61,    67,    99,
     101,    62,    22,   104,   105,   106,   107,   108,   109,   110,
     111,   112,    21,    79,    80,   148,   160,    27,    29,    41,
     167,    43,   115,   178,   170,   114,   141,    88,    63,   122,
     123,   144,    64,   187,   147,    82,   176,    81,   129,    83,
      84,    68,    69,   175,   157,    34,    70,    93,   188,   130,
     -46,   -46,   102,   114,   169,   -46,    75,    76,   172,   -46,
     -46,   173,   116,    34,   117,   -46,   -46,   136,   177,   118,
     146,   119,    67,    87,   182,   121,   131,   124,    -4,     1,
     156,   126,   191,   145,   154,     2,     3,     4,     5,   152,
     158,   155,   161,   159,   162,     6,   166,     7,     8,     9,
      67,   168,    10,    11,    12,   171,   179,   181,   180,    13,
      14,    15,   183,     2,     3,     4,    51,   189,   184,   185,
     186,   190,   194,    16,    17,   193,   195,   192,    -4,    18,
       2,     3,     4,    51,    89,   174,     0,    52,     0,    15,
       6,     0,     7,     8,     9,    97,     0,     0,    11,    12,
       0,    16,    17,     0,    13,    14,    15,    18,     2,     3,
       4,    51,     0,     0,     0,     0,     0,     0,    16,    17,
       0,     0,     0,   139,    18,     2,     3,     4,    51,     0,
       0,     0,    52,     0,    15,     6,     0,     7,     8,     9,
       0,     0,     0,    11,    12,     0,    16,    17,     0,    13,
      14,    15,    65,     0,    92,     0,     0,    68,    69,     0,
       0,     0,    70,    16,    17,     0,    73,    74,     0,    18,
      68,    69,    75,    76,     0,    70,     0,    71,    72,    73,
      74,     0,    68,    69,     0,    75,    76,    70,   103,    71,
      72,    73,    74,     0,    68,    69,    96,    75,    76,    70,
       0,    71,    72,    73,    74,     0,    68,    69,    96,    75,
      76,    70,   103,    71,    72,    73,    74,     0,    68,    69,
       0,    75,    76,    70,     0,    71,    72,    73,    74,     0,
       0,     0,     0,    75,    76
};

static const yytype_int16 yycheck[] =
{
       0,    63,    90,    65,     0,    14,    15,    16,    13,    10,
       0,    16,    17,    18,   102,     0,     0,    15,    16,    11,
      13,    51,    27,    14,    35,    16,    18,    10,    33,    34,
      35,    23,    11,    44,    11,    27,    28,    29,    30,    18,
      50,    50,    35,    35,    10,    55,    52,    52,    27,    55,
      10,   124,    50,   141,    50,    36,    37,     0,    63,    64,
      65,    50,    62,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    62,    34,    35,   137,   149,    62,    62,    27,
     153,    29,    52,   171,   157,    55,   128,    35,    51,    94,
      95,   133,    44,   181,   136,    11,   169,    55,   103,    11,
      27,    38,    39,   165,   146,    51,    43,    10,   181,   114,
      38,    39,    34,    55,   156,    43,    53,    54,   160,    47,
      48,   163,    10,    51,    11,    53,    54,   127,   170,    11,
     135,    11,   137,    27,   176,    10,    10,    52,     0,     1,
     145,    52,   184,    35,    10,     7,     8,     9,    10,    55,
      50,    16,    21,    34,    15,    17,    10,    19,    20,    21,
     165,    32,    24,    25,    26,    14,    16,    34,    16,    31,
      32,    33,    16,     7,     8,     9,    10,    16,   178,    21,
      21,    32,    50,    45,    46,    32,    50,   187,    50,    51,
       7,     8,     9,    10,    46,   164,    -1,    31,    -1,    33,
      17,    -1,    19,    20,    21,    62,    -1,    -1,    25,    26,
      -1,    45,    46,    -1,    31,    32,    33,    51,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      -1,    -1,    -1,    50,    51,     7,     8,     9,    10,    -1,
      -1,    -1,    31,    -1,    33,    17,    -1,    19,    20,    21,
      -1,    -1,    -1,    25,    26,    -1,    45,    46,    -1,    31,
      32,    33,    51,    -1,    22,    -1,    -1,    38,    39,    -1,
      -1,    -1,    43,    45,    46,    -1,    47,    48,    -1,    51,
      38,    39,    53,    54,    -1,    43,    -1,    45,    46,    47,
      48,    -1,    38,    39,    -1,    53,    54,    43,    44,    45,
      46,    47,    48,    -1,    38,    39,    52,    53,    54,    43,
      -1,    45,    46,    47,    48,    -1,    38,    39,    52,    53,
      54,    43,    44,    45,    46,    47,    48,    -1,    38,    39,
      -1,    53,    54,    43,    -1,    45,    46,    47,    48,    -1,
      -1,    -1,    -1,    53,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     8,     9,    10,    17,    19,    20,    21,
      24,    25,    26,    31,    32,    33,    45,    46,    51,    57,
      58,    59,    60,    61,    62,    66,    67,    68,    73,    74,
      76,    79,    83,    51,    51,    70,    10,    75,    11,    18,
      23,    27,    28,    29,    30,    35,    77,    78,    10,    11,
      10,    10,    31,    59,    73,    36,    37,    10,    73,    73,
      73,     0,    50,    51,    44,    51,    65,    73,    38,    39,
      43,    45,    46,    47,    48,    53,    54,    73,    84,    84,
      84,    55,    11,    11,    27,    11,    18,    27,    35,    78,
      80,    73,    22,    10,    35,    44,    52,    57,    65,    73,
      65,    73,    34,    44,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    52,    55,    52,    10,    11,    11,    11,
      70,    10,    73,    73,    52,    71,    52,    70,    72,    73,
      73,    10,    81,    72,    13,    35,    60,    68,    74,    50,
      60,    71,    50,    55,    71,    35,    73,    71,    65,    14,
      16,    70,    55,    82,    10,    16,    73,    71,    50,    34,
      72,    21,    15,    63,    64,    69,    10,    72,    32,    71,
      72,    14,    71,    71,    63,    65,    72,    71,    70,    16,
      16,    34,    71,    16,    60,    21,    21,    70,    72,    16,
      32,    71,    60,    32,    50,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 101 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_xpop); ;}
    break;

  case 11:
#line 104 "engines/director/lingo/lingo-gr.y"
    { yyerrok; ;}
    break;

  case 12:
#line 107 "engines/director/lingo/lingo-gr.y"
    {
		g_lingo->code1(g_lingo->c_varpush);
		g_lingo->codeString((yyvsp[(4) - (4)].s)->c_str());
		g_lingo->code1(g_lingo->c_assign);
		(yyval.code) = (yyvsp[(2) - (4)].code);
		delete (yyvsp[(4) - (4)].s); ;}
    break;

  case 13:
#line 113 "engines/director/lingo/lingo-gr.y"
    {
		g_lingo->code1(g_lingo->c_varpush);
		g_lingo->codeString((yyvsp[(2) - (4)].s)->c_str());
		g_lingo->code1(g_lingo->c_assign);
		(yyval.code) = (yyvsp[(4) - (4)].code);
		delete (yyvsp[(2) - (4)].s); ;}
    break;

  case 14:
#line 119 "engines/director/lingo/lingo-gr.y"
    {
		g_lingo->code1(g_lingo->c_varpush);
		g_lingo->codeString((yyvsp[(2) - (4)].s)->c_str());
		g_lingo->code1(g_lingo->c_assign);
		(yyval.code) = (yyvsp[(4) - (4)].code);
		delete (yyvsp[(2) - (4)].s); ;}
    break;

  case 15:
#line 127 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_xpop); ;}
    break;

  case 18:
#line 134 "engines/director/lingo/lingo-gr.y"
    {
		inst body = 0, end = 0;
		WRITE_UINT32(&body, (yyvsp[(5) - (8)].code));
		WRITE_UINT32(&end, (yyvsp[(6) - (8)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (8)].code) + 1] = body;	/* body of loop */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (8)].code) + 2] = end; ;}
    break;

  case 19:
#line 145 "engines/director/lingo/lingo-gr.y"
    {
		inst init = 0, finish = 0, body = 0, end = 0, inc = 0;
		WRITE_UINT32(&init, (yyvsp[(3) - (11)].code));
		WRITE_UINT32(&finish, (yyvsp[(6) - (11)].code));
		WRITE_UINT32(&body, (yyvsp[(8) - (11)].code));
		WRITE_UINT32(&end, (yyvsp[(9) - (11)].code));
		WRITE_UINT32(&inc, 1);
		(*g_lingo->_currentScript)[(yyvsp[(1) - (11)].code) + 1] = init;	/* initial count value */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (11)].code) + 2] = finish;/* final count value */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (11)].code) + 3] = body;	/* body of loop */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (11)].code) + 4] = inc;	/* increment */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (11)].code) + 5] = end; ;}
    break;

  case 20:
#line 161 "engines/director/lingo/lingo-gr.y"
    {
		inst init = 0, finish = 0, body = 0, end = 0, inc = 0;
		WRITE_UINT32(&init, (yyvsp[(3) - (12)].code));
		WRITE_UINT32(&finish, (yyvsp[(7) - (12)].code));
		WRITE_UINT32(&body, (yyvsp[(9) - (12)].code));
		WRITE_UINT32(&end, (yyvsp[(10) - (12)].code));
		WRITE_UINT32(&inc, -1);
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 1] = init;	/* initial count value */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 2] = finish;/* final count value */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 3] = body;	/* body of loop */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 4] = inc;	/* increment */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 5] = end; ;}
    break;

  case 21:
#line 175 "engines/director/lingo/lingo-gr.y"
    {
		inst then = 0, end = 0;
		WRITE_UINT32(&then, (yyvsp[(4) - (6)].code));
		WRITE_UINT32(&end, (yyvsp[(6) - (6)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (6)].code) + 1] = then;	/* thenpart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (6)].code) + 3] = end; 	/* end, if cond fails */

		g_lingo->processIf((yyvsp[(6) - (6)].code)); ;}
    break;

  case 22:
#line 183 "engines/director/lingo/lingo-gr.y"
    {
		inst then = 0, else1 = 0, end = 0;
		WRITE_UINT32(&then, (yyvsp[(4) - (12)].code));
		WRITE_UINT32(&else1, (yyvsp[(9) - (12)].code));
		WRITE_UINT32(&end, (yyvsp[(11) - (12)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 1] = then;	/* thenpart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 2] = else1;     /* elsepart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (12)].code) + 3] = end; 	/* end, if cond fails */

		g_lingo->processIf((yyvsp[(11) - (12)].code)); ;}
    break;

  case 23:
#line 195 "engines/director/lingo/lingo-gr.y"
    {
		inst then = 0, end = 0;
		WRITE_UINT32(&then, (yyvsp[(4) - (7)].code));
		WRITE_UINT32(&end, (yyvsp[(5) - (7)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (7)].code) + 1] = then;      /* thenpart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (7)].code) + 3] = end;      /* end, if cond fails */
		g_lingo->processIf((yyvsp[(5) - (7)].code)); ;}
    break;

  case 24:
#line 202 "engines/director/lingo/lingo-gr.y"
    {
		inst then = 0, else1 = 0, end = 0;
		WRITE_UINT32(&then, (yyvsp[(4) - (10)].code));
		WRITE_UINT32(&else1, (yyvsp[(7) - (10)].code));
		WRITE_UINT32(&end, (yyvsp[(8) - (10)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (10)].code) + 1] = then;      /* thenpart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (10)].code) + 2] = else1;     /* elsepart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (10)].code) + 3] = end;      /* end, if cond fails */
		g_lingo->processIf((yyvsp[(8) - (10)].code)); ;}
    break;

  case 25:
#line 211 "engines/director/lingo/lingo-gr.y"
    {
		inst then = 0, else1 = 0, end = 0;
		WRITE_UINT32(&then, (yyvsp[(4) - (10)].code));
		WRITE_UINT32(&else1, (yyvsp[(6) - (10)].code));
		WRITE_UINT32(&end, (yyvsp[(8) - (10)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (10)].code) + 1] = then;      /* thenpart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (10)].code) + 2] = else1;     /* elsepart */
		(*g_lingo->_currentScript)[(yyvsp[(1) - (10)].code) + 3] = end;      /* end, if cond fails */
		g_lingo->processIf((yyvsp[(8) - (10)].code)); ;}
    break;

  case 28:
#line 226 "engines/director/lingo/lingo-gr.y"
    {
		inst then = 0;
		WRITE_UINT32(&then, (yyvsp[(4) - (6)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (6)].code) + 1] = then;      /* thenpart */

		g_lingo->codeLabel((yyvsp[(1) - (6)].code)); ;}
    break;

  case 29:
#line 232 "engines/director/lingo/lingo-gr.y"
    {
		inst then = 0;
		WRITE_UINT32(&then, (yyvsp[(4) - (4)].code));
		(*g_lingo->_currentScript)[(yyvsp[(1) - (4)].code) + 1] = then;      /* thenpart */

		g_lingo->codeLabel((yyvsp[(1) - (4)].code)); ;}
    break;

  case 30:
#line 240 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(STOP); ;}
    break;

  case 31:
#line 241 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code2(g_lingo->c_eq, STOP); ;}
    break;

  case 33:
#line 244 "engines/director/lingo/lingo-gr.y"
    { (yyval.code) = g_lingo->code3(g_lingo->c_repeatwhilecode, STOP, STOP); ;}
    break;

  case 34:
#line 246 "engines/director/lingo/lingo-gr.y"
    {
		(yyval.code) = g_lingo->code3(g_lingo->c_repeatwithcode, STOP, STOP);
		g_lingo->code3(STOP, STOP, STOP);
		g_lingo->codeString((yyvsp[(3) - (3)].s)->c_str());
		delete (yyvsp[(3) - (3)].s); ;}
    break;

  case 35:
#line 252 "engines/director/lingo/lingo-gr.y"
    {
		(yyval.code) = g_lingo->code1(g_lingo->c_ifcode);
		g_lingo->code3(STOP, STOP, STOP);
		g_lingo->codeLabel(0); ;}
    break;

  case 36:
#line 257 "engines/director/lingo/lingo-gr.y"
    { (yyval.code) = g_lingo->code1(g_lingo->c_ifcode); g_lingo->code3(STOP, STOP, STOP); ;}
    break;

  case 37:
#line 259 "engines/director/lingo/lingo-gr.y"
    { (yyval.code) = g_lingo->_currentScript->size(); ;}
    break;

  case 38:
#line 261 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(STOP); (yyval.code) = g_lingo->_currentScript->size(); ;}
    break;

  case 39:
#line 263 "engines/director/lingo/lingo-gr.y"
    { (yyval.code) = g_lingo->_currentScript->size(); ;}
    break;

  case 42:
#line 268 "engines/director/lingo/lingo-gr.y"
    {
		(yyval.code) = g_lingo->code1(g_lingo->c_constpush);
		inst i = 0;
		WRITE_UINT32(&i, (yyvsp[(1) - (1)].i));
		g_lingo->code1(i); ;}
    break;

  case 43:
#line 273 "engines/director/lingo/lingo-gr.y"
    {
		(yyval.code) = g_lingo->code1(g_lingo->c_fconstpush);
		g_lingo->codeFloat((yyvsp[(1) - (1)].f)); ;}
    break;

  case 44:
#line 276 "engines/director/lingo/lingo-gr.y"
    {
		if ((yyvsp[(3) - (4)].narg) != g_lingo->_builtins[*(yyvsp[(1) - (4)].s)]->nargs)
			error("Built-in function %s expects %d arguments but got %d", (yyvsp[(1) - (4)].s)->c_str(), g_lingo->_builtins[*(yyvsp[(1) - (4)].s)]->nargs, (yyvsp[(3) - (4)].narg));

		(yyval.code) = g_lingo->code1(g_lingo->_builtins[*(yyvsp[(1) - (4)].s)]->func);
		delete (yyvsp[(1) - (4)].s); ;}
    break;

  case 45:
#line 282 "engines/director/lingo/lingo-gr.y"
    {
		(yyval.code) = g_lingo->code1(g_lingo->c_call);
		g_lingo->codeString((yyvsp[(1) - (4)].s)->c_str());

		inst numpar = 0;
		WRITE_UINT32(&numpar, (yyvsp[(3) - (4)].narg));
		g_lingo->code1(numpar);
		delete (yyvsp[(1) - (4)].s); ;}
    break;

  case 46:
#line 290 "engines/director/lingo/lingo-gr.y"
    {
		(yyval.code) = g_lingo->codeId(*(yyvsp[(1) - (1)].s));
		delete (yyvsp[(1) - (1)].s); ;}
    break;

  case 48:
#line 294 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_add); ;}
    break;

  case 49:
#line 295 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_sub); ;}
    break;

  case 50:
#line 296 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_mul); ;}
    break;

  case 51:
#line 297 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_div); ;}
    break;

  case 52:
#line 298 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_gt); ;}
    break;

  case 53:
#line 299 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_lt); ;}
    break;

  case 54:
#line 300 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_neq); ;}
    break;

  case 55:
#line 301 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_ge); ;}
    break;

  case 56:
#line 302 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_le); ;}
    break;

  case 57:
#line 303 "engines/director/lingo/lingo-gr.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 58:
#line 304 "engines/director/lingo/lingo-gr.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); g_lingo->code1(g_lingo->c_negate); ;}
    break;

  case 59:
#line 305 "engines/director/lingo/lingo-gr.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 60:
#line 308 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_mci); g_lingo->codeString((yyvsp[(2) - (2)].s)->c_str()); delete (yyvsp[(2) - (2)].s); ;}
    break;

  case 61:
#line 309 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_mciwait); g_lingo->codeString((yyvsp[(2) - (2)].s)->c_str()); delete (yyvsp[(2) - (2)].s); ;}
    break;

  case 62:
#line 310 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_printtop); ;}
    break;

  case 64:
#line 312 "engines/director/lingo/lingo-gr.y"
    { 	g_lingo->code2(g_lingo->c_constpush, (inst)0); // Push fake value on stack
								g_lingo->code1(g_lingo->c_procret); ;}
    break;

  case 66:
#line 317 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_global); g_lingo->codeString((yyvsp[(1) - (1)].s)->c_str()); delete (yyvsp[(1) - (1)].s); ;}
    break;

  case 67:
#line 318 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_global); g_lingo->codeString((yyvsp[(3) - (3)].s)->c_str()); delete (yyvsp[(3) - (3)].s); ;}
    break;

  case 68:
#line 329 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_gotoloop); ;}
    break;

  case 69:
#line 330 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_gotonext); ;}
    break;

  case 70:
#line 331 "engines/director/lingo/lingo-gr.y"
    { g_lingo->code1(g_lingo->c_gotoprevious); ;}
    break;

  case 71:
#line 332 "engines/director/lingo/lingo-gr.y"
    {
		g_lingo->code1(g_lingo->c_goto);
		g_lingo->codeString((yyvsp[(2) - (2)].s)->c_str());
		g_lingo->codeString("");
		delete (yyvsp[(2) - (2)].s); ;}
    break;

  case 72:
#line 337 "engines/director/lingo/lingo-gr.y"
    {
		g_lingo->code1(g_lingo->c_goto);
		g_lingo->codeString((yyvsp[(2) - (3)].s)->c_str());
		g_lingo->codeString((yyvsp[(3) - (3)].s)->c_str());
		delete (yyvsp[(2) - (3)].s);
		delete (yyvsp[(3) - (3)].s); ;}
    break;

  case 73:
#line 343 "engines/director/lingo/lingo-gr.y"
    {
		g_lingo->code1(g_lingo->c_goto);
		g_lingo->codeString("");
		g_lingo->codeString((yyvsp[(2) - (2)].s)->c_str());
		delete (yyvsp[(2) - (2)].s); ;}
    break;

  case 74:
#line 350 "engines/director/lingo/lingo-gr.y"
    { (yyval.s) = (yyvsp[(3) - (3)].s); ;}
    break;

  case 75:
#line 351 "engines/director/lingo/lingo-gr.y"
    { (yyval.s) = (yyvsp[(2) - (2)].s); ;}
    break;

  case 76:
#line 352 "engines/director/lingo/lingo-gr.y"
    { (yyval.s) = (yyvsp[(2) - (2)].s); ;}
    break;

  case 77:
#line 353 "engines/director/lingo/lingo-gr.y"
    { (yyval.s) = (yyvsp[(1) - (1)].s); ;}
    break;

  case 78:
#line 356 "engines/director/lingo/lingo-gr.y"
    { (yyval.s) = (yyvsp[(3) - (3)].s); ;}
    break;

  case 79:
#line 357 "engines/director/lingo/lingo-gr.y"
    { (yyval.s) = (yyvsp[(2) - (2)].s); ;}
    break;

  case 80:
#line 358 "engines/director/lingo/lingo-gr.y"
    { (yyval.s) = (yyvsp[(3) - (3)].s); ;}
    break;

  case 81:
#line 386 "engines/director/lingo/lingo-gr.y"
    { g_lingo->_indef = true; ;}
    break;

  case 82:
#line 387 "engines/director/lingo/lingo-gr.y"
    {
			g_lingo->code2(g_lingo->c_constpush, (inst)0); // Push fake value on stack
			g_lingo->code1(g_lingo->c_procret);
			g_lingo->define(*(yyvsp[(2) - (8)].s), (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].narg));
			g_lingo->_indef = false; ;}
    break;

  case 83:
#line 393 "engines/director/lingo/lingo-gr.y"
    { (yyval.narg) = 0; ;}
    break;

  case 84:
#line 394 "engines/director/lingo/lingo-gr.y"
    { g_lingo->codeArg((yyvsp[(1) - (1)].s)); (yyval.narg) = 1; ;}
    break;

  case 85:
#line 395 "engines/director/lingo/lingo-gr.y"
    { g_lingo->codeArg((yyvsp[(3) - (3)].s)); (yyval.narg) = (yyvsp[(1) - (3)].narg) + 1; ;}
    break;

  case 86:
#line 396 "engines/director/lingo/lingo-gr.y"
    { g_lingo->codeArg((yyvsp[(4) - (4)].s)); (yyval.narg) = (yyvsp[(1) - (4)].narg) + 1; ;}
    break;

  case 87:
#line 398 "engines/director/lingo/lingo-gr.y"
    { g_lingo->codeArgStore(); ;}
    break;

  case 88:
#line 401 "engines/director/lingo/lingo-gr.y"
    {
		g_lingo->code1(g_lingo->c_call);
		g_lingo->codeString((yyvsp[(1) - (3)].s)->c_str());
		inst numpar = 0;
		WRITE_UINT32(&numpar, (yyvsp[(3) - (3)].narg));
		g_lingo->code1(numpar); ;}
    break;

  case 89:
#line 409 "engines/director/lingo/lingo-gr.y"
    { (yyval.narg) = 0; ;}
    break;

  case 90:
#line 410 "engines/director/lingo/lingo-gr.y"
    { (yyval.narg) = 1; ;}
    break;

  case 91:
#line 411 "engines/director/lingo/lingo-gr.y"
    { (yyval.narg) = (yyvsp[(1) - (3)].narg) + 1; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2115 "engines/director/lingo/lingo-gr.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 414 "engines/director/lingo/lingo-gr.y"


