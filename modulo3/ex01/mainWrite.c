#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct {
	int num;
	char name[20];
} shrData;

int main(){
	int fd;
	int dataSize = sizeof(shrData);
	shrData *sD1;

	//shared memory creation
	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	sD1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	sD1->num = 1;
	strcpy(sD1->name, "Pedro");
		
	//memory management
	if (munmap(sD1, dataSize) < 0) printf("\nError munmap!");
//	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");

	return 0;
}
