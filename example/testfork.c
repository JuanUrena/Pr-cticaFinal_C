#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>


void forkexample(){ 
	
   /* for loop execution */
   	char *aux=strdup("hola");
   
	// child process because return value zero 
	if (fork()){
			free(aux);
			printf("Hello from Parent!: %s\n",aux);
	}else{
			printf("Hello from Child!: %s\n", aux);
			printf("Hello from Child!: %s\n", aux);
			printf("Hello from Child!: %s\n", aux);
			printf("Hello from Child!: %s\n", aux);
			
	}
	//char *pepe=strdup("hola");

	// parent process because return value non-zero. 
}
int main() { 
	forkexample(); 
	return 0; 
}

