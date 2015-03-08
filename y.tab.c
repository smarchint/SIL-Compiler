
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "6.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	int lineno=1;
	int n,TypeFlag=1; 			//typeflag default to okay ie., every thing's fine
	
	#define DUMMY "Dummy"
	#define _Varlist 12
	#define _StmtList 13
	#define _Var 14
	#define _GDefList 15
	#define _Program 19
	#define _Truth 20
	#define _mod 25
	#define ARRAY 34
	#include "table2.c"
	#include "tree2.c"
	#define getline() printf("Error at %d\n",lineno);


	FILE * fp;

	void evalDecl(struct node *nd,int i);
//		| '(' Relexp ')'	{$$=$2;}
	struct node* t;



/* Line 189 of yacc.c  */
#line 103 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INT = 259,
     WRITE = 260,
     READ = 261,
     IF = 262,
     THEN = 263,
     ENDIF = 264,
     WHILE = 265,
     DO = 266,
     ENDWHILE = 267,
     EQEQ = 268,
     INTEGER = 269,
     MAIN = 270,
     EXIT = 271,
     SILBEGIN = 272,
     END = 273,
     DECL = 274,
     ENDDECL = 275,
     GBOOL = 276,
     GINT = 277,
     INTD = 278,
     BOOLD = 279,
     TRUE = 280,
     FALSE = 281,
     LE = 282,
     GE = 283,
     NE = 284,
     AND = 285,
     OR = 286,
     NOT = 287
   };
#endif
/* Tokens.  */
#define ID 258
#define INT 259
#define WRITE 260
#define READ 261
#define IF 262
#define THEN 263
#define ENDIF 264
#define WHILE 265
#define DO 266
#define ENDWHILE 267
#define EQEQ 268
#define INTEGER 269
#define MAIN 270
#define EXIT 271
#define SILBEGIN 272
#define END 273
#define DECL 274
#define ENDDECL 275
#define GBOOL 276
#define GINT 277
#define INTD 278
#define BOOLD 279
#define TRUE 280
#define FALSE 281
#define LE 282
#define GE 283
#define NE 284
#define AND 285
#define OR 286
#define NOT 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 31 "6.y"

	int val;
	char* id;
	struct node *ptr;



/* Line 214 of yacc.c  */
#line 211 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 223 "y.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   154

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  39
/* YYNRULES -- Number of states.  */
#define YYNSTATES  94

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,    38,     2,     2,
      42,    43,    36,    34,    45,    35,     2,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
      39,    44,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    10,    13,    15,    19,    23,    27,
      29,    32,    38,    44,    53,    62,    67,    72,    76,    78,
      82,    86,    90,    94,    98,   102,   105,   109,   113,   115,
     117,   119,   123,   127,   131,   135,   139,   141,   143,   145
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    53,    -1,    19,    51,    20,    -1,
      51,    52,    -1,    52,    -1,    22,    56,    41,    -1,    21,
      56,    41,    -1,    17,    54,    18,    -1,    55,    -1,    54,
      55,    -1,     5,    42,    58,    43,    41,    -1,     6,    42,
      59,    43,    41,    -1,     7,    42,    57,    43,     8,    54,
       9,    41,    -1,    10,    42,    57,    43,    11,    54,    12,
      41,    -1,    59,    44,    58,    41,    -1,    59,    44,    57,
      41,    -1,    56,    45,    59,    -1,    59,    -1,    58,    39,
      58,    -1,    58,    40,    58,    -1,    58,    28,    58,    -1,
      58,    27,    58,    -1,    58,    29,    58,    -1,    58,    13,
      58,    -1,    33,    57,    -1,    57,    30,    57,    -1,    57,
      31,    57,    -1,    25,    -1,    26,    -1,    59,    -1,    58,
      34,    58,    -1,    58,    35,    58,    -1,    58,    36,    58,
      -1,    58,    37,    58,    -1,    58,    38,    58,    -1,     4,
      -1,    59,    -1,     3,    -1,     3,    46,    58,    47,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    84,    84,    99,   102,   104,   108,   111,   116,   120,
     122,   126,   130,   134,   139,   143,   147,   154,   156,   161,
     163,   165,   167,   169,   171,   173,   175,   177,   179,   181,
     183,   187,   189,   191,   193,   195,   197,   199,   204,   206
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INT", "WRITE", "READ", "IF",
  "THEN", "ENDIF", "WHILE", "DO", "ENDWHILE", "EQEQ", "INTEGER", "MAIN",
  "EXIT", "SILBEGIN", "END", "DECL", "ENDDECL", "GBOOL", "GINT", "INTD",
  "BOOLD", "TRUE", "FALSE", "LE", "GE", "NE", "AND", "OR", "NOT", "'!'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "';'", "'('", "')'",
  "'='", "','", "'['", "']'", "$accept", "Program", "GDefblock",
  "GDefList", "GDecl", "Mainblock", "StmtList", "Stmt", "Varlist",
  "Relexp", "Expr", "Var", 0
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
     285,   286,   287,    33,    43,    45,    42,    47,    37,    60,
      62,    59,    40,    41,    61,    44,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    51,    51,    52,    52,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    56,    56,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     2,     1,     3,     3,     3,     1,
       2,     5,     5,     8,     8,     4,     4,     3,     1,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     5,     1,     0,
       2,    38,     0,    18,     0,     3,     4,     0,     0,     0,
       0,     0,     9,     0,     0,     7,     0,     6,     0,     0,
       0,     0,     8,    10,     0,    36,     0,    37,    17,     0,
       0,    28,    29,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    39,     0,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      15,    31,    32,    33,    34,    35,    11,    12,    26,    27,
       0,    24,    22,    21,    23,    19,    20,     0,     0,     0,
       0,     0,    13,    14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     6,     7,    10,    21,    22,    12,    44,
      45,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -39
static const yytype_int16 yypact[] =
{
     -10,    16,    23,    11,    54,    54,    86,   -39,   -39,    61,
     -39,    45,   -38,   -39,   -37,   -39,   -39,    60,    67,    80,
      81,    55,   -39,    57,    71,   -39,    54,   -39,    71,    54,
      17,    17,   -39,   -39,    17,   -39,   -23,   -39,   -39,    83,
      87,   -39,   -39,    17,    10,    76,   -12,    47,    51,    59,
      71,    71,    71,    71,    71,   -39,    90,    97,   -39,    17,
      17,   116,    71,    71,    71,    71,    71,    71,   138,   -39,
     -39,   110,   110,   -39,   -39,   -39,   -39,   -39,   -39,   120,
      61,   107,   107,   107,   107,   107,   107,    61,   130,   122,
     111,   112,   -39,   -39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -39,   -39,   -39,   -39,   145,   -39,   -28,   -19,   149,    20,
     -18,    -4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -31
static const yytype_int8 yytable[] =
{
      13,    13,    33,    25,    27,    23,    36,    26,    26,     1,
      39,    50,    51,    52,    53,    54,    49,    23,   -30,   -30,
      11,    35,    38,     8,    55,    40,    46,    46,     9,   -30,
      46,   -30,    71,    72,    73,    74,    75,     4,     5,    46,
      59,    60,    41,    42,    81,    82,    83,    84,    85,    86,
      43,    47,    88,    61,    48,    46,    46,    11,    11,    89,
      17,    18,    19,    58,    11,    20,    17,    18,    19,    33,
      33,    20,    62,    32,    11,    35,    23,    59,    60,    78,
      79,    59,    60,    23,    23,    23,    63,    64,    65,    62,
      68,    24,    69,    50,    51,    52,    53,    54,    66,    67,
      70,    34,    28,    63,    64,    65,    15,     4,     5,    29,
      50,    51,    52,    53,    54,    66,    67,    50,    51,    52,
      53,    54,    30,    31,    80,    11,    56,    17,    18,    19,
      57,    76,    20,    11,    91,    17,    18,    19,    77,    90,
      20,    50,    51,    52,    53,    54,    52,    53,    54,    87,
      59,    16,    92,    93,    14
};

static const yytype_uint8 yycheck[] =
{
       4,     5,    21,    41,    41,     9,    24,    45,    45,    19,
      28,    34,    35,    36,    37,    38,    34,    21,    30,    31,
       3,     4,    26,     0,    47,    29,    30,    31,    17,    41,
      34,    43,    50,    51,    52,    53,    54,    21,    22,    43,
      30,    31,    25,    26,    62,    63,    64,    65,    66,    67,
      33,    31,    80,    43,    34,    59,    60,     3,     3,    87,
       5,     6,     7,    43,     3,    10,     5,     6,     7,    88,
      89,    10,    13,    18,     3,     4,    80,    30,    31,    59,
      60,    30,    31,    87,    88,    89,    27,    28,    29,    13,
      43,    46,    41,    34,    35,    36,    37,    38,    39,    40,
      41,    44,    42,    27,    28,    29,    20,    21,    22,    42,
      34,    35,    36,    37,    38,    39,    40,    34,    35,    36,
      37,    38,    42,    42,     8,     3,    43,     5,     6,     7,
      43,    41,    10,     3,    12,     5,     6,     7,    41,     9,
      10,    34,    35,    36,    37,    38,    36,    37,    38,    11,
      30,     6,    41,    41,     5
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    49,    50,    21,    22,    51,    52,     0,    17,
      53,     3,    56,    59,    56,    20,    52,     5,     6,     7,
      10,    54,    55,    59,    46,    41,    45,    41,    42,    42,
      42,    42,    18,    55,    44,     4,    58,    59,    59,    58,
      59,    25,    26,    33,    57,    58,    59,    57,    57,    58,
      34,    35,    36,    37,    38,    47,    43,    43,    57,    30,
      31,    43,    13,    27,    28,    29,    39,    40,    43,    41,
      41,    58,    58,    58,    58,    58,    41,    41,    57,    57,
       8,    58,    58,    58,    58,    58,    58,    11,    54,    54,
       9,    12,    41,    41
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 2:

/* Line 1455 of yacc.c  */
#line 84 "6.y"
    {	
									//print_table();
									if(TypeFlag==0) {printf("Exit status = failure\n");exit(0);}
									else{
										//	$$=makenode($2,NULL,_Program,0,DUMMY);
										//evaltree($2,-1);
										fp= fopen("outfile.txt","a");
										CodeGen((yyvsp[(2) - (2)].ptr));
										int z= fclose(fp);
										print_table();
										exit(1);
									}
								}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 99 "6.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr); evalDecl((yyvsp[(2) - (3)].ptr),-1);}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 102 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),_GDefList,0,DUMMY);}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 104 "6.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 108 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),NULL,GINT,0,DUMMY); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 111 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),NULL,GBOOL,0,DUMMY); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 116 "6.y"
    {(yyval.ptr) = (yyvsp[(2) - (3)].ptr);}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 120 "6.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 122 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),_StmtList,0,DUMMY);}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 128 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (5)].ptr),NULL,WRITE,0,DUMMY);if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 132 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (5)].ptr),NULL,READ,0,DUMMY);if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 136 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),IF,0,DUMMY);if(!type_check((yyval.ptr),1)==1){ getline();TypeFlag = 0;}}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 141 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),WHILE,0,DUMMY);if(!type_check((yyval.ptr),1)==1) {getline();TypeFlag = 0;}}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 145 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),'=',0,DUMMY);if(!type_check((yyval.ptr),1)==1) {getline();TypeFlag = 0;}}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 149 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),'=',0,DUMMY);if(!type_check((yyval.ptr),1)==1) {getline();TypeFlag = 0;}}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 154 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),_Varlist,0,DUMMY);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 156 "6.y"
    {(yyval.ptr)=makenode(NULL,(yyvsp[(1) - (1)].ptr),_Varlist,0,DUMMY);}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 161 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'<',0,DUMMY);	if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 163 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'>',0,DUMMY);	if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 165 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),GE,0,DUMMY);		if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 167 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),LE,0,DUMMY);		if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 169 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NE,0,DUMMY);		if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 171 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),EQEQ,0,DUMMY);	if(!type_check((yyval.ptr),0)==1) {getline();TypeFlag = 0;}}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 173 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(2) - (2)].ptr),NULL,NOT,0,DUMMY);	if(!type_check((yyval.ptr),1)==1) {getline();TypeFlag = 0;}}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 175 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),AND,0,DUMMY);	if(!type_check((yyval.ptr),1)==1){getline();TypeFlag = 0;}}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 177 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),OR,0,DUMMY);		if(!type_check((yyval.ptr),1)==1) {getline();TypeFlag = 0;}}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 179 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,_Truth,TRUE,DUMMY);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 181 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,_Truth,FALSE,DUMMY);}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 183 "6.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 187 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'+',0,DUMMY); if(!type_check((yyval.ptr),0)==0) {getline();TypeFlag = 0;}}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 189 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'-',0,DUMMY); if(!type_check((yyval.ptr),0)==0) {getline();TypeFlag = 0;}}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 191 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'*',0,DUMMY); if(!type_check((yyval.ptr),0)==0) {getline();TypeFlag = 0;}}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 193 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'/',0,DUMMY); if(!type_check((yyval.ptr),0)==0) {getline();TypeFlag = 0;}}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 195 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),_mod,0,DUMMY);if(!type_check((yyval.ptr),0)==0) {getline();TypeFlag = 0;}}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 197 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,INT,(yyvsp[(1) - (1)].val),DUMMY);}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 199 "6.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 204 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,ID,0,(yyvsp[(1) - (1)].id));}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 206 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (4)].ptr),NULL,ARRAY,0,(yyvsp[(1) - (4)].id));}
    break;



/* Line 1455 of yacc.c  */
#line 1776 "y.tab.c"
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 1675 of yacc.c  */
#line 211 "6.y"


//version 2   typecheck need to be improved


//returns type or (1 for 'okay' and 0 for 'not okay')
int type_check(struct node* nd,int i){
	if(nd == NULL) return i;

	//base case-------------------------
	if(nd->flag==ID || nd->flag==ARRAY ) {

		struct gnode* temp=fetch(nd->varname);
		if(temp->type == 0)
		return 0;
		else return 1;

	} 
	if(nd->flag==INT) {
		return 0;
	} 	

	if(nd->flag==_Truth){

		return 1;
	}


 	//operators ----------------------------------------
 	//returns type
	if(nd->flag=='+'||nd->flag=='-'||nd->flag=='/'||nd->flag=='*'||\
		nd->flag==_mod ) {
		
		//i == 0 : true  since exp has int but no  bools
		if (type_check(nd->left,0)==0 && type_check(nd->right,0) ==0){
			return 0;
		}
		else{
			//error msg
			//printf("Expected int but found bool in operators\n");
			return 1;
		}
		
	}

	//comparators--------------------------------------------------(can merge comparator and oiperator cases)
	//returns type
	if(nd->flag=='>'||nd->flag=='<'||nd->flag==EQEQ||\
		nd->flag==NE||nd->flag==LE ||nd->flag==GE){

		//i == 0 : true  since exp has int but no  bools
		if (type_check(nd->left,0)==0 && type_check(nd->right,0) ==0){
			return 1;
		}
		else{
			//error msg
			//printf("Expected int but foiund bool in comparators\n");
			return 0;
		}
	}

	//logical connectives--------------------------------------------
	//returns type
	else if(nd->flag==AND ||nd->flag==OR||nd->flag==NOT){
		
		//i==1 :
		if (type_check(nd->left,1)==1 &&  type_check(nd->right,1)==1 ) 
			return 1;
		else {
			//erroe msg
			//printf("Expected bool but found int  --or -- some found some bool in comparators\n");
			return 0;
		}
	
	}


	//assignment---------------------------------------------------------
	else if(nd->flag== '='){			//i value not considered in te call

		if((type_check(nd->left,0)==type_check(nd->right,0)) ||\
			(type_check(nd->left,1)==type_check(nd->right,1))){
			//printf("Left : %d  Right : %d\n",nd->left->val,nd->right->val);
			return 1;	//okay
		}
		else{	
			printf("TYPE MISMATCH\n");
			return 0;	//not okaay
		}
	}

	//@Read---------------------------------------------------------------- 
	//read only int
	else if(nd->flag==READ){			//i value for read and write
		
		struct gnode * temp= fetch(nd->left->varname);
		
		//if left has a ijnt
		if(temp->type==0) {return 1;} 	//okay
		else {
			printf("bools cannot be read\n");
			return 0;
		}

	}

	//Write----------------------------------------------------------------
	//write only int
	else if(nd->flag==WRITE){

		if(type_check(nd->left,i)==0) return 1;	//okay
		else{
			//error msg
			//printf("bools cannot be written\n");
			return 0;
		}					//not okay
	}

	//if conditional------------------------------------------------------
	else if(nd->flag == IF){	
		
		if(type_check(nd->left,1)==1) return 1; //okay
		else{
			//error msg
			//printf("Expected bool but found int in  if condition\n");
			return 0;							//not okay
		}
	}
	
	//while------------------------------------------------------------
	else if(nd->flag == WHILE){

		if(type_check(nd->left,1)==1) return 1;
		else {
			//error msg
			//printf("Expected bool but found int in  while condition\n");
			return 0;
		}
	}
	//end of function : type_check
}


//CODE GENERATION PART=================================================================


//free reg after completion of its requirement
int RegNo = -1;	//range 0-7

//use and increase to size
int LocNo = 0;	//range 0-25

//suggestion : Add error msg for redeclarations;
void evalDecl(struct node *nd,int i){	//i for type filling in table
	if(nd == NULL ) return;
	switch(nd->flag){
		case _GDefList: evalDecl(nd->left,i);evalDecl(nd->right,i); break;
		case GINT: 		evalDecl(nd->left,0); break;
		case GBOOL: 	evalDecl(nd->left,1); break;
		case _Varlist: 	evalDecl(nd->left,i);
						if(nd->right->flag==ID) {
							gentry(nd->right->varname,i,1,LocNo);
							LocNo++;
						}
						else if(nd->right->flag == ARRAY){
							int size = nd->right->left->val;
							gentry(nd->right->varname,i,size,LocNo);
							LocNo += size;							

						}
						break;
	}
}



int getLoc(char * varname){

	struct gnode * temp;
	
	temp = fetch(varname);

	return temp->bind;
}

int getReg(){
//Suggestion : Add error msg if RegNo exceeds 7
	
	RegNo++;

	int r = RegNo;
	
	return r;
}

void freeReg(int r){	
//if reg r at top of reg stack the remove else return error

	//if(r==RegNo)
	RegNo--;

}

int getLocArray(struct node * nd){
	
	int r = CodeGen(nd->left);

	int loc = getLoc(nd->varname);

	int r1 = getReg();

	int foo = fprintf(fp,"MOV R%d,%d\n",r1,loc);	//mov r1 loc

	foo = fprintf(fp,"ADD R%d,R%d\n",r,r1);//add r + r1	

	freeReg(r1);

	return r; //contains final location of array element


}

//generates machine code for SIM
//returns regno to be used at an instance
int CodeGen(struct node *nd){
	if(nd==NULL) return -1;

	switch(nd->flag){
		case INT:	{int r = getReg();

					int foo = fprintf(fp,"MOV R%d,%d\n",r,nd->val);

					return r;

					break;} 

		case ID :	{int r = getReg();
					
					int loc = getLoc(nd->varname);
					
					int foo = fprintf(fp,"MOV R%d,[%d]\n",r,loc);
					
					return r;
					
					break;}

		case ARRAY :{int r = getReg();
					
					int r1 = getLocArray(nd);	// in a register

					int foo = fprintf(fp,"MOV R%d,[R%d]\n",r,r1);//mov r [r1] 	

					freeReg(r1);

					return r;
					
					break;}
		
		case '+' :	
					
					{int r1 = CodeGen(nd->left);	//increment for r1 will be done in rec part
					
					int r2 = CodeGen(nd->right);

					int foo =  fprintf(fp,"ADD R%d,R%d\n",r1,r2);

					freeReg(r2);

					return r1;	

					break;}

		case '=' :	//one reg for returning remaining canbe disposed off
					{int r = CodeGen(nd->right);				//right part of =

					if(nd->left->flag == ID){
						int loc = getLoc(nd->left->varname);

						int foo = fprintf(fp,"MOV [%d],R%d\n",loc,r);
						
						freeReg(r);

						return -1;
					}

					else if(nd->left->flag == ARRAY){		//left part of =

						int r1 = getLocArray(nd->left);

						int foo =  fprintf(fp,"MOV [R%d],R%d\n",r1,r);

						freeReg(r1);

						freeReg(r);

						return -1;						

					}
					
					break;}

		case _StmtList:{CodeGen(nd->left);CodeGen(nd->right);break;}

		case WRITE : //printing out of register
					{if(nd->left->flag == ID){
						
						int loc = getLoc(nd->left->varname);
						
						int r = getReg();

						int foo = fprintf(fp,"MOV R%d,[%d]\n",r,loc);

						foo = fprintf(fp,"OUT R%d\n",r);

						freeReg(r);

						return -1;


					}
					else if(nd->left->flag == ARRAY){

						int r1 = getLocArray(nd->left);
						
						int r = getReg();

						int foo = fprintf(fp,"MOV R%d,[%d]\n",r,r1);

						foo = fprintf(fp,"OUT R%d\n",r);

						freeReg(r);

						freeReg(r1);

						return -1;


					}
					break;}

		//case :



	}



}





//========================EVAL TREE


/*
//improvement required : use switch and cases to make code pretty
//tree evaluation------------======================================================
int evaltree(struct node* nd,int i){		//infix eval
	//printf("Evaluation\n");
	if (nd == NULL) {	
		return 1;
	}
	//print(nd);/
	if(nd->flag==INT){		//integer
		return nd->val;
	}	

	//check both sides as integer
	if (nd->flag=='+')
		return (evaltree(nd->left,i) + evaltree(nd->right,i));

	else if(nd->flag== '*')
		return (evaltree(nd->left,i) * evaltree(nd->right,i));
	
	else if(nd->flag=='/')
	 	return (evaltree(nd->left,i) / evaltree(nd->right,i));
	
	else if(nd->flag=='-')
	 	{	printf("%d - %d\n",evaltree(nd->left,i) ,evaltree(nd->right,i) );
	 		int dog= (evaltree(nd->left,i) - evaltree(nd->right,i));
	 		printf("dog = %d\n",dog);
	 		return dog;
	 	}

	else if(nd->flag==_mod)
	 	{	printf("%d mod %d\n",evaltree(nd->left,i) ,evaltree(nd->right,i) );
	 		int dog= (evaltree(nd->left,i) % evaltree(nd->right,i));
	 		printf("dog = %d\n",dog);
	 		return dog;
	 	}



	else if(nd->flag=='>'){
		if (evaltree(nd->left,i) > evaltree(nd->right,i)) return TRUE;
	 	else return FALSE;
	}
	else if(nd->flag=='<'){
	 	if (evaltree(nd->left,i) < evaltree(nd->right,i)) return TRUE;
	 	else return FALSE;
	}

	else if(nd->flag==EQEQ){
	 	if (evaltree(nd->left,i) == evaltree(nd->right,i)) return TRUE;
	 	else return FALSE;
	}


	//later added
	else if(nd->flag==NE){
	 	if (evaltree(nd->left,i)!=evaltree(nd->right,i)) return TRUE;
	 	else return FALSE;
	}
	else if(nd->flag==GE){
	 	if (evaltree(nd->left,i)>= evaltree(nd->right,i)) return TRUE;
	 	else return FALSE;
	}
	else if(nd->flag==LE){
	 	if (evaltree(nd->left,i) <= evaltree(nd->right,i)) return TRUE;
	 	else return FALSE;
	}



	//checking for bool (and. or .not . )
	if(nd->flag==AND){
		if (evaltree(nd->left,i) == TRUE  && evaltree(nd->right,i) == TRUE )
			{;return TRUE;}
		else return FALSE;
	}
	else if(nd->flag==OR){
		if (evaltree(nd->left,i) == FALSE  && evaltree(nd->right,i) == FALSE )
		return FALSE;
		else return TRUE;
	}
	else if(nd->flag==NOT){
	 	if (evaltree(nd->left,i) == TRUE )  return FALSE;
		else return TRUE;
	}

	
	else if(nd->flag==_Truth){
		//printf("Asked for %d\n",nd->val);
			return nd->val;
	}


	else if(nd->flag== '='){
		int t=evaltree(nd->right,i);
			//printf("Doggie kruger %d",nd->right->flag);
			//printf("changer  %d\n",t);			
			//printf("found to change : %s\n",nd->left->varname);
		if(nd->left->flag==ID)   set(nd->left->varname,t,0);

		else if(nd->left->flag==ARRAY){
			int place = evaltree(nd->left->left,i);
			set(nd->left->varname,t,place);
		}


	}
	

	else if(nd->flag==_Program){
		evaltree(nd->left,i);
		evaltree(nd->right,i);
	}

	else if(nd->flag==_GDefList){
		evaltree(nd->left,i);
		evaltree(nd->right,i);
	}
	else if(nd->flag==GINT){	//to declaration
		evaltree(nd->left,0);	//important type here

	}
	else if(nd->flag==GBOOL){	//here too----------
		evaltree(nd->left,1);	
	}

	else if(nd->flag==ID){		//getter
		//printf("test@identi : %s\n",need->varname);
		struct gnode * temp;
		temp=fetch(nd->varname);
		int num= *(temp->bind);
		return num;

	}

	else if(nd->flag==ARRAY){
		struct gnode * temp;
		int place=evaltree(nd->left,i);
		temp=fetch(nd->varname);
		int num= *(temp->bind+place);
		return num;
		
	}

	else if(nd->flag==_Varlist){
		evaltree(nd->left,i);
		
		if(nd->right->flag==ID) {
			gentry(nd->right->varname,i,1);
			return 1;
		}
		
		else if(nd->right->flag==ARRAY){
			int size=evaltree(nd->right->left,i);
			gentry(nd->right->varname,i,size);
			return 1;
		}
	}

	else if(nd->flag==INTD){
		evaltree(nd->left,0);				//type =0 for integers
				
	}
	else if(nd->flag==READ){				//alpha : need to check
		
		int temp;	
		printf("Enter a number : ");
		scanf("%d",&temp);

		if(nd->left->flag==ID)
			set(nd->left->varname,temp,0); //set
		else{
			int place = evaltree(nd->left->left,i);
			set(nd->left->varname,temp,place);
		}
		printf("reading done\n");
		
	}

	else if(nd->flag==WRITE){

		printf("printing %d\n",evaltree(nd->left,i));

	}

	else if(nd->flag==IF){	
		
		if (evaltree(nd->left,i)==TRUE) evaltree(nd->right,i);
		else return 1;
	}

	else if(nd->flag==WHILE){

		while(evaltree(nd->left,i) == TRUE){
			evaltree(nd->right,i);
		}

	}

	else if(nd->flag == _StmtList){

		evaltree(nd->left,i);
		evaltree(nd->right,i);

	}

	return 1;
}
*/
