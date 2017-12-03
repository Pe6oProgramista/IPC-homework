#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pipefd[2];
	pid_t cpid;
	char buf;

	if(pipe(pipefd) == -1) {
		perror("pipe");
		return -1;
	}

	cpid = fork();
	if(cpid == -1) {
		perror("fork");
		return -1;
	}

	if(cpid == 0) {
		//This is the forked (child) process
		printf("Hello child\n");
		close(pipefd[1]); //we won't be writing from here
		
		while(read(pipefd[0], &buf, 1) > 0) {
			write(STDOUT_FILENO, &buf, 1);
		}

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		return 0;
	}
	else {
		//This is the original (parent) process
		printf("Hello parent\n");
		close(pipefd[0]); //we won't be writing from here
		char* str = "hyperspace";

		write(pipefd[1], str, strlen(str));
		close(pipefd[1]);
		wait(NULL);
		return 0;
		//close(pipefd[1]); //or we can just exit here...
	}
}
