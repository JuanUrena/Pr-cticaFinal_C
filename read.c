#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 10

struct list{
	struct cell *first;
	int number_element;
};


struct cell{
	char *ins;
	struct cell *next;
};

void add_element(struct list *mylist, char *new_ins)
{
	struct cell *new;
	
	//Estamos copiando la dir de memoria, valorar copiar el contenido a una nueva dir de memoria, para que sea un ente a parte, en vez de un punto al que apuntan dos cosas. 
	new=(struct cell *)malloc(sizeof(struct cell));
	new->ins=(char *)malloc(sizeof(new_ins)+1);
	strcpy(new->ins,new_ins);
	new->next=NULL;
	
	if (mylist->first==NULL){
		mylist->first=new;
		mylist->number_element++;
	}else{
		struct cell *aux;
		aux=mylist->first;
	
		while(aux->next!=NULL){
			aux=aux->next;
		}
		aux->next=new;
		mylist->number_element++;
	}
}

char* read_line(){

	char *line;
	line=(char *)calloc(1,1);
	char buffer[BUFFERSIZE];
	
	if (!line) {
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Enter a message: \n");
	
	while(fgets(buffer, BUFFERSIZE , stdin) ){
  	
    	line = realloc(line, strlen(line)+1+strlen(buffer) );
    	if (!line) {
			fprintf(stderr, "lsh: allocation error\n");
			exit(EXIT_FAILURE);
		}
    	strcat(line, buffer);
    
    	if (buffer[strlen(buffer)-1]=='\n'){
    		return line;
    	}
    
  	}
  	printf("\n1:\n%s",line);
  	return line;
}

struct list* tokenizar(char *line, char *cut)
{
	struct list *mylist;
	
	mylist=(struct list *)malloc(sizeof(struct list));
	mylist->first=NULL;
	mylist->number_element=0;

	printf("\n2:\n%s",line);
	char *copy = (char *)malloc(strlen(line) + 1);
	strcpy(copy, line);
	char *token;
	
	token=strtok(copy, cut);
	
	while(token != NULL ) {
		add_element(mylist, token);
		token = strtok(NULL, cut);
	}
	free(copy);	
   return mylist;
	
} 

void print(struct list *mylist){
	
	struct cell *aux;
	int i=0;
	aux=mylist->first;
	printf("\nd:\n%d",mylist->number_element);
	while(i<mylist->number_element){
		printf("\ntoken:\n%s",aux->ins);
		aux=aux->next;
		i++;
	} 
}

void free_list(struct list *mylist)
{
	struct cell *aux;
	struct cell *aux2;
	
	aux=mylist->first;
	aux2=mylist->first;
	
	while (aux2!=NULL){
		aux=aux2->next;
		free (aux2->ins);
		free(aux2);
		aux2=aux;
	}
	free(mylist);
}




int main() {
	char *text;
//	char *text2;

	
	struct list *ins_list;
	struct list *arg_list;
	struct cell *ins;
//	struct cell *aux;
	
	
	arg_list=(struct list *) malloc (sizeof(struct list));
	arg_list->first=NULL;
	arg_list->number_element=0;
	
	free(arg_list);
  
	do{
	int i=0;
	//La linea de comandos
		text=read_line();
	//	text2=strdup(text);
	//compruebo si es EOF
		
		if (!strlen(text)){
			free(text);
			printf("\n-----FIN-----");
  			return 0;
		}
	//lista de las instrucciones 
		ins_list=tokenizar(text, "|");
		print(ins_list);
		
		
		ins=ins_list->first;
		printf("\nee:\n%d",ins_list->number_element);
		while(i<ins_list->number_element){
			arg_list=tokenizar(ins->ins, " ");
			print(arg_list);
			ins=ins->next;
			i++;
			free_list(arg_list);
		}
	//	print(ins_list);
	//	ins=ins_list->first;
	//	while (ins!=NULL){
	//		aux=ins->next;
	//		free(ins);
	//		ins=aux;
	//	}
	
		//printf("\n3:\n%s",text2);

		
		free_list(ins_list);

		free(text);

	}while(1);
  
	return 0;
}
