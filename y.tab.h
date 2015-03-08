
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 28 "6.y"

	int val;
	char* id;
	struct node *ptr;



/* Line 1676 of yacc.c  */
#line 124 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


