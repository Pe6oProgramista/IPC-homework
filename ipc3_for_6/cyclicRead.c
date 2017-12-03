#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "cyclicBuf.h"
#include "gen.h"
#include "gen.c"

int main() {
	int memFd = shm_open( "simple_memory", O_RDONLY, 0 );
	if( memFd == -1 ) {
		perror("Can't open file");
		return 1;
	}

	struct cyclic_buf* mem = mmap( NULL, sizeof(struct cyclic_buf), PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL ) {
		perror("Can't mmap");
		return -1;
	}	

	uint64_t pos = ( mem->pos + 2048 ) % 128;
	printf("starting at %ld\n", pos);
	while(true) {
		if(mem->pos == pos) {
			sleep(1);
			continue;
		}

		if(verify((void*)mem->array[pos]) < 0) {
			printf("Failed at %ld\n", pos);
			return 1;
		}
		else {
			printf("passed %lu\n", pos);
		}

		pos++;
		pos %= 128;
	}

	return 0;
}
