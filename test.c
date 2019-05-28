#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "token.h"
#define BUFFERSIZE 10

char* read_line(){

	char *line;
	line=(char *)calloc(1,1);
	char buffer[BUFFERSIZE];
//	printf("linea");
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
    		//printf("linea1");
    		char *aux=(char *)malloc(sizeof(strtok(line, "\n")+1));
			strcpy(aux,strtok(line, "\n"));
			free(line);
    		line=strtok(aux, "\n");
    	//	printf("linea");
    		return line;
    	}
    
  	}
  	//printf("\n1:\n%s",line);
  	return line;
}

int main() {
	char *text;
//	char *text2;
	//struct param_cmd *cmd_line;
	//struct value_var *equal;
	//struct param_cmd* mi_param;


	do{
		text=read_line();

	//	text2=strdup(text);
	//compruebo si es EOF
	
		if(text){
			if (!strlen(text)){
				free(text);
				printf("\n-----FIN-----");
	  			return 0;
			};	
			printf("\nANTES\n%s\n", text);
			text=env_variable(text);
			printf("DESPUÉS\n%s\n", text);
			free(text);
		};
		
	}while(1);
  
	return 0;
}
