#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 10

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





int main() {
  char *text;
  
  
  do{
		text=read_line();
		if (!strlen(text)){
			free(text);
			printf("\n-----FIN-----");
  			return 0;
		}
		printf("\ntext:\n%s",text);
		free(text);
  }while(1);
  
  return 0;
}
