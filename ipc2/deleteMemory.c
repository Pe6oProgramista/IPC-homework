#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	if(shm_open("simple_memory", O_RDONLY, 0) < 0) {
		perror("open");
		exit(1);
	}

	if(shm_unlink("simple_memory") < 0) {
		perror("unlink");
		exit(1);
	}
	return 0;
}
