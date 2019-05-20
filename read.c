#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 10

char* read_line(){

	char *line=calloc(1,1);
	char buffer[BUFFERSIZE];
	
	printf("Enter a message: \n");
	
	while(fgets(buffer, BUFFERSIZE , stdin) ){
  	
    	line = realloc(line, strlen(line)+1+strlen(buffer) );
    	strcat(line, buffer);
    
    	if (buffer[strlen(buffer)-1]=='\n'){
    		return line;
    	}
    
  	}
  	return line;
}





int main() {
  char *text;
  
  
  
  while(1==1){
		text=read_line();
		printf("\ntext:\n%s",text);
		free(text);			    
  }
  
  return 0;
}
