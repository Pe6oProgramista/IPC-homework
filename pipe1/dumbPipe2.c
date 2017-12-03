#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	mkfifo("namedPipe", 0666);
	pid_t cpid;
	char buf;

	cpid = fork();
	if(cpid < 0) {
		perror("fork");
		return -1;
	}
	else if(cpid == 0) {
		//printf("Hello from child\n");
		
		int fd = open("namedPipe", O_RDONLY);
		if(fd < 0) {
			perror("open");
			return 1;
		}

		while(read(fd, &buf, 1) > 0) {
			write(STDOUT_FILENO, &buf, 1);
		}
		write(STDOUT_FILENO, "\n", 1);

		if(close(fd) < 0) {
			perror("close");
			return 3;
		}

		return 0;
	}
	else {
		//printf("Hello from parent\n");

		int fd = open("namedPipe", O_WRONLY);
		if(fd < 0) {
			perror("open");
			return 2;
		}
		char* str = "Hi, Georgie! :D";
		for (int i = 0; i < strlen(str); ++i) {
			usleep(60000);
			write(fd, str + i, 1);
		}
		//write(STDOUT_FILENO, "Parent write it!\n", 17);

		if(close(fd) < 0) {
			perror("close");
			return 4;
		}
		wait(NULL);

		return 0;
	}
}
