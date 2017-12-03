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

	uint64_t pos = ( mem->pos + 2048 ) % 4096;
	printf("starting at %ld\n", pos);
	while(true) {
		if(mem->pos == pos) {
			continue;
		}

		if(verify((void*)mem->array) != mem->pos) {
			printf("Failed at %ld\n", mem->pos);
			return 1;
		}
		if(mem->pos%1024 == 0) {
			printf("passed %lu\n", pos);
		}

		pos++;
		pos %= 4096;
	}

	return 0;
}
