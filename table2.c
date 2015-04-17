//lookup table for identifiers (and arrays)
//no dependency for this file
//global; symbol table


//====================STRUCT for SYMBOL table
 struct gnode {
		char *name;				//variable name
		int type;				//for (0)int or (1)bool
		int size; 				//1 for int and n for array
		int bind; 				//pointer to the entity
		int flabel;
		struct gnode * next;	//pointer in linked list
		struct gnode * args;
		//struct gnode * local;
} ;

struct gnode* head=NULL;
struct gnode* local_head = NULL;


//=====================FETCH
//fetches sybol table node of crresponding var name

struct gnode* fetch(struct gnode *first,char* _name){	//getter
	struct gnode* temp;
	temp=first;
	int t;
	while((temp ) && (t=strcmp(temp->name,_name))){
		temp=temp->next;
	} 
	return temp;
}

//NOTICE : add this to  ---  type check
struct gnode * fetch_args(char * _func,char * _name){
	struct gnode* temp = fetch(head,_func);
	if(temp == NULL) {printf("undeclared func\n");exit(1);}
	temp = fetch(temp->args,_name);
	return temp;
}

//======================GENTRY
void print_table();
// int _loc is added for compilation stage for stage8
//		biind will now be an int and will contain locno. 
void gentry(char* _name,int _type,int _size,int _loc){	//type : 0 fro int
	//if name is not present
	if (!fetch(head,_name)){

		struct gnode* temp;
		temp=(struct gnode *)malloc(sizeof(struct  gnode));
		temp->name=_name;
		temp->size=_size;

		temp->type=_type;
		temp->bind=_loc;
		temp->args = NULL;

		temp->next=head;
		head=temp;
		
	}
	else{
		//error message : if variable is not present in symbol table
		printf("%s\n",_name);
		print_table();
		printf("Sorry var already present or not found\n");
	}
}


void print_locals(){
	struct gnode * temp  = local_head;
	printf("local_table : ");
	while(temp){
		printf("%s(%d-%d) ",temp->name,temp->type,temp->bind );
		temp=temp->next;

	}
	printf("\n");
}

//Additional function just to print global symbol table 
void print_table(){
	printf("\ntable----\n");
	struct gnode* temp;
	temp=head;
	int count=0;
	while(temp){
		if(temp->type == 3 || temp->type == 4){
			printf("(%d) %s(%d) : ",count,temp->name,temp->type);

			struct gnode * t = NULL;
			t = temp->args;
			while(t) {
				printf("%s (%d)-%d ," ,t->name,t->type,t->bind);
				t=t->next;
			}
			t = NULL;
			//printf("\n\t");
			while(t){
				printf(" %s (%d) ," ,t->name,t->type);
				t=t->next;
			}
			printf("\n");

		}
		else{
			if(temp->size>1){
				printf("(%d) %s(%d) : ",count,temp->name,temp->type);
				int place=0;
				for(place=0;place< temp->size; place++){
					printf("%d ", temp->bind+place );
				}
				printf("\n");
			}	
			else{
				printf("(%d) %s(%d): %d\n",count,temp->name,temp->type,temp->bind);
			}
			
		}
		temp=temp->next;
		count++;
	}
	printf("end table\n");
}