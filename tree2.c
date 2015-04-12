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
		struct node * parent;
};

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

struct node* makenode(struct node* lt,struct node* rt,int flag,int value,char* var){
	struct node* head1= (struct node *)malloc(sizeof(struct node));
	//printf("new htree node adddr : %d\n",head1);
	head1->left=lt;
	head1->right=rt;
	if(lt && rt ){
	lt->parent = head1;
	rt->parent = head1;
	}
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

/*  mistake
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
*/
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