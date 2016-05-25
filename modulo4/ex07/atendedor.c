#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define NUM_MAX 10

typedef struct {
	int numBilh;
} bilhete;

int main(){
	bilhete *bS1;
	sem_t *sem1, *sem2;

	int fd, i=1;
	int dataSize = sizeof(bilhete);

//Semaphore & Memory Management	
	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	bS1 = (bilhete*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	sem1 = sem_open("sAtendedor", O_CREAT|O_EXCL, 0644, 0);
	sem2 = sem_open("sCliente", O_CREAT|O_EXCL, 0644, 0);
		

	printf("Começar venda bilhetes\n");
	while(1){
//Start sell tickets
		bS1->numBilh = i;
		sem_post(sem1);
//wait for client
		sem_wait(sem2);
		if(i++ == NUM_MAX) break;
	}
	

	printf("Exiting atendedor\n");
//Semaphore & memory Management
	if(sem_unlink("sAtendedor") != 0) printf("\nError! >> sem_unlink");
	if(sem_unlink("sCliente") != 0) printf("\nError! >> sem_unlink");
	
	if (munmap(bS1, dataSize) < 0) printf("\nError! >> munmap");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError >> shm_unlink");	
	printf("\n");
	
	return 0;
}
