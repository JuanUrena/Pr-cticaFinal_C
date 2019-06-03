#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int fd[2];
	char *str ="Luke, I am your father\n";
	int file=open(" text.txt ", O_WRONLY);
	if(pipe(fd) < 0)
		err(EXIT_FAILURE, "cannot make a pipe");

	switch(fork()){
	case -1:
		err(EXIT_FAILURE, "fork failed");
	case 0:
		
		dup2(file, 1);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execl("/usr/bin/tr", "tr", "a-z", "A-Z", NULL);
		err(EXIT_FAILURE, "exec failed");
	default:
		close(fd[0]);
		printf("Aqui");
		dup2(fd[1], 1);
		close(fd[1]);
		printf("%s", str);
 	}
	exit(EXIT_SUCCESS);
}
