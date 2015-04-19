
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
	#define FUNC 35
	#define _ArgList 36
	#define _Arg 37
	#define _GIdList 38
	#define _List 39
	#define _LDefList 40
	#define _LIdList 41
	#define _Fdeflist 42
	#define _Fdef 43
	#define _ARG_LVAR 44
	#define _junc 45
	#define HEAD 1
	#define L_HEAD 0
	#define _body 46
	#define _ExpList 47
	#define _main 48
	#define _pointer 49

	int POINT = 5;
	#include "table2.c"
	#include "tree2.c"
	#define getline() printf("Error at %d\n",lineno);
	

	int agcount =1;

	//===GLOBAL VARIABLES used in codegen part

	//reg call count
	int regCallCount = 0;

	int regStack[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
	

	//for label generation
	int Label=0;

	//free reg after completion of its requirement
	int RegNo = -1;	//range 0-7

	//use and increase to size
	int LocNo = 0;	//range 0-25

	int BP = 0;
	int SP = 0;

	//============================================


	FILE * fp;
	char * current_func;
	void evalDecl(int flag ,struct node *nd,int i,char * name);
	void flush_local();
	void ret_check(int i,struct node * nd);
	void install_args_to_locals(int i,struct node * nd);
	void push_list(struct node * nd);
	void pop_list(struct node * nd);
	void func_code_gen(int i,struct node * nd);
	void err_arg(int i,struct node * nd);
	void alloc_mem_for_func_locals(struct node * nd);
	void bind_locals_to_mem(int i,struct node * nd);
	void freeReg(int r,struct node * nd);
	void local_bind_count_init();
	int get_local_bind_count();
	void arg_bind_count_init();
	int get_arg_bind_count();

//void func_init(struct node * ) ask anoosh abt this #args list struct in c lang


void main_init(struct node * nd){
		if(TypeFlag==0) {printf("Exit status = failure\n");exit(0);}
		print_table();	
		int foo = fprintf(fp,"START\n");
		///fprintf(fp,"MOV BP, 0\n");
		//fprintf(fp, "MOV SP,BP\n" );
		fprintf(fp,"MOV BP, %d\n",LocNo-1);
		fprintf(fp,"MOV SP,BP\n");
		printf("Initial BP is at %d\n",LocNo-1);
		//fprintf(fp,"PUSH BP\n");
		int m = local_head->bind;	
		int r = getReg();
		int r1 = getReg();
		fprintf(fp, "MOV R%d,%d\n",r,m );
		fprintf(fp, "MOV R%d,SP\n",r1 );
		fprintf(fp, "ADD R%d,R%d\n",r,r1 );
		fprintf(fp,"MOV SP,R%d\n",r);
		freeReg(r1,NULL);
		freeReg(r,NULL);
		CodeGen(nd);
		foo = fprintf(fp,"HALT");
		int z= fclose(fp);
		print_table();
		exit(1);
}

void error(int i){
	getline();
	switch(i){
		case 1: {printf("Undeclared Variable\n");}
		case 2: {printf("Redeclared Variable\n");}
		case 3: {printf("Expected int\n");}
		case 4: {printf("Expected bool\n");}
		case 5: {printf("Type Mismatch\n");}
		case 6: {printf("Return type error\n");}
		case 7: {printf("Undeclared function\n");}
		case 8: {printf("redeclared function\n");}
		case 9: {printf("arguments mismatch\n");}
		case 10:{printf("argument pointer error\n");}
	}
	exit(1);
}
//for pointeres from callee perspective
int get_pointer_val(char* _name){
	int r  = get_pointer_addr( _name);
	fprintf(fp,"MOV R%d,[R%d]\n",r,r);
	return r;
}

int get_pointer_addr(struct node * nd){
	int r = getReg();
	int r1 = getReg();
	int flag = 0;		//to distinguish from global to local -- BP issue in global
	struct gnode * temp;
	temp = fetch(head,nd->varname);
	if(temp == NULL) temp = fetch(local_head,nd->varname);
	else flag =1;
	if(temp  ==  NULL) {error(10);}
	int m = temp->bind;
	fprintf(fp,"MOV R%d,%d\n",r,m);
	if(nd->left) {
		int r2 = CodeGen(nd->left);
		fprintf(fp,"ADD R%d,R%d\n",r,r2);
		freeReg(r2,nd);
	}
	fprintf(fp,"MOV R%d,0\n",r1);
	if(flag!=1) fprintf(fp,"MOV R%d,BP\n",r1);
	fprintf(fp,"ADD R%d,R%d\n",r,r1 );
	freeReg(r1,NULL);
	return r;
}



/* Line 189 of yacc.c  */
#line 235 "y.tab.c"

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
     ELSE = 264,
     ENDIF = 265,
     WHILE = 266,
     DO = 267,
     ENDWHILE = 268,
     EQEQ = 269,
     INTEGER = 270,
     MAIN = 271,
     EXIT = 272,
     SILBEGIN = 273,
     END = 274,
     DECL = 275,
     ENDDECL = 276,
     RET = 277,
     GBOOL = 278,
     GINT = 279,
     INTD = 280,
     BOOLD = 281,
     TRUE = 282,
     FALSE = 283,
     LE = 284,
     GE = 285,
     NE = 286,
     AND = 287,
     OR = 288,
     NOT = 289
   };
#endif
/* Tokens.  */
#define ID 258
#define INT 259
#define WRITE 260
#define READ 261
#define IF 262
#define THEN 263
#define ELSE 264
#define ENDIF 265
#define WHILE 266
#define DO 267
#define ENDWHILE 268
#define EQEQ 269
#define INTEGER 270
#define MAIN 271
#define EXIT 272
#define SILBEGIN 273
#define END 274
#define DECL 275
#define ENDDECL 276
#define RET 277
#define GBOOL 278
#define GINT 279
#define INTD 280
#define BOOLD 281
#define TRUE 282
#define FALSE 283
#define LE 284
#define GE 285
#define NE 286
#define AND 287
#define OR 288
#define NOT 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 163 "6.y"

	int val;
	char* id;
	struct node *ptr;



/* Line 214 of yacc.c  */
#line 347 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 359 "y.tab.c"

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
#define YYLAST   400

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,     2,     2,    40,    49,     2,
      47,    48,    38,    36,    44,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      41,    52,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    14,    17,    19,    23,    27,
      31,    33,    35,    40,    45,    49,    53,    55,    58,    61,
      65,    67,    69,    72,    75,    77,    80,    82,    94,   106,
     117,   128,   132,   136,   139,   141,   145,   149,   153,   155,
     164,   172,   174,   177,   183,   189,   198,   209,   218,   223,
     227,   231,   235,   239,   243,   247,   250,   254,   258,   260,
     262,   266,   270,   274,   278,   282,   284,   286,   291,   295,
     299,   301,   303,   306,   312,   314
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    55,    64,    72,    -1,    55,    72,    -1,
      20,    56,    21,    -1,    56,    57,    -1,    57,    -1,    24,
      58,    43,    -1,    23,    58,    43,    -1,    58,    44,    59,
      -1,    59,    -1,     3,    -1,     3,    45,    75,    46,    -1,
       3,    47,    60,    48,    -1,     3,    47,    48,    -1,    60,
      43,    61,    -1,    61,    -1,    24,    62,    -1,    23,    62,
      -1,    62,    44,    63,    -1,    63,    -1,     3,    -1,    49,
       3,    -1,    64,    66,    -1,    66,    -1,    73,    67,    -1,
      67,    -1,    24,     3,    47,    60,    48,    50,    68,    18,
      65,    19,    51,    -1,    23,     3,    47,    60,    48,    50,
      68,    18,    65,    19,    51,    -1,    24,     3,    47,    48,
      50,    68,    18,    65,    19,    51,    -1,    23,     3,    47,
      48,    50,    68,    18,    65,    19,    51,    -1,    22,    75,
      43,    -1,    20,    69,    21,    -1,    69,    70,    -1,    70,
      -1,    24,    71,    43,    -1,    23,    71,    43,    -1,    71,
      44,     3,    -1,     3,    -1,    16,    50,    68,    18,    73,
      67,    19,    51,    -1,    16,    50,    18,    73,    67,    19,
      51,    -1,    74,    -1,    73,    74,    -1,     5,    47,    75,
      48,    43,    -1,     6,    47,    78,    48,    43,    -1,     7,
      47,    75,    48,     8,    73,    10,    43,    -1,     7,    47,
      75,    48,     8,    73,     9,    73,    10,    43,    -1,    11,
      47,    75,    48,    12,    73,    13,    43,    -1,    78,    52,
      75,    43,    -1,    75,    41,    75,    -1,    75,    42,    75,
      -1,    75,    30,    75,    -1,    75,    29,    75,    -1,    75,
      31,    75,    -1,    75,    14,    75,    -1,    35,    75,    -1,
      75,    32,    75,    -1,    75,    33,    75,    -1,    27,    -1,
      28,    -1,    75,    36,    75,    -1,    75,    37,    75,    -1,
      75,    38,    75,    -1,    75,    39,    75,    -1,    75,    40,
      75,    -1,     4,    -1,    78,    -1,     3,    47,    76,    48,
      -1,     3,    47,    48,    -1,    76,    44,    77,    -1,    77,
      -1,    75,    -1,    49,     3,    -1,    49,     3,    45,    75,
      46,    -1,     3,    -1,     3,    45,    75,    46,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   210,   210,   216,   222,   224,   225,   227,   228,   230,
     231,   233,   234,   236,   237,   239,   240,   242,   243,   245,
     246,   248,   249,   251,   252,   254,   255,   257,   273,   290,
     309,   328,   331,   333,   334,   337,   338,   341,   342,   345,
     353,   365,   366,   370,   373,   376,   379,   383,   386,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   403,   404,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   417,
     418,   421,   422,   423,   426,   427
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INT", "WRITE", "READ", "IF",
  "THEN", "ELSE", "ENDIF", "WHILE", "DO", "ENDWHILE", "EQEQ", "INTEGER",
  "MAIN", "EXIT", "SILBEGIN", "END", "DECL", "ENDDECL", "RET", "GBOOL",
  "GINT", "INTD", "BOOLD", "TRUE", "FALSE", "LE", "GE", "NE", "AND", "OR",
  "NOT", "'!'", "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "';'",
  "','", "'['", "']'", "'('", "')'", "'&'", "'{'", "'}'", "'='", "$accept",
  "Program", "GDefblock", "GDefList", "GDecl", "GIdList", "GId", "ArgList",
  "Arg", "List", "item", "FdefList", "Body", "Fdef", "retExp", "LDefblock",
  "LDefList", "LDecl", "LIdList", "Mainblock", "StmtList", "Stmt", "Expr",
  "ExpList", "Expr1", "Var", 0
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
     285,   286,   287,   288,   289,    33,    43,    45,    42,    47,
      37,    60,    62,    59,    44,    91,    93,    40,    41,    38,
     123,   125,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    59,    59,    60,    60,    61,    61,    62,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    66,
      66,    67,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    76,
      76,    77,    77,    77,    78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     3,     2,     1,     3,     3,     3,
       1,     1,     4,     4,     3,     3,     1,     2,     2,     3,
       1,     1,     2,     2,     1,     2,     1,    11,    11,    10,
      10,     3,     3,     2,     1,     3,     3,     3,     1,     8,
       7,     1,     2,     5,     5,     8,    10,     8,     4,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     1,     1,
       3,     3,     3,     3,     3,     1,     1,     4,     3,     3,
       1,     1,     2,     5,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     6,     1,     0,
       0,     0,     0,    24,     3,    11,     0,    10,     0,     4,
       5,     0,     0,     0,    23,     2,     0,     0,     8,     0,
       7,     0,     0,     0,     0,     0,    74,    65,    58,    59,
       0,     0,    66,     0,     0,    14,     0,    16,     9,    74,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    21,     0,    18,    20,    17,     0,    13,
       0,     0,     0,     0,     0,     0,    42,     0,    38,     0,
       0,    32,    33,     0,     0,     0,     0,     0,     0,    68,
       0,    71,     0,    70,    54,    52,    51,    53,    56,    57,
      60,    61,    62,    63,    64,    49,    50,    22,     0,    15,
       0,     0,     0,     0,     0,     0,     0,    36,     0,    35,
       0,     0,     0,     0,     0,    75,    72,     0,    67,    19,
       0,     0,     0,     0,    31,    40,    48,    37,     0,     0,
       0,     0,     0,     0,    69,    43,    44,     0,     0,    39,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
      25,     0,     0,     0,    73,     0,     0,     0,    30,     0,
      29,     0,     0,    45,    47,    28,    27,     0,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     7,    16,    17,    46,    47,    85,
      86,    12,   170,    13,   171,    33,    59,    60,    99,    14,
     172,    55,   111,   112,   113,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -58
static const yytype_int16 yypact[] =
{
     -19,    40,    16,    -2,    15,    15,    87,   -58,   -58,     9,
      72,    96,    -2,   -58,   -58,    35,    45,   -58,    63,   -58,
     -58,    80,    56,    68,   -58,   -58,     1,   -17,   -58,    15,
     -58,   389,   111,   108,   -13,    -4,    82,   -58,   -58,   -58,
       1,   187,   -58,    12,    12,   -58,   -10,   -58,   -58,    98,
     106,   117,   126,   150,   342,   -58,   120,   195,   195,   134,
     -58,   389,   149,    -9,   157,    -3,     1,    38,    54,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,   -58,   -58,   205,   186,   -58,   186,   125,   -58,
       1,   229,     1,     1,     1,   212,   -58,     1,   -58,   116,
     119,   -58,   -58,   342,   214,   185,   214,   193,   208,   -58,
     233,   288,   -36,   -58,   237,    -5,    -5,    -5,    54,   302,
     321,   321,    83,    83,    83,    91,    -5,   -58,    12,   -58,
     138,   204,   152,   173,   248,   202,   268,   -58,   252,   -58,
     244,   238,   214,   253,   214,   -58,   227,    74,   -58,   -58,
     230,   232,   275,   264,   -58,   -58,   -58,   -58,   241,   342,
     276,   342,   277,     1,   -58,   -58,   -58,   389,   389,   -58,
     274,   -58,   342,   342,   284,   342,   228,   371,   362,   245,
     -58,   293,   262,   295,   -58,   389,   272,   279,   -58,   285,
     -58,   286,   380,   -58,   -58,   -58,   -58,   280,   -58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,   -58,   -58,   340,   349,   326,   161,   269,   312,
     242,   -58,   -57,   346,   -41,   -25,   -58,   307,   313,   360,
     -29,   -27,   -23,   -58,   246,   -31
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      56,     1,    54,    41,    36,    37,    43,    44,   147,    69,
      43,    44,   148,    95,     9,    83,     8,    68,    15,    43,
      44,    10,    11,    56,    -1,    -1,    -1,    96,    38,    39,
      56,    45,   103,    88,    88,    62,    40,    -1,    89,   105,
      88,    36,    37,   108,    64,   107,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    21,
     131,    84,   140,     4,     5,    38,    39,   130,    69,   132,
     133,   134,    56,    40,   136,    22,    96,    36,    37,   141,
      26,   143,    27,    70,    71,    72,   109,   110,    28,    29,
      75,    76,    77,    78,    79,    80,    81,    69,    31,    23,
      32,    38,    39,    34,   174,    69,    30,    29,    19,    40,
       4,     5,    70,    71,    72,    35,   181,   160,   183,   162,
      70,    71,    72,   110,    80,    81,    61,    66,    56,    67,
      56,   180,    -1,    81,    57,    58,    56,    56,   177,   178,
     176,    56,    56,    66,    56,    96,    56,    56,    43,    44,
      96,    96,    69,    90,    56,   101,   192,    57,    58,   137,
     138,    56,   139,   138,    91,    96,    69,    70,    71,    72,
      73,    74,    97,    92,    75,    76,    77,    78,    79,    80,
      81,    70,    71,    72,    73,    74,   150,    69,    75,    76,
      77,    78,    79,    80,    81,    63,    65,    93,    98,   104,
     152,    69,    70,    71,    72,    73,    74,   106,   127,    75,
      76,    77,    78,    79,    80,    81,    70,    71,    72,    73,
      74,   153,    69,    75,    76,    77,    78,    79,    80,    81,
     128,   135,    49,    82,    32,   142,   146,    70,    71,    72,
      73,    74,    69,   144,    75,    76,    77,    78,    79,    80,
      81,    -1,   151,   155,   145,   157,   159,    70,    71,    72,
      73,    74,    69,   158,    75,    76,    77,    78,    79,    80,
      81,   161,   163,   165,   184,   166,   168,    70,    71,    72,
      73,    74,    69,   167,    75,    76,    77,    78,    79,    80,
      81,   154,   169,   179,   173,   175,   188,    70,    71,    72,
      73,    74,    69,   182,    75,    76,    77,    78,    79,    80,
      81,   156,   189,   190,   191,   193,    69,    70,    71,    72,
      73,    74,   194,   198,    75,    76,    77,    78,    79,    80,
      81,    70,    71,    72,    73,    69,   195,   196,    75,    76,
      77,    78,    79,    80,    81,    49,    20,    50,    51,    52,
      70,    71,    72,    53,    18,    48,    87,   129,    24,    77,
      78,    79,    80,    81,    94,    49,   102,    50,    51,    52,
     149,   100,    25,    53,    49,   187,    50,    51,    52,     0,
     185,   186,    53,    49,     0,    50,    51,    52,     0,     0,
     197,    53,    49,   164,    50,    51,    52,     0,     0,     0,
      53
};

static const yytype_int16 yycheck[] =
{
      31,    20,    31,    26,     3,     4,    23,    24,    44,    14,
      23,    24,    48,    54,    16,     3,     0,    40,     3,    23,
      24,    23,    24,    54,    29,    30,    31,    54,    27,    28,
      61,    48,    61,    43,    43,    48,    35,    42,    48,    48,
      43,     3,     4,    66,    48,    48,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    50,
      91,    49,   103,    23,    24,    27,    28,    90,    14,    92,
      93,    94,   103,    35,    97,     3,   103,     3,     4,   104,
      45,   106,    47,    29,    30,    31,    48,    49,    43,    44,
      36,    37,    38,    39,    40,    41,    42,    14,    18,     3,
      20,    27,    28,    47,   161,    14,    43,    44,    21,    35,
      23,    24,    29,    30,    31,    47,   173,   142,   175,   144,
      29,    30,    31,    49,    41,    42,    18,    45,   159,    47,
     161,   172,    41,    42,    23,    24,   167,   168,   167,   168,
     163,   172,   173,    45,   175,   172,   177,   178,    23,    24,
     177,   178,    14,    47,   185,    21,   185,    23,    24,    43,
      44,   192,    43,    44,    47,   192,    14,    29,    30,    31,
      32,    33,    52,    47,    36,    37,    38,    39,    40,    41,
      42,    29,    30,    31,    32,    33,    48,    14,    36,    37,
      38,    39,    40,    41,    42,    34,    35,    47,     3,    50,
      48,    14,    29,    30,    31,    32,    33,    50,     3,    36,
      37,    38,    39,    40,    41,    42,    29,    30,    31,    32,
      33,    48,    14,    36,    37,    38,    39,    40,    41,    42,
      44,    19,     3,    46,    20,    50,     3,    29,    30,    31,
      32,    33,    14,    50,    36,    37,    38,    39,    40,    41,
      42,    14,    48,    51,    46,     3,    18,    29,    30,    31,
      32,    33,    14,    19,    36,    37,    38,    39,    40,    41,
      42,    18,    45,    43,    46,    43,    12,    29,    30,    31,
      32,    33,    14,     8,    36,    37,    38,    39,    40,    41,
      42,    43,    51,    19,    18,    18,    51,    29,    30,    31,
      32,    33,    14,    19,    36,    37,    38,    39,    40,    41,
      42,    43,    19,    51,    19,    43,    14,    29,    30,    31,
      32,    33,    43,    43,    36,    37,    38,    39,    40,    41,
      42,    29,    30,    31,    32,    14,    51,    51,    36,    37,
      38,    39,    40,    41,    42,     3,     6,     5,     6,     7,
      29,    30,    31,    11,     5,    29,    44,    88,    12,    38,
      39,    40,    41,    42,    22,     3,    59,     5,     6,     7,
     128,    58,    12,    11,     3,    13,     5,     6,     7,    -1,
       9,    10,    11,     3,    -1,     5,     6,     7,    -1,    -1,
      10,    11,     3,   147,     5,     6,     7,    -1,    -1,    -1,
      11
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    20,    54,    55,    23,    24,    56,    57,     0,    16,
      23,    24,    64,    66,    72,     3,    58,    59,    58,    21,
      57,    50,     3,     3,    66,    72,    45,    47,    43,    44,
      43,    18,    20,    68,    47,    47,     3,     4,    27,    28,
      35,    75,    78,    23,    24,    48,    60,    61,    59,     3,
       5,     6,     7,    11,    73,    74,    78,    23,    24,    69,
      70,    18,    48,    60,    48,    60,    45,    47,    75,    14,
      29,    30,    31,    32,    33,    36,    37,    38,    39,    40,
      41,    42,    46,     3,    49,    62,    63,    62,    43,    48,
      47,    47,    47,    47,    22,    67,    74,    52,     3,    71,
      71,    21,    70,    73,    50,    48,    50,    48,    75,    48,
      49,    75,    76,    77,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,     3,    44,    61,
      75,    78,    75,    75,    75,    19,    75,    43,    44,    43,
      67,    68,    50,    68,    50,    46,     3,    44,    48,    63,
      48,    48,    48,    48,    43,    51,    43,     3,    19,    18,
      68,    18,    68,    45,    77,    43,    43,     8,    12,    51,
      65,    67,    73,    18,    65,    18,    75,    73,    73,    19,
      67,    65,    19,    65,    46,     9,    10,    13,    51,    19,
      51,    19,    73,    43,    43,    51,    51,    10,    43
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
#line 210 "6.y"
    {	(yyval.ptr) = (yyvsp[(3) - (3)].ptr);
											main_init((yyvsp[(3) - (3)].ptr));
											printf("Exit");
											exit(1);
									
								}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 216 "6.y"
    {		(yyval.ptr) = (yyvsp[(2) - (2)].ptr);
									main_init((yyvsp[(2) - (2)].ptr));
									printf("Exit");
									exit(1);
								}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 222 "6.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);fp= fopen("outfile.txt","w+");print_table();}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 224 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),_GDefList,0,DUMMY);}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 225 "6.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 227 "6.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr); evalDecl(HEAD,(yyvsp[(2) - (3)].ptr),0,DUMMY); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 228 "6.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr); evalDecl(HEAD,(yyvsp[(2) - (3)].ptr),1,DUMMY); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 230 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),_GIdList,0,DUMMY);}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 231 "6.y"
    {(yyval.ptr)=makenode(NULL,(yyvsp[(1) - (1)].ptr),_GIdList,0,DUMMY);}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 233 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,ID,0,(yyvsp[(1) - (1)].id));}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 234 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (4)].ptr),NULL,ARRAY,0,(yyvsp[(1) - (4)].id));
							/*MOD : make "expr" integer in grammar*/}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 236 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(3) - (4)].ptr),NULL,FUNC,0,(yyvsp[(1) - (4)].id));	flush_local();}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 237 "6.y"
    {(yyval.ptr) = makenode(NULL,NULL,FUNC,0,(yyvsp[(1) - (3)].id));}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 239 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),_ArgList,0,"_ArgList");/*when func is called called*/install_args_to_locals(-1,(yyval.ptr));}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 240 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(1) - (1)].ptr),NULL,_ArgList,0,"_ArgList");install_args_to_locals(-1,(yyvsp[(1) - (1)].ptr));}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 242 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(2) - (2)].ptr),NULL,GINT,0,"arg");}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 243 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(2) - (2)].ptr),NULL,GBOOL,0,"arg");}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 245 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),_List,0,"list");}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 246 "6.y"
    {(yyval.ptr) = makenode(NULL,(yyvsp[(1) - (1)].ptr),_List,0,"list");}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 248 "6.y"
    {(yyval.ptr) = makenode(NULL,NULL,ID,0,(yyvsp[(1) - (1)].id));}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 249 "6.y"
    {(yyval.ptr) = makenode(NULL,NULL,_pointer,0,(yyvsp[(2) - (2)].id));/*new change*/}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 251 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),_Fdeflist,0,"Fdeflist");}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 252 "6.y"
    {(yyval.ptr) = makenode(NULL,(yyvsp[(1) - (1)].ptr),_Fdeflist,0,"Fdeflist");}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 254 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),_body,0,"Body");}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 255 "6.y"
    {(yyval.ptr) = makenode(NULL,(yyvsp[(1) - (1)].ptr),_body,0,"Body");}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 258 "6.y"
    {	/*MOD : Fdef  <-- stmtlist     (improves tree)*/
								//flush_local();
								ret_check(0,(yyvsp[(9) - (11)].ptr)->right);
								
								int t = func_check1(0,(yyvsp[(2) - (11)].id),(yyvsp[(4) - (11)].ptr));
								if(t !=-1  ) {getline();TypeFlag=0;}

								struct gnode * temp = fetch(head,(yyvsp[(2) - (11)].id));
								temp->flabel = Label; Label++;
								
								(yyval.ptr) = makenode((yyvsp[(9) - (11)].ptr),makenode((yyvsp[(4) - (11)].ptr),(yyvsp[(7) - (11)].ptr),_junc,0,DUMMY),_Fdef,temp->flabel,(yyvsp[(2) - (11)].id));	//NEW : right child
								func_code_gen(0,(yyval.ptr));
								flush_local();
							}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 274 "6.y"
    {	
								//flush_local();
								ret_check(1,(yyvsp[(9) - (11)].ptr)->right);

								int t = func_check1(1,(yyvsp[(2) - (11)].id),(yyvsp[(4) - (11)].ptr));
								if(t !=-1  ) {getline();TypeFlag=0;}

								struct gnode * temp = fetch(head,(yyvsp[(2) - (11)].id));
								temp->flabel = Label; Label++;

								(yyval.ptr) = makenode((yyvsp[(9) - (11)].ptr),makenode((yyvsp[(4) - (11)].ptr),(yyvsp[(7) - (11)].ptr),_junc,1,DUMMY),_Fdef,temp->flabel,(yyvsp[(2) - (11)].id));	//NEW : right child
								func_code_gen(1,(yyval.ptr));

								flush_local();
							}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 291 "6.y"
    {
	 							//flush_local();
	 							ret_check(0,(yyvsp[(8) - (10)].ptr)->right);

	 							int t = func_check1(0,(yyvsp[(2) - (10)].id),NULL); 
								if(t !=-1  ) {getline();TypeFlag=0;}

	 							struct gnode * temp = fetch(head,(yyvsp[(2) - (10)].id));
								temp->flabel = Label; Label++;

	 							(yyval.ptr) = makenode((yyvsp[(8) - (10)].ptr),makenode(NULL,(yyvsp[(6) - (10)].ptr),_junc,1,DUMMY),_Fdef,temp->flabel,(yyvsp[(2) - (10)].id));	//NEW : right child
	 							
	 							func_code_gen(0,(yyval.ptr));

								flush_local();

	 						}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 310 "6.y"
    {
	 							//flush_local();
	 							ret_check(1,(yyvsp[(8) - (10)].ptr)->right);

	 							int t = func_check1(1,(yyvsp[(2) - (10)].id),NULL);		
								if(t !=-1  ) {getline();TypeFlag=0;}

	 							struct gnode * temp = fetch(head,(yyvsp[(2) - (10)].id));
								temp->flabel = Label; Label++;

	 							(yyval.ptr) = makenode((yyvsp[(8) - (10)].ptr),makenode(NULL,(yyvsp[(6) - (10)].ptr),_junc,1,DUMMY),_Fdef,temp->flabel,(yyvsp[(2) - (10)].id));	//NEW : right child
	 							
	 							func_code_gen(1,(yyval.ptr));

								flush_local();
							}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 328 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(2) - (3)].ptr),NULL,RET,0,DUMMY);}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 331 "6.y"
    {(yyval.ptr) = (yyvsp[(2) - (3)].ptr);evalDecl(L_HEAD,(yyvsp[(2) - (3)].ptr),0,DUMMY);}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 333 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),_LDefList,0,"LDefList");}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 334 "6.y"
    {(yyval.ptr) = makenode(NULL,(yyvsp[(1) - (1)].ptr),_LDefList,0,"LDefList");}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 337 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(2) - (3)].ptr),NULL,GINT,0,"Gint");/*flush_local();/*evalDecl(L_HEAD,$2,0,DUMMY);*/}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 338 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(2) - (3)].ptr),NULL,GBOOL,0,"Gbool");/*flush_local();/*evalDecl(L_HEAD,$2,0,DUMMY);*/}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 341 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(1) - (3)].ptr),makenode(NULL,NULL,ID,0,(yyvsp[(3) - (3)].id)),_LIdList,0,DUMMY);}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 342 "6.y"
    {(yyval.ptr) = makenode(NULL,makenode(NULL,NULL,ID,0,(yyvsp[(1) - (1)].id)),_LIdList,0,DUMMY);}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 345 "6.y"
    {(yyval.ptr) = (yyvsp[(5) - (8)].ptr);//BP = LocNo -1; SP = BP;
																	flush_local();ret_check(0,(yyvsp[(6) - (8)].ptr));
																	local_bind_count_init();
																	bind_locals_to_mem(-1,(yyvsp[(3) - (8)].ptr));			//generate local_table for main
																	printf("\nMAIN LOCAL TABLE \n");
																	print_locals();
																	alloc_mem_for_func_locals((yyval.ptr));
																	}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 353 "6.y"
    {(yyval.ptr) = (yyvsp[(4) - (7)].ptr);
													flush_local();ret_check(0,(yyvsp[(5) - (7)].ptr));
													local_bind_count_init();
													//bind_locals_to_mem(-1,$3);
													printf("\nMAIN LOCAL TABLE \n");
													print_locals();
													alloc_mem_for_func_locals((yyval.ptr));
													//local_head is null
													}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 365 "6.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 366 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),_StmtList,0,DUMMY);}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 371 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (5)].ptr),NULL,WRITE,0,"Write"); type_check2((yyval.ptr));}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 374 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (5)].ptr),NULL,READ,0,"Read"); type_check2((yyval.ptr));}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 377 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),IF,0,"If");     type_check2((yyval.ptr));}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 380 "6.y"
    { (yyval.ptr)=makenode((yyvsp[(3) - (10)].ptr),makenode((yyvsp[(6) - (10)].ptr),(yyvsp[(8) - (10)].ptr),ELSE,0,"Else"),IF,0,"If");  type_check2((yyval.ptr));}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 384 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),WHILE,0,"While"); type_check2((yyval.ptr));}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 387 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),'=',0,"=");	type_check2((yyval.ptr));}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 393 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'<',0,DUMMY); err_arg(1,(yyval.ptr));}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 394 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'>',0,DUMMY); err_arg(1,(yyval.ptr));}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 395 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),GE,0,DUMMY);	 err_arg(1,(yyval.ptr));}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 396 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),LE,0,DUMMY);	 err_arg(1,(yyval.ptr));}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 397 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NE,0,DUMMY);	 err_arg(1,(yyval.ptr));}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 398 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),EQEQ,0,DUMMY);err_arg(1,(yyval.ptr));}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 399 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(2) - (2)].ptr),NULL,NOT,0,DUMMY);err_arg(1,(yyval.ptr));}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 400 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),AND,0,DUMMY); err_arg(1,(yyval.ptr));}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 401 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),OR,0,DUMMY);	 err_arg(1,(yyval.ptr));}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 403 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,_Truth,TRUE,DUMMY);}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 404 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,_Truth,FALSE,DUMMY);}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 406 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'+',0,DUMMY); err_arg(0,(yyval.ptr));}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 407 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'-',0,DUMMY); err_arg(0,(yyval.ptr));}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 408 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'*',0,DUMMY); err_arg(0,(yyval.ptr));}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 409 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),'/',0,DUMMY); err_arg(0,(yyval.ptr));}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 410 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),_mod,0,DUMMY);err_arg(0,(yyval.ptr));}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 411 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,INT,(yyvsp[(1) - (1)].val),DUMMY);}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 412 "6.y"
    {(yyval.ptr) = (yyvsp[(1) - (1)].ptr);}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 413 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(3) - (4)].ptr),NULL,FUNC,0,(yyvsp[(1) - (4)].id));}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 414 "6.y"
    {(yyval.ptr) = makenode(NULL,NULL,FUNC,0,(yyvsp[(1) - (3)].id));}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 417 "6.y"
    {(yyval.ptr) =makenode((yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),_ExpList,0,"ExpList");}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 418 "6.y"
    {(yyval.ptr) =makenode(NULL,(yyvsp[(1) - (1)].ptr),_ExpList,0,"ExpList");}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 421 "6.y"
    {(yyval.ptr) = (yyvsp[(1) - (1)].ptr);}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 422 "6.y"
    {(yyval.ptr) = makenode(NULL,NULL,_pointer,0,(yyvsp[(2) - (2)].id));/*new change*/}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 423 "6.y"
    {(yyval.ptr) = makenode((yyvsp[(4) - (5)].ptr),NULL,_pointer,0,(yyvsp[(2) - (5)].id));}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 426 "6.y"
    {(yyval.ptr)=makenode(NULL,NULL,ID,0,(yyvsp[(1) - (1)].id));}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 427 "6.y"
    {(yyval.ptr)=makenode((yyvsp[(3) - (4)].ptr),NULL,ARRAY,0,(yyvsp[(1) - (4)].id));}
    break;



/* Line 1455 of yacc.c  */
#line 2353 "y.tab.c"
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
#line 430 "6.y"


//=========================================================================================================

//====================================================================================



//temp1 is global node pointer associated with checkargs func only
struct gnode * temp1;
//checks for arguments of func in func definitions 
//----------  not declarations in global symbol table 
int check_args(struct node *nd,int i){
	
	if(nd == NULL ) return  1;
	switch(nd->flag){

		case _ArgList : {int t= check_args(nd->right,i) ;int u= check_args(nd->left,i); return t&&u;}
		case GINT : {int t = check_args(nd->left,0); return t;}
		case GBOOL: {int t = check_args(nd->left,1);return  t;}

		case _List : {int t1 = 0;//strcmp(nd->right->varname,temp1->name);

						if(t1!=0 || (temp1->type != i && temp1->type -5 != i)) {
							printf("mismatch in arguments of func (%s %d - %s %d)\n",temp1->name,temp1->type,nd->right->varname,i);
							return 0;
						}
						if(temp1->next) temp1 = temp1->next;
						int t= check_args(nd->left,i); return t;
					}
	}

}

int func_check1(int return_type,char *name,struct node *nd){

	//printf("Asked for checking func %s and arg at %d\n",name,nd->flag);
	struct gnode *temp;
	temp = fetch(head,name);

	int flag =1; //init every thing's okay 

	//if func not present
	if(!temp){ getline();printf("undeclared function defined");flag =0;exit(1);}

	//else
	//check return type of func
	//printf("%d && %d\n",temp->type,return_type);
	if(temp->type-3 != return_type) {getline();printf("return type error\n");flag =0;exit(1);/*error(6)*/}


	//temp1 is global node pointer associated with checkargs func only
	temp1 = temp->args;

	//function name and return type  are okay
	//check the arguments

	int t  = check_args(nd , -1);
	if( t == 0 || flag!=1) return -2;

	else return -1; //good
}


//NOTE : ADD func local table at codegen part 

//========================================================================================================
//helper for list_checker
int getType(struct node * nd){
	switch(nd->flag){
		case _pointer : 
		case ID : 	{
						struct gnode * temp = fetch(local_head,nd->varname);
						if(temp == NULL) temp = fetch(head,nd->varname);
						if(temp == NULL) {getline();printf("Undeclared var\n");exit(1);}
						int typ = temp->type;
						if(temp->type ==5 || temp->type ==6) typ = typ -5;
						return typ;
					}
		case ARRAY : {
						struct gnode * temp = fetch(head,nd->varname);
						if(temp == NULL) {getline();printf("Undeclared array\n");exit(1);}
						return temp->type; 
					}	
		case '<' :case '>' :case GE :case LE :case NE :case EQEQ:case NOT :
		case AND :case OR :case _Truth :	return 1;
		
		case '+':case '-':case '%':case '*':case INT : case '/':	return 0;
		
		case FUNC : {struct gnode * temp = fetch(head,nd->varname);if(temp) return temp->type-3;}
		//this is cause : func args cannot have funcs
	}
}

//temp2 is global node pointer associated with list_checker func only
struct gnode * temp2;
//helpewr function for func_check2
int list_checker(struct node * nd){
	if (nd == NULL) return -1;
	if(nd->right){
		int t1 = 0;//strcmp(nd->right->varname,temp2->name);
		//or coulg only check  the type
		int typ = getType(nd->right);
		//printf("name : %d at %s\n",nd->flag, nd->right->varname);
		//printf("typo is here %d expected %d\n",typ,temp2->type );
		if(t1!=0 || (temp2->type != typ && temp2->type -5 !=typ )) {
			getline();
			printf("mismatch in arguments of func (%s %d - %s %d)\n",temp1->name,temp2->type,nd->right->varname,typ);
			exit(1);
		}
		if(temp2->next) temp2 = temp2->next;		
		int t= list_checker(nd->left); 		
		return t;
	}
	else printf("something smells\n");
}


//function  In expressions
int func_check2(struct node * nd){

	struct gnode *temp;
	temp = fetch(head,nd->varname);

	if(!temp) {getline();printf("undeclared function used\n");exit(1);/*error(7);*/}
	else if(temp->args != NULL && nd->left == NULL) {getline();printf("Arguments mismatch\n");exit(1);}
	else if(temp->args == NULL && nd->left != NULL) {getline();printf("Arguments mismatch\n");exit(1);}
	else if(temp->args == NULL && nd->left == NULL) return temp->type-3;
	//main part
	//temp2 is global node pointer associated with list_checker func only
	if(temp->args != NULL && nd->left != NULL){
		temp2 = temp->args;		
		list_checker(nd->left);
	}
	return temp->type-3;
}
//=============================================================================================

void ret_check(int i,struct node * nd){
	int t = type_check2(nd->left);
	if(t != i ) {getline();printf("return type error\n");exit(1);/*error(6)*/}
	return ;
}
//==========================================================================================

//version 2   typecheck need to be improved
//returns : -1 okay ,-2 not ok , type of the var(0,1)
//1 for bool ;  0 for int int 
int type_check2(struct node * nd ){ // -1 is good sign , -2 is bad
	if(nd== NULL) {return -1;}

	switch(nd->flag){

		case WRITE:	{int l = type_check2(nd->left);if (l == 0 ) return -1;error(3);}
		case READ : {int l = type_check2(nd->left);return -1;error(4);}
		case '='  :	{int l = type_check2(nd->left); int r = type_check2(nd->right);if(l==r) return -1;error(5);}
		case WHILE: {int l = type_check2(nd->left); if (l == 1) return -1;error(4);}
		case IF   :	{int l = type_check2(nd->left);if(l==1) return -1;error(4);}
		
		case '<'  : case '>'  : case EQEQ :case NE   :case LE   :case GE   : 
		{int l = type_check2(nd->left);int r = type_check2(nd->right);if(l==0 && r==0) return 1;error(3);}

		case '+'  : case '-'  : case '*'  :case _mod :case '/'  : 
		{int l = type_check2(nd->left); int r = type_check2(nd->right);
						if(l==0 && r==0) return 0;error(3);}
		case INT  : return 0;
		
		case ARRAY : case ID  : 
		{/*ADD : arr[exp] checker for exp not to be bool*/
			if(nd->left){
				//printf("HERE \n");
				int t = type_check2(nd->left);
				if(t != 0) {getline();printf("Error at array exp\n");exit(1);}
			}
			struct gnode * temp; temp = fetch(local_head,nd->varname);//printf("%d\n",temp); 
					//if (temp == NULL) temp = fetch_args(func,nd->varname);
					if(temp == NULL) temp = fetch(head,nd->varname);
					if(temp == NULL) {getline();printf("no such var detected\n");exit(1);}
					int m = temp->type ;
					if(m == 5 || m == 6) m = m-5; 
					  return m;		
		}	
		case _Truth: {if(nd->val == TRUE || nd->val == 	FALSE) return 1;error(4);}

		case AND :case OR  :case NOT : 
		{int l = type_check2(nd->left);int r=1; if(nd->right){ r = type_check2(nd->right);} 
					if(l==1 && r ==1) return 1; error(4);}

		case FUNC : {return func_check2(nd);/*func check in statements like [ a= foo(); ]*/}
		
	}

}

void err_arg(int flag,struct node * nd){
	if(type_check2(nd)!=flag ){
		getline();
		printf("Error in exp in arguments\n");
		exit(1);
	}
	return;
}
//CODE GENERATION PART=================================================================



//--------------------------------------------

//Episode : INSTALL

//=============================================
void flush_local(){
	//free memoey of past local_head
	/*
	if(local_head && local_head->next){
		struct gnode * delnode = local_head->next;	//safe to do like this -- good prctice
		struct gnode * helper;
		
		while(delnode){
			helper = delnode ;
			delnode = delnode->next;

			//free(helper->name); 					//so we can free only pointers
			//free(helper->size);
			//free(helper->bind);
			free(helper->next);
			free(helper->args);
			
		}
	}
	else if(local_head && local_head->next== NULL){
		free(local_head->next);
		free(local_head->args);
	}
	*/
	local_head = NULL;
	//return;
}

//INITIALIZERS-----------------------------------------------------------------
void local_bind_count_init(){
	agcount = 1;
	return;
}
int get_local_bind_count(){
	agcount+=1;
	return agcount-1;
}

//[BP - 3] for arguments in run stack
int nastyCount=-3;	//warning : initialize everytime to -3 do nort forget stupid

void arg_bind_count_init(){
	nastyCount = -3;
}

int get_arg_bind_count(){	//sophistication can be addded by increasing param
	nastyCount-=1;
	return nastyCount+1;
}
//-------------------------------------------------------------------------------

void foo(int i, char * _name){
	struct gnode * temp;
	temp = (struct gnode *) malloc(sizeof(struct gnode)) ;
	temp->name = _name;
	temp->type = i;
	temp->bind = get_arg_bind_count();
	//nastyCount--;
	temp->args = NULL;

	temp->next = local_head;
	local_head = temp;


}


void install_args_to_locals(int i,struct node * nd){
	if (nd == NULL) return;
	//printf("sam is hwrw\n");
	switch(nd->flag){
		case _ArgList:{install_args_to_locals(i,nd->left);install_args_to_locals(i,nd->right);break;}
		case GINT :   {install_args_to_locals(0,nd->left);break;}
		case GBOOL:   {install_args_to_locals(1,nd->left);break;}
		case _List :  {install_args_to_locals(i,nd->left);
						if(nd->right->flag == _pointer) i = i+POINT;
						//printf("I like iceceram %d \n",i);
						foo(i,nd->right->varname);break;}
	}
	return;
}

// i rep's type : important logic for pointers
//this func is for tye checking of a function
void install_local_var(struct node *nd,int i){

	struct gnode * t = fetch(local_head , nd->varname);
	if (t != NULL) {getline();printf("redeclared var in local \n");exit(1);}
 
	struct gnode * temp;
	temp = (struct gnode *) malloc(sizeof(struct gnode ));

	//NEED to change the BIND here
	temp->name = nd->varname;
	temp->type = i;
	temp->args = NULL;
	//initial binding of locals 
	temp->bind = -100;

	//install locals in local table
	temp->next = local_head;
	local_head = temp;

}


//at global sym table func declarations

//	t  : func_arg_head 		count for numbering args 	i is return type

void install_args_to_func_in_global(struct gnode *t,struct node *nd,int i,int count){ 
	if(nd == NULL) return;
	switch(nd->flag){
		case _ArgList: {install_args_to_func_in_global(t,nd->left,i,count);install_args_to_func_in_global(t,nd->right,i,count);break;}
		case GINT : {install_args_to_func_in_global(t,nd->left,0,count);break;}
		case GBOOL: {install_args_to_func_in_global(t,nd->left,1,count);break;}
		case _List :{install_args_to_func_in_global(t,nd->left,i,count+1);
						struct gnode *temp;


						temp = (struct gnode *)malloc(sizeof(struct gnode ));
						temp->name = nd->right->varname;
						//printf("sai %d\n",nd->right->flag);
						//NOTICE for pointer: type = 5,6 for int ,bool pointers
						if(nd->right->flag == _pointer) {i = i+POINT;}
						temp->type = i;
						temp->args = NULL;
						temp->bind = count;
						temp->next = t->args;
						t->args = temp;
						break;
					}
	}
	return;
}

//allcating space in memory of target machine
//suggestion : Add error msg for redeclarations;
//NOTE : I think func arg can be removed since local sym table is being crearted

//flag indicates whether to local_head or global
void evalDecl(int Flag,struct node *nd,int i,char * func){	// i for type filling in table
	if(nd == NULL ) {
		//for relative adddressing of local variable
		// initialisig after every time
		return;
	}
	switch(nd->flag){
		//case _GDefList: evalDecl(nd->left,i);evalDecl(nd->right,i); break;
		//case GINT: 		evalDecl(nd->left,0); break;
		//case GBOOL: 	evalDecl(nd->left,1); break;
		case _GIdList: 	evalDecl(Flag,nd->left,i,func);

						if(nd->right->flag==ID) {
							//printf("same %s\n",nd->right->varname);
							gentry(nd->right->varname,i,1,LocNo);//1 rep's size
							LocNo++;
						}
						else if(nd->right->flag == ARRAY){
							//printf("same %s\n",nd->right->varname);
							int size = nd->right->left->val;
							gentry(nd->right->varname,i,size,LocNo);
							LocNo += size;							

						}
						//pointer mark
						else if(nd->right->flag == FUNC ){
							//printf("same %s\n",nd->right->varname);
							struct gnode * temp;
							//gnode for function in global symbol table
							temp =(struct gnode *) malloc(sizeof(struct gnode));
							
							temp->name = nd->right->varname;
							int func_type;
							if(i==0) func_type=3;
							else if(i == 1) func_type=4;

							//printf("func name %s(%d)\n",nd->right->varname,);

							temp->type = func_type;
							temp->args = NULL;

							//head is here now use your head
							temp->next =head;
							head = temp;
							install_args_to_func_in_global(temp,nd->right->left,i,0);	
							//i means nothing but useful in "inst_args_func_glob"
							//nd->r->l : arg starts	

						}break;

		case _LDefList: evalDecl(Flag,nd->left,i,func);evalDecl(Flag,nd->right,i,func);break;
		case GINT 	: evalDecl(Flag,nd->left,0,func);break;
		case GBOOL	: evalDecl(Flag,nd->left,1,func);break;

		case _LIdList: 	evalDecl(Flag,nd->left,i,func);
						//struct gnode *temp ;
						//temp = fetch(head,func);
						//print_table();
						//printf("type : %d ,i = %d\n",temp->type,i);
						//if(!temp) {printf("Function undeclared\n");exit(1);}
						
						//if(temp->type-3 !=  i) {printf("function of different typecheck\n");exit(1);}
						install_local_var(nd->right,i);

						break;	
	}
}

//=======================================----------------------------------======

//code gen helpers=============================================================
void printRegStack(){	//needn't touch
	return;
	regCallCount++;

	printf("( %d )regStack : ",regCallCount);
	int i;
	for( i=0;i<8;i++){
		if(regStack[i]==-1 ) break;
		printf("%d ",regStack[i]);
	}
	printf("\n");

}

void freeReg(int r,struct node * nd){	
//if reg r at top of reg stack the remove else return error
	//if(r==0) {printRegStack();return;}
	if(r < 	0) {getline();printf("cannot free get whe all are free \n");exit(1);}
	if (RegNo < 0) {getline(); printf("attempt to free reg at -1\n");exit(1);}
	if(r==RegNo)
	{	RegNo--;regStack[RegNo+1]=-1;
		printRegStack();}
	else{
		printf("%d cannot happen reg(%d) - %d",lineno,r,RegNo);
		if(nd) printf("at %d\n",nd->flag);
		if(nd->left) printf(": l(%d)  ",nd->left->flag);
		if(nd->right) printf(": r(%d) ",nd->right->flag);printf("\n");
	}
}	

//allocates a new register by increasing a global count
int getReg(){
	RegNo++;
	if(RegNo >7) {
		getline();
		printf("Exeeded register usage\n");
		exit(1);
	}
	regStack[RegNo] =RegNo;
	printRegStack(); 
	int r = RegNo;
	return r;
}

//gets loc of a var in a reg
int getLoc(char * varname){	

	struct gnode * temp;
	temp = fetch(local_head,varname);
	if(temp) {
		int loc = temp->bind;							//fetch in local
		int r1 = getReg();
		int r2 = getReg();
		fprintf(fp,"MOV R%d,BP\n",r1);
		fprintf(fp,"MOV R%d,%d\n",r2,loc);			
		fprintf(fp,"ADD R%d,R%d\n",r1,r2);
		freeReg(r2,NULL);
		return r1;
	}
	
	else temp = fetch(head,varname);					//fetch in  global tab

	if(temp){
		int loc = temp->bind;
		int r = getReg();
		fprintf(fp, "MOV R%d,%d\n",r,loc);
		return r;
	}
	if(temp == NULL) {getline();printf("Local symbol table -- biscuit\n");exit(1);}
	//printf("saikumar");
}


int isLocGlobal(int i){
	if(i>=200000) return 1;
	else return 0;
}

//returns (array base addr + location num in expr) in a reg
int getLocArray(struct node * nd){
	
	int r = CodeGen(nd->left);
	int r1 = getLoc(nd->varname);
	int foo = fprintf(fp,"ADD R%d,R%d\n",r,r1);	//add r + r1	
	freeReg(r1 , nd);
	return r; //contains final location of array element
}

//func used in codegen() 
int op(struct node* nd , int flag){

	int r1 = CodeGen(nd->left);	//increment for r1 will be done in rec part			
	int r2 = CodeGen(nd->right);

	switch(flag){
		case 1:{int foo =  fprintf(fp,"ADD R%d,R%d\n",r1,r2);break;}
		case 2:{int foo =  fprintf(fp,"SUB R%d,R%d\n",r1,r2);break;}
		case 3:{int foo =  fprintf(fp,"MUL R%d,R%d\n",r1,r2);break;}
		case 4:{int foo =  fprintf(fp,"DIV R%d,R%d\n",r1,r2);break;}

		case 5:{int foo =  fprintf(fp,"LT R%d,R%d\n",r1,r2);break;}
		case 6:{int foo =  fprintf(fp,"GT R%d,R%d\n",r1,r2);break;}
		case 7:{int foo =  fprintf(fp,"EQ R%d,R%d\n",r1,r2);break;}
		case 8:{int foo =  fprintf(fp,"LE R%d,R%d\n",r1,r2);break;}
		case 9:{int foo =  fprintf(fp,"GE R%d,R%d\n",r1,r2);break;}
		case 10:{int foo =  fprintf(fp,"NE R%d,R%d\n",r1,r2);break;}
		case 11:{int foo =  fprintf(fp,"MOD R%d,R%d\n",r1,r2);break;}
	}

	freeReg(r2 , nd);

	return r1;
}

//CODEGEN===============================================================
//generates machine code for SIM
//returns regno to be used at an instance


void foo2(int i, char * _name,int _bind){
	struct gnode * temp;
	temp = (struct gnode *) malloc(sizeof(struct gnode)) ;
	temp->name = _name;
	temp->type = i;
	temp->args = NULL;
	temp->bind = _bind;

	temp->next = local_head;
	local_head = temp;
}

//add locals to local table and binds them to mem relative to bp
void bind_locals_to_mem(int i,struct node * nd){
	int bind;
	if (nd == NULL) return;
	switch(nd->flag){
		case _LDefList : {bind_locals_to_mem(i,nd->left);bind_locals_to_mem(i,nd->right);break;}
		case GINT : {bind_locals_to_mem(0,nd->left);break;}
		case GBOOL: {bind_locals_to_mem(1,nd->left);break;}
		case _LIdList : {
							bind_locals_to_mem(i,nd->left);
							struct gnode * temp = fetch(local_head,nd->right->varname);
							if(temp == NULL)
							bind = get_local_bind_count();

							foo2(i,nd->right->varname,bind);	//main part
							break;
						}
	}
	return ;
}
//_____________________________________________
//helper to func_code_gen
void alloc_mem_for_func_locals(struct node * nd){
	if(local_head){
		int m = local_head->bind; printf("val is impoertantianno %d\n", m);
		///*
		int r = getReg();
		fprintf(fp,"MOV R%d, 0\n",r);	//for init-ing all locals to 0
		print_locals();
		
		
		int  i=0;
		while(i<m){			//CHANGE : this can be writtren as increasing sp only
			fprintf(fp,"PUSH R%d\n",r);
			i=i+1;
		}
		
		freeReg(r,nd);
		//*/
		/*
		//  SP  =  SP  +  m ;
		int r = getReg();
		int r1 = getReg();
		fprintf(fp, "MOV R%d,%d\n",r,m);
		fprintf(fp, "MOV R%d,SP\n",r1);
		fprintf(fp, "ADD R%d,R%d\n",r,r1);
		fprintf(fp,"MOV SP,R%d\n",r);
		freeReg(r1,nd);
		freeReg(r,nd);
		*/

		printf("say hi to me now\n");
	}
}
//ADD : label to func  in gsymtab

void func_code_gen(int i,struct node * nd){
	if (nd == NULL) return ;
	switch(nd->flag){
		//case _Fdeflist : {func_code_gen(i,nd->left);func_code_gen(i,nd->right);break;}
		case _Fdef : {
						//make the local table then generate the code

						flush_local();
						printf("------Visting : %s\n",nd->varname);

						fprintf(fp,"L%d:\n",nd->val);
						//if(nd->flag != _main)
						fprintf(fp,"PUSH BP\n");
						fprintf(fp,"MOV BP,SP\n");
						local_bind_count_init();
						arg_bind_count_init();
						//agcount = 1;				//for local vars
						//nastyCount = -3;  		//for the sake of arguments -- do you get it?
						install_args_to_locals(-1,nd->right->left);
						bind_locals_to_mem(-1,nd->right->right);
						printf("safty check ");print_locals();
						//by looking the first (last entered var in local sym tab inc the sp i.e push a reg)
						alloc_mem_for_func_locals(nd);		//stack manip
						int r = CodeGen(nd->left);

						//freeReg(r,nd);
						flush_local();
						break;	
						}
	}
	return;
}

int getFuncLabel(char * name){
	struct gnode * temp = fetch(head, name);
	return temp->flabel;
}


int CodeGen(struct node *nd){
	if(nd==NULL) return -1;
	switch(nd->flag){
		case _body : {CodeGen(nd->left);CodeGen(nd->right);break;}

		case _Truth : 
					{ int value = 0 ; if(nd->val == TRUE) value =1;
					  
					  int r = getReg();
					  
					  int foo = fprintf(fp,"MOV R%d,%d\n",r,value);
					  
					  return r; 
					}
		case _pointer:{
						int r = get_pointer_addr(nd);
						return r;
					}
		case INT:	{int r = getReg();

					int foo = fprintf(fp,"MOV R%d,%d\n",r,nd->val);

					return r;

					break;} 

		//club ID and Array
		case ID :	{int r = getReg();
					
					int r1 = getLoc(nd->varname);

					int foo = fprintf(fp,"MOV R%d,[R%d]\n",r,r1);

					struct  gnode * temp  = fetch(local_head,nd->varname);

					if(temp->type == 5 || temp->type == 6){

						fprintf(fp,"MOV R%d,[R%d]\n",r,r);

					} 

					freeReg(r1,nd);
					
					return r;
					
					break;}

		case ARRAY :{int r = getReg();
					
					int r1 = getLocArray(nd);	// in a register

					int foo = fprintf(fp,"MOV R%d,[R%d]\n",r,r1);//mov r [r1] 	

					freeReg(r1 , nd);

					return r;
					
					break;}
		
		case _StmtList:{CodeGen(nd->left);CodeGen(nd->right);break;}

		case '+' :	{int reg = op(nd,1); return reg;break;}
		case '-' :	{int reg = op(nd,2); return reg;break;}
		case '*' :	{int reg = op(nd,3); return reg;break;}
		case '/' :	{int reg = op(nd,4); return reg;break;}
		case '<' :	{int reg = op(nd,5); return reg;break;}
		case '>' :	{int reg = op(nd,6); return reg;break;}
		case EQEQ :	{int reg = op(nd,7); return reg;break;}
		case  LE :	{int reg = op(nd,8); return reg;break;}
		case  GE :	{int reg = op(nd,9); return reg;break;}
		case  NE :	{int reg = op(nd,10); return reg;break;}
		case _mod :	{int reg = op(nd,11); return reg;break;}

		
		case '=' :	//one reg for returning remaining canbe disposed off
					{int r = CodeGen(nd->right);				//right part of =
					//fprintf(fp,"OUT R%d\n",r);
					//printf("good  ");printRegStack();
					if(nd->left->flag == ID){
						
						int r1 = getLoc(nd->left->varname);
						//printf("Bad %d\n",r1);

						

						struct gnode* temp  = fetch(local_head,nd->left->varname);

						if(temp->type == 5 || temp->type == 6){

							fprintf(fp,"MOV R%d,[R%d]\n",r1,r1);
							
						}

						fprintf(fp,"MOV [R%d], R%d\n",r1,r);

						freeReg(r1,nd);
						//fprintf(fp,"num = %d\n",r1);
						//fprintf(fp,"Error123\n");
						freeReg(r,nd);

						return -1;
					}

					else if(nd->left->flag == ARRAY){		//left part of =

						int r1 = getLocArray(nd->left);

						int foo =  fprintf(fp,"MOV [R%d],R%d\n",r1,r);

						freeReg(r1,nd);

						freeReg(r,nd);

						return -1;						

					}
					
					break;}

		

		case WRITE : //printing out of register
					{
						int  r = CodeGen(nd->left);

						//printf("sam is here\n");

						fprintf(fp,"OUT R%d\n",r);

						freeReg(r,nd);

						return -1;

						break;}

		case READ :	{//load to register then load to memorand

					int r =getReg();

					if(nd->left->flag == ID){

						int foo = fprintf(fp,"IN R%d\n",r);

						int r1 = getLoc(nd->left->varname);

						struct gnode* temp  = fetch(local_head,nd->left->varname);

						if(temp->type == 5 || temp->type == 6){

							fprintf(fp,"MOV R%d,[R%d]\n",r1,r1);
							
						}
						
						foo = fprintf(fp,"MOV [R%d],R%d\n",r1,r);

						freeReg(r1,nd);

						freeReg(r,nd);

						return -1;

					}
					else if(nd->left->flag == ARRAY) {

						int foo = fprintf(fp,"IN R%d\n",r);

						int r1 = getLocArray(nd->left);

						foo = fprintf(fp,"MOV [R%d],R%d\n",r1,r);

						freeReg(r1,nd);

						freeReg(r,nd);

						return -1;

					}

					break;}

		case IF:{
					int r  = CodeGen(nd->left);
					int l;	//reserved for else part
					int l1 = Label;
					Label++;
					int foo = fprintf(fp,"JZ R%d,L%d\n",r,l1);
					freeReg(r,nd);

					if(nd->right->flag == ELSE)	{
						foo = CodeGen(nd->right->left);
						l = Label;
						Label++;
						fprintf(fp, "JMP L%d\n",l);
					}

					else foo = CodeGen(nd->right);
					
					foo = fprintf(fp,"L%d: ",l1);

					if(nd->right->flag == ELSE)	{
						foo = CodeGen(nd->right->right);
						fprintf(fp, "L%d:\n",l );
					}

					

					return -1;
				}


		case AND :{
					int r1 = CodeGen(nd->left);

					int r2 = CodeGen(nd->right);
					
					int foo = fprintf(fp,"MUL R%d,R%d\n",r1,r2);

					freeReg(r2,nd);

					return r1;

					break;

					}

		case OR :{
					int r1 = CodeGen(nd->left);

					int r2 = CodeGen(nd->right);
					
					int r3 = getReg();

					int foo = fprintf(fp,"MOV R%d,R%d\n",r3,r1);

					foo = fprintf(fp,"ADD R%d,R%d\n",r1,r2);

					foo = fprintf(fp,"MUL R%d,R%d\n",r3,r2);

					foo = fprintf(fp,"SUB R%d,R%d\n",r1,r3);

					freeReg(r3,nd);

					freeReg(r2,nd);

					return r1;

					break;

					}

		case NOT :{
					int r = CodeGen(nd->left);

					int r1 = getReg();

					int foo = fprintf(fp,"MOV R%d,1\n",r1);

					foo = fprintf(fp,"LT R%d,R%d\n",r,r1);

					freeReg(r1,nd);

					return r;

					break;

					}

		case WHILE :{
						//fprintf(fp, "WHILE start------\n");
						int l1 = Label;
						Label++;

						int foo = fprintf(fp,"L%d:",l1);						

						int r = CodeGen(nd->left);
						
						int l2 = Label;
						Label++;
						foo = fprintf(fp,"JZ R%d,L%d\n",r,l2);

						freeReg(r,nd);

						foo= CodeGen(nd->right);

						foo = fprintf(fp,"JMP L%d\n",l1);

						foo = fprintf(fp,"L%d:",l2);

						//fprintf(fp, "WHILE end--------\n" );

						return -1;

						break;

					}

		case FUNC : {	//ADD : improve this point geta reg free it 
						//		 in this process you will get the max reg in use
						printf("Function call %s\n",nd->varname);
						int r = getReg();
						freeReg(r,nd);
						printf("last free reg : %d\n",r-1);
						int i = 0;
						while(i<r){ 
							fprintf(fp, "PUSH R%d\n",i );
							//freeReg(i,nd);
							i=i+1;
						}
						
						//ADD : FREE THE REGs
						
						push_list(nd->left);

						r = getReg();
						fprintf(fp, "PUSH R%d\n", r); //return add
						freeReg(r,nd);
						int lab = getFuncLabel(nd->varname);

						//CALL the function
						fprintf(fp,"CALL L%d\n",lab);

						r = getReg();
						fprintf(fp,"POP R%d\n",r);	//	r == return val i guess
						
						pop_list(nd->left);
						
						//something's fishy here : how to store return value
						/*
						i =0 ;
						while(i<r){
							int t = getReg();
							i = i+1;
						}
						*/
						i=r-1;
						while(i>=0){
							fprintf(fp,"POP R%d\n",i);
							i--;
						}
						return r;
					}

		case RET : {	

						int r = CodeGen(nd->left);
						int r1 = getReg();
						int  r2 = getReg();
						fprintf(fp,"MOV R%d,2\n",r2);
						fprintf(fp,"MOV R%d,BP\n",r1);
						fprintf(fp,"SUB R%d,R%d\n",r1,r2);
						fprintf(fp,"MOV [R%d],R%d\n",r1,r);
						//fprintf(fp, "MOV [BP - 2], R%d\n",r );
						freeReg(r2,nd);
						freeReg(r1,nd);
						freeReg(r,nd);
						fprintf(fp, "MOV SP,BP\n");
						fprintf(fp,"POP BP\n");
						fprintf(fp,"RET\n");
						printf("End of a function\n");
						return -1;
					}
	}
}

//first arg pushed last
void push_list(struct node * nd){

	if(nd == NULL) return;

	//this sequence is important and arg names must match exactly

	//pusing the value only (change the strat for pointers)
	int r = CodeGen(nd->right);

	fprintf(fp,"PUSH R%d\n",r);

	freeReg(r,nd->right);

	push_list(nd->left);

	return;
}

void pop_list(struct node * nd){
	if (nd == NULL) return;

	pop_list(nd->left);

	int r =getReg();

	fprintf(fp,"POP R%d\n",r);

	freeReg(r,nd->right);

	return ;
}

//Old code need not be looked at

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
