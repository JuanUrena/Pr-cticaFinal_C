#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



void close_pipes(int pipes[4][2]){
	for (int i=0; i<4; i++){
		close(pipes[i][0]);
		close(pipes[i][1]);
	} 
}


int
main(int argc, char *argv[])
{

	int num_pipes=4;
	int conex[num_pipes][2];
				
			
	for(int i=0; i<num_pipes; i++){
		if (pipe(conex[i]) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}else{
			printf("Correct\n");
		}
	}

//	char *str ="Luke, I am your father\n";
	printf("Aqui");

	switch(fork()){
	case -1:
		err(EXIT_FAILURE, "fork failed");
	case 0:
		dup2(conex[3][0], 0);
		close_pipes(conex);
		execl("/usr/bin/tr", "tr", "a-z", "A-Z",NULL);
		err(EXIT_FAILURE, "exec failed");
	default:
		dup2(conex[3][1], 1);
		close_pipes(conex);
		execl("/bin/ls", "ls", NULL);
		
 	}
	exit(EXIT_SUCCESS);
}
