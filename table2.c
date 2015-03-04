//lookup table for identifiers (and arrays)
//no dependency for this file
			//global; symbol table

 struct gnode {
		char *name;	//variable name
		int type;	//for (0)int or (1)bool
		int size; 	//1 for int and n for array
		int *bind; 	//pointer to the entity
		struct gnode * next;	//pointer in linked list
} ;

struct gnode* head=NULL;
//struct gnode* temp=NULL;

struct gnode* fetch(char* _name){	//getter
	struct gnode* temp;
	temp=head;
	int t;
	while((temp ) && (t=strcmp(temp->name,_name))){
		temp=temp->next;
	} 
	return temp;
}
								//setter
void set(char* _name,int _value,int _place){

	struct gnode* temp;
	temp=fetch(_name);
	//if(place >= temp->size){   		//int a[10];a[12]=3; ???
	//	printf("memory exceeded\n");
	//}
	//else{

		if(temp==NULL){				//failure
			printf("temp at set: %d\n",temp);
			printf("var not defined\n");
		}		
		else{
			*(temp->bind+_place)=_value;
			//printf("successful var set\n");
								//success
		}
		//if(_place == 0) {printf("ERROR ikkada : %d\n",*(temp->bind));}
	//}
}
void gentry(char* _name,int _type,int _size){	//type : 0 fro int
	//printf("test at gentry %s\n",_name);
	if (!fetch(_name)){
		int *intptr;
		struct gnode* temp;
		temp=(struct gnode *)malloc(sizeof(struct  gnode));
		intptr=(int*) malloc(_size*sizeof(int));
		
		//initializing declared int to zero (0).
		int i;
		for(i=0;i<_size;i++){
			*(intptr+i)=0;
		}
		//printf("gentry initiated\n");
		//printf("---------------------\n");
		//printf("init head addr 		: %d\n",head);
		//printf("new table node addr : %d\n\n",temp );
		temp->name=_name;
		temp->size=_size;
		temp->type=_type;
		temp->bind=intptr;
		//printf("intptr : %d\n",intptr);
		temp->next=head;
		head=temp;
		//free(_name);
	}
	else{
		printf("Sorry already present or not found\n");
	}
}
int get_type(struct gnode *temp){
	return temp->type;
}

void print_table(){
	printf("\ntable----\n");
	struct gnode* temp;
	temp=head;
	int count=0;
	while(temp){
		if(temp->size>1){
			printf("(%d) %s(%d) : ",count,temp->name,temp->type);
			int place=0;
			for(place=0;place< temp->size; place++){
				printf("%d ",*(temp->bind+place) );
			}
			printf("\n");
		}	
		else{
			printf("(%d) %s(%d): %d\n",count,temp->name,temp->type,*(temp->bind));
		}
		temp=temp->next;
		count++;
	}
	printf("end table\n");
}