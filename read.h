#define BUFFERSIZE 10

struct my_line{
//info sobre la linea de comandos que he leido. 
	struct comands *list_comands;
	char *input;
	char *output;

};

char* read_line();

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
    		//printf("\n%s\n", line);
    		line=strtok(line, "\n");
    		return line;
    	}
    
  	}
  	//printf("\n1:\n%s",line);
  	return line;
}
