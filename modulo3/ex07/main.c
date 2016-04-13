#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PROD_SIZE 30
#define BUFFER_SIZE 10

typedef struct {
	int intBuffer[10];
	int flag;
} cBuffer;

void initArray(int *arr){
	int i;
	for (i = 0; i < PROD_SIZE; i++)
	{
		arr[i] = 0;
	}
}

int main(){
	int fd, estado, i, j;
	int dataSize = sizeof(cBuffer);
	pid_t pid;
	cBuffer *cB1;

	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	cB1 = (cBuffer*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	cB1->flag = 0;
	
	pid = fork();
	
	if(pid == 0){ // filho - consumer
		
		for(i = 0; i < PROD_SIZE; i=i+BUFFER_SIZE){
			printf("%d transporte: ", ((i/BUFFER_SIZE)+1));
			while(cB1->flag==0);
			for (j = 0; j < BUFFER_SIZE; j++){
				printf("%d ", cB1->intBuffer[j]);
			}
			printf("\n");
			cB1->flag = 0;
		}
		exit(0);		
	}
	
	if (pid > 0){ //pai - producer
		
		for (i = 0; i < PROD_SIZE; i=i+BUFFER_SIZE){
			while(cB1->flag==1);
			for (j = 0; j < BUFFER_SIZE; j++){
				cB1->intBuffer[j] = i+j;
			}
			cB1->flag = 1;
		}
	}
	
	waitpid(pid, &estado, 0);
	
		
	//memory management
	if (munmap(cB1, dataSize) < 0) printf("\nError munmap!");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");
	
	return 0;
}
