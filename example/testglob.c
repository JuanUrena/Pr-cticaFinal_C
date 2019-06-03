#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>

char* get_route(char *program){
	char *path=strdup(getenv("PATH"));
	
	
	char *aux2;
	
	
	aux2=strdup(program);
	
	if(!access(aux2, F_OK)){
		free(path);
		return aux2;
	}
		
	free(aux2);

	char *aux=strtok(path, ":");
	
	while (aux!=NULL){
		aux2=calloc(1, strlen(aux)+strlen(program)+2);
		
		strcpy(aux2,aux);
		strcat(aux2,"/");
		strcat(aux2,program);
		
		if(!access(aux2, F_OK)){
			free(path);
			return aux2;
		}
		
		free(aux2);
		aux=strtok(NULL, ":");
	}
	free(path);
	return NULL;
}


int main() {

	char *word=get_route("pwd");
	if (word){
		printf("%s\n",word);
		free(word);
	}
    return 0;
}
