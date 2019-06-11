#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>


void forkexample(){ 
	
   /* for loop execution */
   	char *aux=strdup("x=hola");
   	int a=0;
	// child process because return value zero 
	if (fork()){
		if (fork()){
			a=putenv(aux);
			printf("Hello from parent!: %s\n",getenv("x"));
		}else{
			printf("Hello from child!: %s\n",getenv("x"));
		}
	}else{

		printf("Hello from child!: %d\n",a);
		printf("Hello from child!: %s\n",getenv("x"));
	}
	//char *pepe=strdup("hola");

	// parent process because return value non-zero. 
}
int main() { 
	//forkexample();
	char *word="patata";
	char *c=getenv("patata");
	if (!c){
	fprintf(stderr, "error:var %s does not exist", word);
		exit(EXIT_FAILURE);
	}
	printf("%s\n", c);
	return 0; 
}

