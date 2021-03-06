#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "cyclicBuf.h"

int main() {
	sleep(3);
	int memFd = shm_open( "simple_memory", O_RDONLY, 0 );
	if(memFd < 0) {
		perror("file");
		return 1;
	}

	struct cyclic_buf* mem = mmap( NULL, sizeof(struct cyclic_buf), PROT_READ, MAP_SHARED, memFd, 0 );
	if(mem == NULL) {
		perror("mmap");
		return -1;
	}	

	uint64_t pos = ( mem->pos + 2048 ) % 4096;
	printf("starting at %ld\n", pos);
	while( true ) {
		if(mem->pos == pos) {
			sleep(1);
			continue;
		}
		printf("%d\n", mem->array[pos]);
		if(mem->array[pos] == 9)
			printf( "\n" );
		pos++;
		pos %= 4096;
	}

	return 0;
}
