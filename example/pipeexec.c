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
	printf("Aqui");
	if(pipe(fd) < 0)
		err(EXIT_FAILURE, "cannot make a pipe");

	switch(fork()){
	case -1:
		err(EXIT_FAILURE, "fork failed");
	case 0:
		close(fd[1]);
		close(fd[0]);
		execl("/bin/ls", "ls", NULL);
		err(EXIT_FAILURE, "exec failed");
	default:
		close(fd[0]);
		if(write(fd[1], str, strlen(str)) != strlen(str))
			err(EXIT_FAILURE, "error writting in pipe");
		close(fd[1]);
 	}
	exit(EXIT_SUCCESS);
}
