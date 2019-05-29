#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

void forkexample(){ 
	
   /* for loop execution */
   	printf("Hello from Parent!\n");

	// child process because return value zero 
	fork();
	printf("Hello from Child!\n"); 
	// parent process because return value non-zero. 
}
int main() { 
	forkexample(); 
	return 0; 
}

