#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "token.h"
#define BUFFERSIZE 10

struct my_line{
//info sobre la linea de comandos que he leido. 
	struct comands *list_comands;
	char *input;
	char *output;

};
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
    		printf("\n%s\n", line);
    		line=strtok(line, "\n");
    		return line;
    	}
    
  	}
  	//printf("\n1:\n%s",line);
  	return line;
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
	
	struct param_cmd *cmd_line;	
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
		if(text){
			if (!strlen(text)){
				free(text);
				printf("\n-----FIN-----");
	  			return 0;
			}
			
			cmd_line=get_in_out(text);
			free(text);
			printf("\n%s\n%s\n%s\n",cmd_line->comand, cmd_line->in, cmd_line->out);
		//lista de las instrucciones 
			if (cmd_line->comand){
				ins_list=tokenizar(cmd_line->comand, "|");
				//print(ins_list);
			
			
			//obtengo para cada instruccion su lista de argumentos. 
				ins=ins_list->first;
				//printf("\nee:\n%d",ins_list->number_element);
				while(i<ins_list->number_element){
				
					arg_list=tokenizar(ins->ins, " ");
				
					if(!list_comand){
						//printf("SE AÑADE EL PRIMER ELEMENTO");
						list_comand=(struct comands *) malloc (sizeof(struct comands));
						list_comand->list=NULL;
						list_comand->next=NULL;
					
						list_comand->list=arg_list;
					}else{
						//printf("SE AÑADE OTRO ELEMENTO");
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
				free(cmd_line->comand);
				free(cmd_line->in);
				free(cmd_line->out);
				free(cmd_line);				
			}
		}

	}while(1);
  
	return 0;
}
