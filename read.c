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
	new=(struct cell *) malloc (sizeof(struct cell));
	new->ins=new_ins;
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

	char *line=calloc(1,1);
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
  	return line;
}

struct list * tokenizar(char *line)
{
	struct list *mylist;
	
	mylist=(struct list *) malloc (sizeof(struct list));
	mylist->first=NULL;
	mylist->number_element=0;
	
	
	char *token;
	
	token=strtok(line, "|");
	
	while( token != NULL ) {
		add_element(mylist, token);
		token = strtok(NULL, "|");
   }	
   return mylist;
	
} 

void print(struct list *mylist){
	
	struct cell *aux;
	struct cell *aux2;
	int i=0;
	aux=mylist->first;
	while(i<mylist->number_element){
		printf("\ntoken:\n%s",aux->ins);
		aux2=aux->next;
		free(aux);
		aux=aux2;
		i++;
	} 
	free(mylist);
}





int main() {
  char *text;
  struct list *lista;
  
  
  do{
		text=read_line();
		if (!strlen(text)){
			free(text);
			printf("\n-----FIN-----");
  			return 0;
		}
		lista=tokenizar(text);
		print(lista);
		free(text);
  }while(1);
  
  return 0;
}
