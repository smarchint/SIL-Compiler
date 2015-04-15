%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	int lineno=1;
	int n,TypeFlag=1; 			//typeflag default to okay ie., every thing's fine
	//int BringTon = 200000;
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
	#include "table2.c"
	#include "tree2.c"
	#define getline() printf("Error at %d\n",lineno);
	

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
	void bind_func_locals(struct node * nd);
	void bind_locals(int i,struct node * nd);

%}


%union {
	int val;
	char* id;
	struct node *ptr;
}


%token <id>  ID


%token <val> INT
%token <val> WRITE 
%token <val> READ
%token <val> IF THEN ELSE ENDIF
%token <val> WHILE DO ENDWHILE
%token <val> EQEQ
%token <val> INTEGER
%token <val> MAIN EXIT
%token <val> SILBEGIN END
%token <val> DECL ENDDECL RET
%token <val> GBOOL GINT INTD BOOLD
%token <val> TRUE
%token <val> FALSE
%token <val> LE GE NE
%token <val> AND OR NOT



%type <ptr> Program  Mainblock
%type <ptr> StmtList  Stmt Expr
%type <ptr>  Var ArgList Arg List 
%type <ptr> FdefList Fdef Body ExpList
%type <ptr> LDefblock LDefList LDecl  LIdList retExp
%type <ptr> GDefblock GDefList GIdList GDecl GId


%left OR
%left AND 
%left '!'
%left '+' '-'
%left '*' '/' '%'
%nonassoc '<'
%nonassoc '>' LE NE GE
%nonassoc EQEQ 


%%

Program: GDefblock FdefList Mainblock	{	
									//print_table();
									if(TypeFlag==0) {printf("Exit status = failure\n");exit(0);}
									else{
										fp= fopen("outfile.txt","w+");
										
										print_table();
										func_code_gen(-1,$2);
										
										int foo = fprintf(fp,"START\n");
										fprintf(fp,"MOV BP, %d\n",LocNo-1);
										printf("Initial BP is at %d\n",LocNo-1);
										fprintf(fp,"MOV SP,BP\n");
										//bind_locals(-1,);
										CodeGen($3);
										foo = fprintf(fp,"HALT");

										int z= fclose(fp);
										print_table();
										exit(1);
									}
								}
	 |GDefblock  Mainblock	{	
									//print_table();
									if(TypeFlag==0) {printf("Exit status = failure\n");exit(0);}
									else{
										fp= fopen("outfile.txt","w+");
										int foo = fprintf(fp,"START\n");
										CodeGen($2);
										foo = fprintf(fp,"HALT");
										int z= fclose(fp);
										print_table();
										exit(1);
									}
								}
	;

GDefblock : DECL GDefList ENDDECL	{$$=$2;}
		;

GDefList : GDefList GDecl 	{$$=makenode($1,$2,_GDefList,0,DUMMY);}
		| GDecl				{$$=$1;}
		;

GDecl   : GINT GIdList ';'	{$$=$2; evalDecl(HEAD,$2,0,DUMMY); }
		| GBOOL GIdList ';'	{$$=$2; evalDecl(HEAD,$2,1,DUMMY); }		
		;

GIdList :	GIdList ',' GId  {$$=makenode($1,$3,_GIdList,0,DUMMY);}
		| GId 				 {$$=makenode(NULL,$1,_GIdList,0,DUMMY);}
		;


GId : ID 					{$$=makenode(NULL,NULL,ID,0,$1);}
	| ID '[' Expr ']'		{$$=makenode($3,NULL,ARRAY,0,$1);
							/*MOD : make "expr" integer in grammar*/}
	| ID '(' ArgList ')'   	{$$ = makenode($3,NULL,FUNC,0,$1);	flush_local();}
	| ID '(' ')'			{$$ = makenode(NULL,NULL,FUNC,0,$1);}
	;

ArgList : ArgList ';' Arg 	{$$ = makenode($1,$3,_ArgList,0,"_ArgList");install_args_to_locals(-1,$$);}
		| Arg 				{$$ = makenode($1,NULL,_ArgList,0,"_ArgList");install_args_to_locals(-1,$1);}
		;

Arg : GINT List 			{$$ = makenode($2,NULL,GINT,0,"arg");}
	| GBOOL List 			{$$ = makenode($2,NULL,GBOOL,0,"arg");}
	;

List : List ',' ID			{$$ = makenode($1,makenode(NULL,NULL,ID,0,$3),_List,0,"list");}
	| ID 					{$$ = makenode(NULL,makenode(NULL,NULL,ID,0,$1),_List,0,"list");}
	;

FdefList : FdefList Fdef 	{$$ = makenode($1,$2,_Fdeflist,0,"Fdeflist");}
		| Fdef 				{$$ = makenode(NULL,$1,_Fdeflist,0,"Fdeflist");}
		;
 
Body : StmtList retExp 	{$$ = makenode($1,$2,_body,0,"Body");}
	|	retExp			{$$ = makenode(NULL,$1,_body,0,"Body");}
	;

Fdef : GINT ID '(' ArgList ')' '{' LDefblock SILBEGIN Body END  '}'  
							{	/*MOD : Fdef  <-- stmtlist     (improves tree)*/
								ret_check(0,$9->right);
								
								struct gnode * temp = fetch(head,$2);
								temp->flabel = Label; Label++;
								
								$$ = makenode($9,makenode($4,$7,_junc,0,DUMMY),_Fdef,temp->flabel,$2);	//NEW : right child
								int t = func_check1(0,$2,$4);
								if(t !=-1  ) {getline();TypeFlag=0;}
								flush_local();
							}

	 | GBOOL ID '(' ArgList')' '{' LDefblock SILBEGIN Body END  '}' 
							{	
								ret_check(1,$9->right);

								struct gnode * temp = fetch(head,$2);
								temp->flabel = Label; Label++;

								$$ = makenode($9,makenode($4,$7,_junc,1,DUMMY),_Fdef,temp->flabel,$2);	//NEW : right child
								int t = func_check1(1,$2,$4);
								if(t !=-1  ) {getline();TypeFlag=0;}
								flush_local();
							}

	 | GINT ID  '('  ')' '{' LDefblock SILBEGIN  Body END  '}'
	 						{
	 							ret_check(0,$8->right);

	 							struct gnode * temp = fetch(head,$2);
								temp->flabel = Label; Label++;

	 							$$ = makenode($8,makenode(NULL,$6,_junc,1,DUMMY),_Fdef,temp->flabel,$2);	//NEW : right child
	 							int t = func_check1(0,$2,NULL); 
								if(t !=-1  ) {getline();TypeFlag=0;}
								flush_local();

	 						}

	 | GBOOL ID '('  ')' '{' LDefblock SILBEGIN Body END  '}'
	 						{
	 							ret_check(1,$8->right);

	 							struct gnode * temp = fetch(head,$2);
								temp->flabel = Label; Label++;

	 							$$ = makenode($8,makenode(NULL,$6,_junc,1,DUMMY),_Fdef,temp->flabel,$2);	//NEW : right child
	 							int t = func_check1(1,$2,NULL);		
								if(t !=-1  ) {getline();TypeFlag=0;}
								flush_local();
							}
	 ;

retExp : RET Expr ';'  {$$ = makenode($2,NULL,RET,0,DUMMY);}
		;

LDefblock 	: DECL LDefList ENDDECL   {$$ = $2;evalDecl(L_HEAD,$2,0,DUMMY);print_locals();}

LDefList	:LDefList LDecl {$$ = makenode($1,$2,_LDefList,0,"LDefList");}
			| LDecl			{$$ = makenode(NULL,$1,_LDefList,0,"LDefList");}
			;

LDecl 	: GINT LIdList ';'	{$$ = makenode($2,NULL,GINT,0,"Gint");/*flush_local();/*evalDecl(L_HEAD,$2,0,DUMMY);*/}
		| GBOOL LIdList ';'	{$$ = makenode($2,NULL,GBOOL,0,"Gbool");/*flush_local();/*evalDecl(L_HEAD,$2,0,DUMMY);*/}
		;

LIdList : LIdList ',' ID 	{$$ = makenode($1,makenode(NULL,NULL,ID,0,$3),_LIdList,0,DUMMY);}
		| ID 				{$$ = makenode(NULL,makenode(NULL,NULL,ID,0,$1),_LIdList,0,DUMMY);}
		;	

Mainblock : MAIN  '{' LDefblock SILBEGIN StmtList retExp END  '}'	{$$ = $5;//BP = LocNo -1; SP = BP;
																	flush_local();ret_check(0,$6);
																	bind_locals(-1,$3);			//generate local_table for main
																	printf("\nMAIN LOCAL TABLE \n");
																	print_locals();
																	bind_func_locals($$);
																	}
		|  MAIN  '{'  SILBEGIN StmtList retExp END  '}'	{$$ = $4;
													flush_local();ret_check(0,$5);
													//local_head is null
													}
		;


StmtList: Stmt 				{$$=$1;}
	| StmtList Stmt 		{$$=makenode($1,$2,_StmtList,0,DUMMY);}
	;


Stmt : WRITE '(' Expr ')' ';'	
	{$$=makenode($3,NULL,WRITE,0,"Write"); if(type_check2($$)!=-1){getline();TypeFlag = 0;}}

	| READ '(' Var ')' ';'
	{$$=makenode($3,NULL,READ,0,"Read"); if(type_check2($$)!=-1){getline();TypeFlag = 0;}}
	
	| IF '(' Expr ')' THEN StmtList ENDIF ';'
	{$$=makenode($3,$6,IF,0,"If");     if(type_check2($$)!=-1){getline();TypeFlag = 0;}}

	| IF '(' Expr ')' THEN StmtList ELSE StmtList ENDIF ';'
	{ $$=makenode($3,makenode($6,$8,ELSE,0,"Else"),IF,0,"If");  if(type_check2($$)!=-1){getline();TypeFlag = 0;}}


	| WHILE '(' Expr ')' DO StmtList ENDWHILE ';'	
	{$$=makenode($3,$6,WHILE,0,"While");	if(type_check2($$)!=-1){getline();TypeFlag = 0;}}

	| Var '=' Expr ';'
	{$$=makenode($1,$3,'=',0,"=");	if(type_check2($$)!=-1){getline();TypeFlag = 0;}}

	;



Expr  : Expr '<' Expr    	{$$=makenode($1,$3,'<',0,DUMMY); err_arg(1,$$);}
		| Expr '>' Expr    	{$$=makenode($1,$3,'>',0,DUMMY); err_arg(1,$$);}
		| Expr GE Expr   	{$$=makenode($1,$3,GE,0,DUMMY);	 err_arg(1,$$);}
		| Expr LE Expr    	{$$=makenode($1,$3,LE,0,DUMMY);	 err_arg(1,$$);}	
		| Expr NE Expr   	{$$=makenode($1,$3,NE,0,DUMMY);	 err_arg(1,$$);}
		| Expr EQEQ Expr   	{$$=makenode($1,$3,EQEQ,0,DUMMY);err_arg(1,$$);}
		| '!' Expr  		{$$=makenode($2,NULL,NOT,0,DUMMY);err_arg(1,$$);}
		| Expr AND Expr		{$$=makenode($1,$3,AND,0,DUMMY); err_arg(1,$$);}
		| Expr OR Expr		{$$=makenode($1,$3,OR,0,DUMMY);	 err_arg(1,$$);}

		| TRUE				{$$=makenode(NULL,NULL,_Truth,TRUE,DUMMY);} 
		| FALSE				{$$=makenode(NULL,NULL,_Truth,FALSE,DUMMY);}

		| Expr '+' Expr		{$$=makenode($1,$3,'+',0,DUMMY); err_arg(0,$$);}
		| Expr '-' Expr		{$$=makenode($1,$3,'-',0,DUMMY); err_arg(0,$$);}
		| Expr '*' Expr		{$$=makenode($1,$3,'*',0,DUMMY); err_arg(0,$$);}
		| Expr '/' Expr		{$$=makenode($1,$3,'/',0,DUMMY); err_arg(0,$$);}
		| Expr '%' Expr		{$$=makenode($1,$3,_mod,0,DUMMY);err_arg(0,$$);}
		| INT 				{$$=makenode(NULL,NULL,INT,$1,DUMMY);}
		| Var   			{$$ = $1;}
		| ID '(' ExpList ')'	{$$ = makenode($3,NULL,FUNC,0,$1);}
		| ID '('  	  ')'	{$$ = makenode(NULL,NULL,FUNC,0,$1);}
		;
ExpList : ExpList ',' Expr  {$$ =makenode($1,$3,_ExpList,0,"ExpList");}
		|	Expr 			{$$ =makenode(NULL,$1,_ExpList,0,"ExpList");}
		;

Var		: ID 				{$$=makenode(NULL,NULL,ID,0,$1);}
		| ID '[' Expr ']'	{$$=makenode($3,NULL,ARRAY,0,$1);}
		;

%%

//=========================================================================================================

//====================================================================================




//temp1 is global node pointer associated with checkargs func only
struct gnode * temp1;
//checks for arguments of func in func definitions 
//----------  not declarations in global symbol table 
int check_args(struct node *nd,int i){
	
	if(nd == NULL ) return  1;
	//printf("called check_args????????????????????????????????????%d\n",nd->flag);
	switch(nd->flag){

		case _ArgList : {int t= check_args(nd->right,i) ;int u= check_args(nd->left,i); return t&&u;}
		case GINT : {int t = check_args(nd->left,0); return t;}
		case GBOOL: {int t = check_args(nd->left,1);return  t;}

		case _List : {int t1 = 0;//strcmp(nd->right->varname,temp1->name);
						//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//printf("----------------------------------------\n");

						//printf("arg found is %s\n",nd->right->varname);

						if(t1!=0 || (temp1->type != i)) {
							printf("mismatch in arguments of func (%s %d - %s %d)\n",temp1->name,temp1->type,nd->right->varname,i);
							return 0;
						}
						//printf("present temp at %s\n",temp1->name);
						if(temp1->next)
						temp1 = temp1->next;
						//printf("next temp at %s\n",temp1->name);
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
	if(temp->type-3 != return_type) {getline();printf("return type mismatch\n");flag =0;exit(1);}


	//temp1 is global node pointer associated with checkargs func only
	temp1 = temp->args;

	//function name and return type  are okay
	//check the arguments

	int t  = check_args(nd , -1);
	//printf("###########################%d\n",t);
	if( t == 0 || flag!=1) return -2;

	else return -1; //good

}


//NOTE : ADD func local table at codegen part 

//+=======================================================================================================
//helper for list_checker

int getType(struct node * nd){
	switch(nd->flag){

		case ID : 	{
						struct gnode * temp = fetch(local_head,nd->varname);
						if(temp == NULL) temp = fetch(head,nd->varname);
						if(temp == NULL) {getline();printf("Undeclared var\n");exit(1);}
						return temp->type;
					}

		case ARRAY : {
						struct gnode * temp = fetch(head,nd->varname);
						if(temp == NULL) {getline();printf("Undeclared array\n");exit(1);}
						return temp->type; 
					}	
		case '<' :
		case '>' : 
		case GE :
		case LE :
		case NE :
		case EQEQ:
		case NOT :
		case AND :
		case OR :
		case _Truth :return 1;
		case '+':
		case '-':
		case '%':
		case '*':
		case INT : 
		case '/':return 0;
		case FUNC : {getline();printf("Func cannot be in arguments\n");exit(1);}

	}


}



//temp2 is global node pointer associated with list_checker func only
struct gnode * temp2;
//helpewr function for func_check2
int list_checker(struct node * nd){
	if (nd == NULL) return -1;
	//ADD : what if no arguments
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//change here if you want function arg list to be moire flexible

	if(nd->right){
		int t1 = 0;//strcmp(nd->right->varname,temp2->name);
		//or coulg only check  the type
		int typ = getType(nd->right);
		if(t1!=0 || (temp2->type != typ)) {
			getline();
			printf("mismatch in arguments of func (%s %d - %s %d)\n",temp1->name,temp2->type,nd->right->varname,typ);
			exit(1);
		}
		
		//printf("present temp at %s\n",temp2->name);
		if(temp2->next)
		temp2 = temp2->next;
		//printf("next temp at %s\n",temp2->name);
		
		int t= list_checker(nd->left); 
		
		return t;
	}
	else{
		printf("bagayaro\n");
	}

}


//function  In expressions
int func_check2(struct node * nd){

	struct gnode *temp;
	
	temp = fetch(head,nd->varname);

	if(!temp) {getline();printf("undeclared function used\n");exit(1);}

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


void ret_check(int i,struct node * nd){
	int t = type_check2(nd->left);
	if(t != i ) {getline();printf("return type error\n");exit(1);}

	return ;
}


//version 2   typecheck need to be improved
//returns : -1 okay ,-2 not ok , type of the var(0,1)
//1 for bool ;  0 for int int 
int type_check2(struct node * nd ){ // -1 is good sign , -2 is bad
	if(nd== NULL) {return -1;}

	switch(nd->flag){

		case WRITE:	{int l = type_check2(nd->left);if (l == 0 ) return -1;return -2;}
		case READ : {int l = type_check2(nd->left);return -1;return -2;}

		case '='  :	{int l = type_check2(nd->left); int r = type_check2(nd->right);if(l==r) return -1;return -2;}

		case WHILE: {int l = type_check2(nd->left); if (l == 1) return -1;return -2;}

		case IF   :	{int l = type_check2(nd->left);if(l==1) return -1;return -2;}
		case '<'  : 
		case '>'  : 
		case EQEQ :
		case NE   :
		case LE   :
		case GE   : {int l = type_check2(nd->left); int r = type_check2(nd->right);
						if(l==0 && r==0) return 1;return -2;}

		case '+'  : 
		case '-'  : 
		case '*'  :
		case _mod :
		case '/'  : {int l = type_check2(nd->left); int r = type_check2(nd->right);
						if(l==0 && r==0) return 0;return -2;}

		case INT  : return 0;
		case ARRAY : 
		case ID  : {/*ADD : arr[exp] checker for exp not to be bool*/
					if(nd->left){
						//printf("HERE \n");
						int t = type_check2(nd->left);
						if(t != 0) {getline();printf("Error at array exp\n");exit(1);}
					}
					struct gnode * temp; temp = fetch(local_head,nd->varname);//printf("%d\n",temp); 
							//if (temp == NULL) temp = fetch_args(func,nd->varname);
							if(temp == NULL) temp = fetch(head,nd->varname);
							if(temp == NULL) {getline();printf("no such var detected\n");exit(1);}
							  return temp->type;	
					
				}	

		case _Truth: {if(nd->val == TRUE || nd->val == 	FALSE) return 1;return -2;}

		case AND :
		case OR  :
		case NOT : {int l = type_check2(nd->left);int r=1; if(nd->right){ r = type_check2(nd->right);} 
					if(l==1 && r ==1) return 1; return -2;}

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

//[BP - 3] for arguments in run stack
int nastyCount=-3;	//warning : initialize everytime to -3 do nort forget stupid

void foo(int i, char * _name){
	struct gnode * temp;
	temp = (struct gnode *) malloc(sizeof(struct gnode)) ;
	temp->name = _name;
	temp->type = i;
	temp->bind = nastyCount;
	nastyCount--;
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
		case _List :  {install_args_to_locals(i,nd->left);foo(i,nd->right->varname);break;}

	}

	return;
}


void install_local_var(struct node *nd,int i){

	struct gnode * t = fetch(local_head , nd->varname);
	if (t != NULL) {getline();printf("redeclared var in local \n");exit(1);}
 
	struct gnode * temp;
	temp = (struct gnode *) malloc(sizeof(struct gnode ));




	//NEED to change the BIND here
	temp->name = nd->varname;
	temp->type = i;
	temp->args = NULL;
	//temp->local =NULL;

	temp->next = local_head;
	local_head = temp;

}


//at global sym table func declarations
void install_args(struct gnode *t,struct node *nd,int i,int count){ 
	if(nd == NULL) return;
	switch(nd->flag){
		case _ArgList: {install_args(t,nd->left,i,count);install_args(t,nd->right,i,count);break;}
		case GINT : {install_args(t,nd->left,0,count);break;}
		case GBOOL: {install_args(t,nd->left,1,count);break;}
		case _List :{install_args(t,nd->left,i,count+1);
						struct gnode *temp;


						temp = (struct gnode *)malloc(sizeof(struct gnode ));
						temp->name = nd->right->varname;
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
							gentry(nd->right->varname,i,1,LocNo);
							LocNo++;
						}
						else if(nd->right->flag == ARRAY){
							int size = nd->right->left->val;
							gentry(nd->right->varname,i,size,LocNo);
							LocNo += size;							

						}
						else if(nd->right->flag == FUNC ){
							struct gnode * temp;
							//gnode for function in global symbol table
							temp =(struct gnode *) malloc(sizeof(struct gnode));
							
							temp->name = nd->right->varname;
							int _i;
							if(i==0) _i=3;
							else if(i == 1) _i=4;

							//printf("func name %s(%d)\n",nd->right->varname,_i );

							temp->type = _i;
							temp->args = NULL;

							//head is here now use your head
							temp->next =head;
							head = temp;
							//printf("head : %s\n",head->next->name );
							install_args(temp,nd->right->left,i,0);							
						}
						break;

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
	if(r < 0) {getline();printf("cannot free get whe all are free \n");exit(1);}
	if(r==RegNo)
	{RegNo--;
		regStack[RegNo+1]=-1;
		printRegStack();}
	else{
		printf("%d cannot happen reg(%d) ",lineno,r);
		if(nd)
		printf("at %d\n",nd->flag);
		if(nd->left) printf(": l(%d)  ",nd->left->flag);
		if(nd->right) printf(": r(%d) ",nd->right->flag);
		printf("\n");
	}
}	

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


int getLoc(char * varname){	//gets loc of a var in a reg

	struct gnode * temp;
	
	temp = fetch(local_head,varname);
	
	if(temp) {
		int loc = temp->bind;							//local
		int r1 =getReg();
		int r2 = getReg();
		fprintf(fp,"MOV R%d,BP\n",r1);
		fprintf(fp,"MOV R%d,%d\n",r2,loc);			
		fprintf(fp,"ADD R%d,R%d\n",r1,r2);
		freeReg(r2,NULL);
		return r1;
	}
	
	else temp = fetch(head,varname);	//fetch in  global tab

	if(temp) {
		int loc = temp->bind;
		int r = getReg();
		fprintf(fp, "MOV R%d,%d\n",r,loc);
		return r;
	}
}
int isLocGlobal(int i){
	if(i>=200000) return 1;
	else return 0;
}




int getLocArray(struct node * nd){
	
	int r = CodeGen(nd->left);

	int r1 = getLoc(nd->varname);

	int foo = fprintf(fp,"ADD R%d,R%d\n",r,r1);//add r + r1	

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


void foo2(int i, char * _name,int count){


	struct gnode * temp;
	temp = (struct gnode *) malloc(sizeof(struct gnode)) ;
	temp->name = _name;
	temp->type = i;
	temp->args = NULL;
	temp->bind = count;

	temp->next = local_head;
	local_head = temp;


}

int agcount =1;
void bind_locals(int i,struct node * nd){
	//binds local to mem relative to bp 

	if (nd == NULL) return;

	switch(nd->flag){

		case _LDefList : {bind_locals(i,nd->left);bind_locals(i,nd->right);break;}
		case GINT : {bind_locals(0,nd->left);break;}
		case GBOOL: {bind_locals(1,nd->left);break;}
		case _LIdList : {
							bind_locals(i,nd->left);
							struct gnode * temp = fetch(local_head,nd->right->varname);
							if(temp == NULL)
							foo2(i,nd->right->varname,agcount);	//main part
							agcount++;
							break;
						}
	}

	return ;
}
//_____________________________________________
//helper to func_code_gen
//binds func locals in memory
void bind_func_locals(struct node * nd){
	if(local_head){
		int r = getReg();
		fprintf(fp,"MOV R%d, 0\n",r);	//init all locals as 0
		print_locals();
		int m = local_head->bind; printf("val is impoertantianno %d\n", m);
		int  i=0;
		while(i<m){
			fprintf(fp,"PUSH R%d\n",i);
			i=i+1;
		}
		freeReg(r,nd);
		//print_locals();

		printf("say hi to me now\n");
	}
}
//ADD : label to func  in gsymtab

void func_code_gen(int i,struct node * nd){
	if (nd == NULL) return ;
	switch(nd->flag){

		case _Fdeflist : {
							func_code_gen(i,nd->left);
							func_code_gen(i,nd->right);	
							break;
						}
		case _main:
		case _Fdef : {
						//make the local table then generate the code

						
						printf("------Visting : %s\n",nd->varname);

						fprintf(fp,"L%d:\n",nd->val);
						if(nd->flag != _main)
						fprintf(fp,"PUSH BP\n");
						fprintf(fp,"MOV BP,SP\n");
						agcount = 1;			//for local vars
						nastyCount = -3;  		//for the sake of arguments -- do you get it?
						install_args_to_locals(-1,nd->right->left);
						bind_locals(-1,nd->right->right);
						printf("safty check ");print_locals();
						//by looking the first (last entered var in local sym tab inc the sp i.e push a reg)
						bind_func_locals(nd);		//stack manip
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
		case INT:	{int r = getReg();

					int foo = fprintf(fp,"MOV R%d,%d\n",r,nd->val);

					return r;

					break;} 

		//club ID and Array
		case ID :	{int r = getReg();
					
					int r1 = getLoc(nd->varname);

					int foo = fprintf(fp,"MOV R%d,[R%d]\n",r,r1);

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

					if(nd->left->flag == ID){
						
						int r1 = getLoc(nd->left->varname);

						fprintf(fp,"MOV [R%d], R%d\n",r1,r);

						freeReg(r1,nd);
						//printf("Error123\n");
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

						//printf("name : %s\n",nd->left->varname);
						
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

						 

						 return -1;

						 break;

					}

		case FUNC : {	//ADD : improve this point geta reg free it 
						//		 in this process you will get the max reg in use
						//printf("Error0\n");
						printf("Function call %s\n",nd->varname);
						int r = getReg();
						//printf("Error1\n");
						freeReg(r,nd);

						int i = 0;
						
						while(i<r){
							fprintf(fp, "PUSH R%d\n",i );
							i=i+1;
						}
						
						
						push_list(nd->left);

						r = getReg();
						fprintf(fp, "PUSH R%d\n", r); //return add
						freeReg(r,nd);
						int lab = getFuncLabel(nd->varname);
						//printf("Error2\n");
						//CALL the function
						fprintf(fp,"CALL L%d\n",lab);

						r = getReg();
						fprintf(fp,"POP R%d\n",r);	//	r == return val i guess
						
						//printf("Error3\n");
						pop_list(nd->left);

						//something's fishy here : how to store return value
						i=r-1;
						while(i>=0){
							if (i!=r)
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