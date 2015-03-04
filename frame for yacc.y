%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	//#include "lex.yy.c"
	int n;
	#define DUMMY "sai"
	#define _INT 1
	#define	_IDENTIFIER 2
	#define _READ 3
	#define _WRITE 4
	#define _IF 5
	#define _THEN 6
	#define _WHILE 7
	#define _DO 8
	#define _EQEQ 9
	#define _INTD 10
	#include "table1.c"
	#include "tree1.c"
	struct node* t;
	/*
	Prog: GDefblock Fdeflist Mainblock
	GDefblock : DECL GDefList ENDDECL
	GDefList :
				| GDefList GDecl
	GDecl : Type GIdList ;
	GIdList : GIdList, GId
	GId : ID

		| ID ( ArgList)

		| ID [ CONST ]
	FdefList :

			| FdefList Fdef

	Fdef : Type ID ( Arglist ) { LDefblock Body }
	LDefblock :


	Mainblock : INTEGER MAIN '(' ')' '{'  Body '}'
		*/
	
%}


%union {
	int val;
	char* id;
	struct node *ptr;
}


%token <id>  ID
%token <val> READ
%token <val> WRITE
%token <val> IF
%token <val> THEN ENDIF
%token <val> WHILE DO ENDWHILE
%token <val> EQEQ
%token <val> INTD
%token <val> EXIT

%type <ptr> Mainblock
%type <ptr> Body
%type <ptr> StmtList
%type <ptr> Stmt
%type <ptr> relexp
%type <ptr> Expr
%type <ptr> Var
%type <ptr> Body

%left '+' '-'
%left '*' '/'
%nonassoc '<'
%nonassoc '>'
%nonassoc EQEQ


%%

Body :  StmtList EXIT 

StmtList: Stmt

	| StmtList Stmt

	;

Stmt : WRITE '(' Expr ')' ';'

	| READ '(' Var ')' ';'

	| IF '(' Expr ')' THEN StmtList ENDIF ';'

	| WHILE '(' relexp ')' DO StmtList ENDWHILE ';'

	| Var '=' Expr ';'

	;

Var : ID

	| ID '[' Expr ']'

	;

 
Expr:  Expr + Expr

	| Expr * Expr

	| ID '[' Expr ']'

	| ID

	| INT

	;

%%