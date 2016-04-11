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
	int var1;
} shrData;

int main(){
	int fd, estado, i;
	int dataSize = sizeof(shrData);
	shrData *sd1;

	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	
	ftruncate(fd, dataSize);
	
	sd1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	sd1->var1 = 100;
	
	pid_t pid=fork();
	
	for (i = 0; i < 1000; i++)
	{
		(sd1->var1)++;
		(sd1->var1)--;
		printf("%d ", sd1->var1); 
	}
	
	waitpid(pid, &estado, 0);
	
	if (munmap(sd1, dataSize) < 0) printf("\nError munmap!");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");
	
	return 0;
}
