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

struct comands{
	struct list *list;
	struct comands *next;
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
  	//printf("\n1:\n%s",line);
  	return line;
}

struct list* tokenizar(char *line, char *cut)
{
	struct list *mylist;
	
	mylist=(struct list *)malloc(sizeof(struct list));
	mylist->first=NULL;
	mylist->number_element=0;

	//printf("\n2:\n%s",line);
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
	//printf("\nd:\n%d",mylist->number_element);
	while(i<mylist->number_element){
		printf("\n%d:%s\n",i, aux->ins);
		aux=aux->next;
		i++;
	} 
}

void print_all(struct comands *cmdlist){
	struct comands *aux;
	aux=cmdlist;
	while(aux){
		printf("\nNuevo comando\n");
		print(aux->list);
		aux=aux->next;
	} 
}
	



void free_list(struct list *mylist)
{
	struct cell *aux;
	struct cell *aux2;
	
	aux2=mylist->first;
	
	while (aux2!=NULL){
		aux=aux2->next;
		free (aux2->ins);
		free(aux2);
		aux2=aux;
	}
	free(mylist);
}

void free_all(struct comands *cmdlist){
	struct comands *aux;
	
	
	while(cmdlist){
		aux=cmdlist->next;
		free(cmdlist);
		cmdlist=aux;
	}
}


int main() {
	char *text;
//	char *text2;

	
	struct list *ins_list;
	struct list *arg_list;
	struct cell *ins;
//	struct list *comand;
	struct comands *list_comand;
	struct comands *list_comand2;
	struct comands *aux;	
//	struct cell *aux;	

  
	do{
		list_comand=NULL;
		arg_list=(struct list *) malloc (sizeof(struct list));
		free(arg_list);
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
		
		
	//obtengo para cada instruccion su lista de argumentos. 
		ins=ins_list->first;
		//printf("\nee:\n%d",ins_list->number_element);
		while(i<ins_list->number_element){
			
			arg_list=tokenizar(ins->ins, " ");
			
			if(!list_comand){
				printf("SE AÑADE EL PRIMER ELEMENTO");
				list_comand=(struct comands *) malloc (sizeof(struct comands));
				list_comand->list=NULL;
				list_comand->next=NULL;
				
				list_comand->list=arg_list;
			}else{
				printf("SE AÑADE OTRO ELEMENTO");
				list_comand2=list_comand;
				while (list_comand2){
					aux=list_comand2;
					list_comand2=list_comand2->next;
				}
				list_comand2=(struct comands *) malloc (sizeof(struct comands));
				list_comand2->next=NULL;
				list_comand2->list=arg_list;
				aux->next=list_comand2;
			}
			
			ins=ins->next;
			
			i++;
		}
	//	print(ins_list);
	//	ins=ins_list->first;
	//	while (ins!=NULL){
	//		aux=ins->next;
	//		free(ins);
	//		ins=aux;
	//	}
	
		//printf("\n3:\n%s",text2);
		print_all(list_comand);
		free_all(list_comand);
		free_list(ins_list);
		free(text);

	}while(1);
  
	return 0;
}
