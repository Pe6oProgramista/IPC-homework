#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd = open("namedPipe", O_WRONLY);
	char* s = "Hi Georgie!";
	for(int i = 0; i < strlen(s); i++) {
		usleep(60000);
		write( fd, s + i, 1);
	}
	sleep(3);
	close(fd);
	return 0;
}
