#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    	int fd[2];

    	pid_t pid;
    	int status;

	pipe(fd);
	pid = fork();

    	if(pid < 0) {
        	exit(EXIT_FAILURE);
    	}

    	if(pid == 0) {
        	dup2(fd[1], 1);
        	close(fd[0]);
        	close(fd[1]);
        	char *argv[] = {"ls", NULL};
        	execv("/bin/ls", argv);
    	}
    	else {
        	while(wait(&status) > 0);

            	dup2(fd[0], 0);
            	close(fd[0]);
            	close(fd[1]);
            	char *argv[] = {"wc", "-l", NULL};
            	execv("/usr/bin/wc", argv);
    	}
    	return 0;
}
