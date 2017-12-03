#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fd = open("namedPipe", O_WRONLY);
	char* s = "something to transfer...";
	sleep(10);
	write( fd, s, strlen(s) );
	sleep(10);
	return 0;
}
