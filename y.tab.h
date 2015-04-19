
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

/* Line 1676 of yacc.c  */
#line 163 "6.y"

	int val;
	char* id;
	struct node *ptr;



/* Line 1676 of yacc.c  */
#line 128 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


