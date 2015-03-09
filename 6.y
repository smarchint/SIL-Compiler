%{
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
%token <val> DECL ENDDECL
%token <val> GBOOL GINT INTD BOOLD
%token <val> TRUE
%token <val> FALSE
%token <val> LE GE NE
%token <val> AND OR NOT



%type <ptr> Program 
%type <ptr> Mainblock
%type <ptr> StmtList
%type <ptr> Stmt
%type <ptr> Relexp
%type <ptr> Expr
%type <ptr> Var
%type <ptr> Varlist
%type <ptr> GDecl
%type <ptr> GDefList
%type <ptr> GDefblock


%left OR
%left AND 
%left '!'
%left '+' '-'
%left '*' '/' '%'
%nonassoc '<'
%nonassoc '>' LE NE GE
%nonassoc EQEQ 


%%

Program: GDefblock  Mainblock	{	
									//print_table();
									if(TypeFlag==0) {printf("Exit status = failure\n");exit(0);}
									else{
										//	$$=makenode($2,NULL,_Program,0,DUMMY);
										//evaltree($2,-1);
										fp= fopen("outfile.txt","a");
										int foo = fprintf(fp,"START\n");
										CodeGen($2);
										foo = fprintf(fp,"HALT");
										int z= fclose(fp);
										print_table();
										exit(1);
									}
								}
	;

GDefblock : DECL GDefList ENDDECL	{$$=$2; evalDecl($2,-1);}
		;

GDefList : GDefList GDecl 	{$$=makenode($1,$2,_GDefList,0,DUMMY);}

		| GDecl				{$$=$1;}

		;

GDecl   : GINT Varlist ';'	{$$=makenode($2,NULL,GINT,0,DUMMY); }		//type int
								//evaltree($2,0);}
		
		| GBOOL Varlist ';' {$$=makenode($2,NULL,GBOOL,0,DUMMY); }		//type bool
								//evaltree($2,1);}
		
		;

Mainblock : SILBEGIN StmtList END  	{$$ = $2;}

		;

StmtList: Stmt 			{$$=$1;}

	| StmtList Stmt 	{$$=makenode($1,$2,_StmtList,0,DUMMY);}

	;

Stmt : WRITE '(' Expr ')' ';'
	
	{$$=makenode($3,NULL,WRITE,0,DUMMY);if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}

	| READ '(' Var ')' ';'

	{$$=makenode($3,NULL,READ,0,DUMMY);if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}
	
	| IF '(' Relexp ')' THEN StmtList ENDIF ';'

	{$$=makenode($3,$6,IF,0,DUMMY);
		if(!type_check($$,1)==1){ getline();TypeFlag = 0;}}


	| WHILE '(' Relexp ')' DO StmtList ENDWHILE ';'
	
	{$$=makenode($3,$6,WHILE,0,DUMMY);if(!type_check($$,1)==1) {getline();TypeFlag = 0;}}

	| Var '=' Expr ';'

	{$$=makenode($1,$3,'=',0,DUMMY);if(!type_check($$,1)==1) {getline();TypeFlag = 0;}}

	| Var '=' Relexp ';'

	{$$=makenode($1,$3,'=',0,DUMMY);if(!type_check($$,1)==1) {getline();TypeFlag = 0;}}


	; 

Varlist :	Varlist ',' Var  	{$$=makenode($1,$3,_Varlist,0,DUMMY);}

		| Var 					{$$=makenode(NULL,$1,_Varlist,0,DUMMY);}

		
		;

Relexp  : Expr '<' Expr    	{$$=makenode($1,$3,'<',0,DUMMY);	if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}

		| Expr '>' Expr    	{$$=makenode($1,$3,'>',0,DUMMY);	if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}

		| Expr GE Expr   	{$$=makenode($1,$3,GE,0,DUMMY);		if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}

		| Expr LE Expr    	{$$=makenode($1,$3,LE,0,DUMMY);		if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}
		
		| Expr NE Expr   	{$$=makenode($1,$3,NE,0,DUMMY);		if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}

		| Expr EQEQ Expr   	{$$=makenode($1,$3,EQEQ,0,DUMMY);	if(!type_check($$,0)==1) {getline();TypeFlag = 0;}}

		| '!' Relexp  		{$$=makenode($2,NULL,NOT,0,DUMMY);	if(!type_check($$,1)==1) {getline();TypeFlag = 0;}}

		| Relexp AND Relexp	{$$=makenode($1,$3,AND,0,DUMMY);	if(!type_check($$,1)==1){getline();TypeFlag = 0;}}

		| Relexp OR Relexp	{$$=makenode($1,$3,OR,0,DUMMY);		if(!type_check($$,1)==1) {getline();TypeFlag = 0;}}

		| TRUE				{$$=makenode(NULL,NULL,_Truth,TRUE,DUMMY);}

		| FALSE				{$$=makenode(NULL,NULL,_Truth,FALSE,DUMMY);}

		| Var 				{$$=$1; }

		;

Expr: Expr '+' Expr	{$$=makenode($1,$3,'+',0,DUMMY); if(!type_check($$,0)==0) {getline();TypeFlag = 0;}}

	| Expr '-' Expr	{$$=makenode($1,$3,'-',0,DUMMY); if(!type_check($$,0)==0) {getline();TypeFlag = 0;}}

	| Expr '*' Expr	{$$=makenode($1,$3,'*',0,DUMMY); if(!type_check($$,0)==0) {getline();TypeFlag = 0;}}

	| Expr '/' Expr	{$$=makenode($1,$3,'/',0,DUMMY); if(!type_check($$,0)==0) {getline();TypeFlag = 0;}}

	| Expr '%' Expr	{$$=makenode($1,$3,_mod,0,DUMMY);if(!type_check($$,0)==0) {getline();TypeFlag = 0;}}

	| INT 			{$$=makenode(NULL,NULL,INT,$1,DUMMY);}

	| Var 			{$$=$1;}

	;


Var : ID 				{$$=makenode(NULL,NULL,ID,0,$1);}

	| ID '[' Expr ']'	{$$=makenode($3,NULL,ARRAY,0,$1);}

	;


%%

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
		
		if(type_check(nd->left,1)==1){ return 1;} //okay
		else{
			//error msg
			//printf("Expected bool but found int in  if condition\n");
			return 0;							//not okay
		}
	}

	else if(nd->flag == _StmtList) {
		type_check(nd->left,-1);
		type_check(nd->right,-1);

	}
	else if(nd->flag == THEN){
			type_check(nd->right->left,-1);
			type_check(nd->right->right,-1);
	 }
	

	//ADD THE TYPR_CHECK FOR STMTLIST IN ELSE PART OF IF AND SO PART OF WHILE
	//while------------------------------------------------------------
	else if(nd->flag == WHILE){

		if(type_check(nd->left,1)==1 ) return 1;
		else {
			//error msg
			//printf("Expected bool but found int in  while condition\n");
			return 0;
		}
	}
	//end of function : type_check
}


//CODE GENERATION PART=================================================================

int regStack[8];
//for label generation
int Label=0;

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

void printRegStack(){
	printf("regStack : ");
	int i;
	for( i=0;i<8;i++){
		if(regStack[i]==0 && i >0) break;
		printf("%d ",regStack[i]);
	}
	printf("\n");
}

int getLoc(char * varname){

	struct gnode * temp;
	
	temp = fetch(varname);

	return temp->bind;
}

int getReg(){
//Suggestion : Add error msg if RegNo exceeds 7
	
	RegNo++;
	if(RegNo >7) {
		printf("Exeeded register usage\n");
		return;
	}

	regStack[RegNo] =RegNo;

	printRegStack(); 

	int r = RegNo;
	
	return r;
}

void freeReg(int r){	
//if reg r at top of reg stack the remove else return error
	if(r==0) {printRegStack();return;}
	if(r==RegNo)
	{RegNo--;
		regStack[RegNo+1]=0;
		printRegStack();}
	else{
		printf("cannot happen %d\n",r);
	}
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

//HELPER FUNCTIONS for  CODEGEN function===============
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
		case 7:{int foo =  fprintf(fp,"EQEQ R%d,R%d\n",r1,r2);break;}
		case 8:{int foo =  fprintf(fp,"LE R%d,R%d\n",r1,r2);break;}
		case 9:{int foo =  fprintf(fp,"GE R%d,R%d\n",r1,r2);break;}
		case 10:{int foo =  fprintf(fp,"NE R%d,R%d\n",r1,r2);break;}
	}

	freeReg(r2);

	return r1;
}


//generates machine code for SIM======================
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

		

		case WRITE : //printing out of register
					{
						int  r = CodeGen(nd->left);

						//printf("sam is here\n");

						fprintf(fp,"OUT R%d\n",r);

						freeReg(r);

						return -1;

						break;}

		case READ :	{//load to register then load to memorand

					int r =getReg();

					if(nd->left->flag == ID){

						int foo = fprintf(fp,"IN R%d\n",r);

						int loc = getLoc(nd->left->varname);

						//printf("name : %s\n",nd->left->varname);
						
						foo = fprintf(fp,"MOV [%d],R%d\n",loc,r);

						freeReg(r);

						return -1;

					}
					else if(nd->left->flag == ARRAY) {

						int foo = fprintf(fp,"IN R%d\n",r);

						int r1 = getLocArray(nd->left);

						foo = fprintf(fp,"MOV [R%d],R%d\n",r1,r);

						freeReg(r1);

						freeReg(r);

						return -1;

					}

					break;}

		case IF:{//currently not having else part
					int r  = CodeGen(nd->left);

					int l1 = Label;
					Label++;
					int foo = fprintf(fp,"JZ R%d,L%d\n",r,l1);

					foo = CodeGen(nd->right);

					foo = fprintf(fp,"L%d :",l1);

					freeReg(r);

					return -1;

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

						int r1 = CodeGen(nd->right);

						 foo = fprintf(fp,"JMP L%d\n",l1);

						 foo = fprintf(fp,"L%d:",l2);

						 return -1;

						 break;

					}




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