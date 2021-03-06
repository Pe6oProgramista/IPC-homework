#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "cyclicBuf.h"

int main()
{
	int memFd = shm_open("simple_memory", O_CREAT | O_RDWR, S_IRWXO);
	if(memFd < 0) {
		perror("open");
		return 1;
	}

	int res = ftruncate(memFd, sizeof(struct cyclic_buf));
	if(res < 0) {
		perror("truncate");
		return 1;
	}
	
	struct cyclic_buf* mem = mmap(NULL, sizeof(struct cyclic_buf), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	if(mem == NULL) {
		perror("mmap");
		return 1;
	}

	mem->pos %= 4096;
	int currVal = mem->array[mem->pos];
	while(true) {
		mem->pos++;
		mem->pos %= 4096;
		mem->array[mem->pos] = currVal;
		currVal++;
		if(mem->pos % 512 == 0) {
			sleep(1);
		}
	}	

	return 0;
}
