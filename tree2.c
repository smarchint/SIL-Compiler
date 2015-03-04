//#include <stdio.h>
//#include <stdlib.h>
//uses functionality of table.c

					//TREE

struct node{ 
		int type;			//0 : int and 1: bool 
		int flag;			//type : one for each below
		int val;			//integers
		char *varname;		
		struct node *right;	
		struct node *left;
};

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

struct node* makenode(struct node* lt,struct node* rt,int flag,int value,char* var){
	struct node* head1= (struct node *)malloc(sizeof(struct node));
	//printf("new htree node adddr : %d\n",head1);
	head1->left=lt;
	head1->right=rt;
	//head1->type=_type;  	//for (0)int or (1)bool
	head1->val=value;
	head1->flag=flag;
	head1->varname=var;
	//printf("\nsai testing%d  %s\n\n",head1,head1->varname);
	//pass;
	return head1;
}
void print(struct node * nd){
	printf("\n(%d) new tree node details \n",nd);
	printf("----------------------------\n");
	printf("varname : %s\n",nd->varname);
	printf("flag	: %d\n",nd->flag);
	printf("val 	: %d\n",nd->val);
	//printf("type 	: %d\n",nd->type);
	printf("lt ptr 	: %d\n",nd->left);
	printf("rt ptr 	: %d\n",nd->right);
	//printf("type	: %d\n",nd->type);
	printf("----------------------------\n");
}
/* 	deepcopy of a struct

struct node* deep_copy( struct node* img){
    struct node* result = malloc(sizeof(struct node));
    if (result)
    {
        // Assuming 'width' means "number of elements" in 'data'. 
        result->varname = img->varname;
        result->flag = malloc(img->flag);
        result->val = malloc(img->val);
        if (result->data)
        {
            memcpy(result->data, img->data, result->width);

        }
        else
        {
            free(result);
            result = NULL;
        }
    }
    return result;
}
*/


/*
//checks typo and returns 1 if ok else returns 0.
int type_check(struct node* nd){

	//operators ----------------------------------------
	if(nd->flag=='+'||nd->flag=='-'||nd->flag=='/'||nd->flag=='*'||\
		nd->flag==_mod ||nd->flag=='>'||nd->flag=='<'||nd->flag==EQEQ||\
		nd->flag==NE||nd->flag==LE ||nd->flag==GE) {
		
		int l=1,m=1; //every thing's okay

		if(nd->left->flag=='+'||nd->left->flag=='-'||nd->left->flag=='/'||\
			nd->left->flag=='*'||nd->left->flag==_mod ) l=1;
		else l=0;

		if(nd->right->flag=='+'||nd->right->flag=='-'||nd->right->flag=='/'||\
			nd->right->flag=='*'||nd->right->flag==_mod ) m=1;
		else m=0;


		if(nd->left->flag==ID || nd->left->flag==ARRAY) {

			struct gnode* temp=fetch(nd->left->varname);
			if(temp->type==1) l=0;
			else l=1;

		} 

		if(nd->right->flag==ID || nd->right->flag==ARRAY) {

			struct gnode* temp=fetch(nd->right->varname);
			if(temp->type==1) m=0;
			else m=1;

		} 
		
		if(l==0 || m==0) {	//if something's wrong
			printf("Expected int but found bool in operators\n");
			//exit(1);
			return 0;			//failure : typo error
		} 
	}


	//logical connectives--------------------------------------------
	else if(nd->flag==AND ||nd->flag==OR||nd->flag==NOT){
		//
		int l=1,m=1;	//default as okay

		if(nd->left->flag==AND ||nd->left->flag==OR ||nd->left->flag==NOT ||\
		nd->left->flag=='>' ||nd->left->flag=='<' ||\
		nd->left->flag==EQEQ ||nd->left->flag==NE ||nd->left->flag==LE ||nd->left->flag==GE ) l=1;
		else l=0;

		if(nd->right &&(
			nd->right->flag==AND ||	nd->right->flag==OR ||nd->right->flag==NOT ||\
			nd->right->flag=='>' ||nd->right->flag=='<' ||\
			nd->right->flag==EQEQ ||nd->right->flag==NE ||nd->right->flag==LE ||nd->right->flag==GE )
		  ) m=1;
		else m=0;
			
		if(l==0 || m==0) {
			printf("Expected bool but found int in logic\n");
			return 0; 		//typo error
			//exit(1);
		}
		else return 1; 
		
	}


	//equality---------------------------------------------------------
	else if(nd->flag== '='){		

		struct gnode * temp= fetch(nd->left->varname);
		//if right contains a bool
		if(nd->right->flag == '>' || nd->right->flag == '<' || nd->right->flag == EQEQ \
			||nd->right->flag == NE || nd->right->flag == LE || nd->right->flag == GE \
			|| nd->right->flag == OR|| nd->right->flag == AND|| nd->right->flag == NOT\
			|| nd->right->flag == _Truth){
				
				if(temp->type !=1) {	//left is an int
					printf("int = bool TYPE MISMATCH\n");
					//exit(1); ///for the time being //later add line no.
					return 0;				//failure : typo error
				}

				else return 1;
		}

		//if right is not bool
		else{	

			if(temp->type !=0) {		//left in a bool
				printf("bool = int TYPE MISMATCH\n");
				//exit(1);
				return 0;					//failure : typo error
			}

			else return 1;
			
		}
	}

	//@Read---------------------------------------------------------------- 
	else if(nd->flag==_READ){
		
		struct gnode * temp= fetch(nd->left->varname);
		//if left has a ijnt
		if(temp->type==0) return 1;
		else {
			printf("bools cannot be read\n");
			return 0;
		}
	}

	//Write----------------------------------------------------------------
	else if(nd->flag==_WRITE){

		struct gnode * temp= fetch(nd->left->varname);
		//if left has a bool 
		if(temp->type==1){
			printf("Bool cannot be written\n");
			return 0;
		}
		else return 1;
	}

	//if conditional------------------------------------------------------
	else if(nd->flag == IF){	
		if(nd->left->flag == '>' || nd->left->flag == '<' || nd->left->flag == EQEQ \
			||nd->left->flag == NE || nd->left->flag == LE || nd->left->flag == GE \
			|| nd->left->flag == OR|| nd->left->flag == AND|| nd->left->flag == NOT\
			|| nd->left->flag == _Truth)

			return 1;
		else{
			printf("Expected RELexp in IF but found EXP\n");
			return 0;
			//exit(1);
		}
	}
	

	//end of function : type_check
}
*/

/*
int evaltree(struct node* nd,int i){		//infix eval
	if (nd == NULL) {	
		return 1;
	}
	//print(nd);
	if(nd->flag==_INT){		//integer
		return nd->val;
	}	


//check both sides as integer
	if(nd->flag=='+'||nd->flag=='-'||nd->flag=='/'||nd->flag=='*'||\
		nd->flag==_GE||nd->flag==_LE||nd->flag==_mod ||nd->flag==_NE||\
		nd->flag=='<'||nd->flag=='>'||nd->flag==_EQEQ) {
		
		struct gnode * temp= fetch(nd->left->varname);
		int l=temp->type;
		temp= fetch(nd->right->varname);
		int m=temp->type;
		if(l==1 || m==1) {
			printf("Expected int but found bool in operators or comparators\n");
			exit(1);
		} 
		

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
			if (evaltree(nd->left,i) > evaltree(nd->right,i)) return 1;
		 	else return 0;
		}
		else if(nd->flag=='<'){
		 	if (evaltree(nd->left,i) < evaltree(nd->right,i)) return 1;
		 	else return 0;
		}

		else if(nd->flag==_EQEQ){
		 	if (evaltree(nd->left,i) == evaltree(nd->right,i)) return 1;
		 	else return 0;
		}


		//later added

		else if(nd->flag==_NE){
		 	if (evaltree(nd->left,i)!=evaltree(nd->right,i)) return 1;
		 	else return 0;
		}
		else if(nd->flag==_GE){
		 	if (evaltree(nd->left,i)>= evaltree(nd->right,i)) return 1;
		 	else return 0;
		}
		else if(nd->flag==_LE){
		 	if (evaltree(nd->left,i) <= evaltree(nd->right,i)) return 1;
		 	else return 0;
		}

	}


	//checking for bool (and. or .not . )

	if(nd->flag==_myAND ||nd->flag==_myOR||nd->flag==_NOT){
		///*
		struct gnode * temp;
		int l,m=1,flag1=1;
		if(nd->left->flag==_ID){
			temp= fetch(nd->left->varname);
			l=temp->type;
			m=1;
			if(nd->right){	
				temp= fetch(nd->right->varname);
				m=temp->type;
			}
			 flag1=1;
			///*
			if(l==0 || m==0) {
				printf("Expected bool but found int in logic\n");
				return 1;
					//exit(1);
			} 
		}

		if(nd->flag==_myAND){
			return (evaltree(nd->left,i) && evaltree(nd->right,i));
		}
		else if(nd->flag==_myOR){
			return (evaltree(nd->left,i) ||  evaltree(nd->right,i));
		}
		else if(nd->flag==_NOT){
		 	return  (!evaltree(nd->left,i));
		}


	}


	
	else if(nd->flag==_Truth){
			return nd->val;
		}




	else if(nd->flag== '='){
		int t=evaltree(nd->right,i);
		struct gnode* temp=fetch(nd->left->varname);
		

		if(nd->right->flag == '>' || nd->right->flag == '<' || nd->right->flag == _EQEQ \
			||nd->right->flag == _NE || nd->right->flag == _LE || nd->right->flag == _GE \
			|| nd->right->flag == _myOR|| nd->right->flag == _myAND|| nd->right->flag == _NOT\
			|| nd->right->flag == _Truth){
				
				if(temp->type !=1) {	//right is int
					printf("int - bool TYPE MISMATCH\n");
					exit(1); ///for the time being //later add line no.
				}
				else{					//right is bool
					if(nd->left->flag==_ID)
						set(nd->left->varname,t,0); //set
					else if(nd->left->flag==_ARRAY){
						int place = evaltree(nd->left->left,i);
						set(nd->left->varname,t,place);
					}
				}
		}
		else{
			if(temp->type !=0) {
				printf("bool - int TYPE MISMATCH\n");
				exit(1);
			}
			else{
			//printf("%s = evaluated val : %d\n",nd->left->varname,t);
				if(nd->left->flag==_ID)
					set(nd->left->varname,t,0); //set
				else if(nd->left->flag==_ARRAY){
					int place = evaltree(nd->left->left,i);
					set(nd->left->varname,t,place);
				}
			}
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
	else if(nd->flag==_GINT){	//to declaration
		evaltree(nd->left,0);	//important type here

	}
	else if(nd->flag==_GBOOL){	//here too----------
		evaltree(nd->left,1);
	}

	else if(nd->flag==_ID){		//getter
		//printf("test@identi : %s\n",need->varname);
		struct gnode * temp;
		temp=fetch(nd->varname);
		int num= *(temp->bind);
		return num;

	}

	else if(nd->flag==_ARRAY){
		struct gnode * temp;
		int place=evaltree(nd->left,i);
		temp=fetch(nd->varname);
		int num= *(temp->bind+place);
		return num;
		
	}

	else if(nd->flag==_Varlist){
		evaltree(nd->left,i);
		if(nd->right->flag==_ID) {
			gentry(nd->right->varname,i,1);
			return 1;
		}
		else if(nd->right->flag==_ARRAY){
			int size=evaltree(nd->right->left,i);
			gentry(nd->right->varname,i,size);
			return 1;
		}
	}
	else if(nd->flag==_INTD){
		evaltree(nd->left,0);
				
	}
	else if(nd->flag==_READ){				//alpha : need to check
		int tempe;
		struct gnode * temp=fetch(nd->left->varname);
		if(temp->type==0){
			
			printf("Enter a number : ");
			scanf("%d",&tempe);
		
			if(nd->left->flag==_ID)
				set(nd->left->varname,tempe,0); //set
			else{
				int place = evaltree(nd->left->left,i);
				set(nd->left->varname,tempe,place);
			}
			printf("reading done\n");
		}
		else {printf("bools cannot be read\n");}
	}

	else if(nd->flag==_WRITE){
		struct gnode * temp=fetch(nd->left->varname);
		if(temp->type==1)
			{printf("Bool cannot be written\n");return 1;}

		printf("printing %d\n",evaltree(nd->left,i));
	}
	else if(nd->flag==_IF){	
		if(nd->left->flag == _ID || nd->left->flag == _ARRAY ){
			struct gnode * temp= fetch(nd->left->varname);
			if(temp->type==0) {
				printf("Expected RELexp in IF but found EXP\n");
				exit(1);
			}
		}
		int n=evaltree(nd->left,i);
		//printf("n is %d\n",n);
		if(n==1) evaltree(nd->right,i);
	}

	else if(nd->flag==_WHILE){
		while(evaltree(nd->left,i)){
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
///*  mistake
void print_tree(struct  node *nd){
	if (nd!=NULL){
		print_tree(nd->left);

		if(nd->flag==1) printf("-%d-",nd->val);
		else if(nd->flag==2) printf("-%s-",*(nd->varname));
		else if(nd->flag==3) printf("-read()-");
		else if(nd->flag==4) printf("-write()-");
		else if(nd->flag==100) printf("-stmts-");
		else if(nd->flag==5) printf("-if-");
		else if(nd->flag==6) printf("-then-");
		else if(nd->flag==7) printf("-while-");
		else if(nd->flag==8) printf("-do-");
		else if(nd->flag==9) printf("-endwhile-");
		else if(nd->flag==10) printf("-int-");
		print_tree(nd->right);
		printf(" ");
	} 

}
//*/
extern FILE *yyin;
int main(int argc, char *argv[]) {
	
	if(argc >= 2){
			yyin = fopen(argv[1], "r");
		
			yyparse();
			
			if(argc >= 2) fclose(yyin);
	}
	else{
		yyparse();
	}
		
	return 0;
}