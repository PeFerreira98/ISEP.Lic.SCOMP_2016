#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NUM_PROC 5

typedef struct {
	int vArray[NUM_PROC]; 
} shrData;

void initArray(int *arr){
	int i;
	for (i = 0; i < 1000; i++)
	{
		arr[i] = rand()%1000;
	}
}

int main(){
	int fd, estado, i, j;
	int oriArray[1000], bigstNumber;
	int dataSize = sizeof(shrData);
	pid_t pid[NUM_PROC];
	shrData *sd1;
	
	//inicializar array
	initArray(oriArray);
	
	//create shared memory
	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	sd1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	//criação dos filhos e calculos
	for (i = 0; i < NUM_PROC; i++)
	{
		pid[i] = fork();
		if(pid[i] == 0)
		{
			bigstNumber = 0;
			for (j = i*(1000/NUM_PROC); j < (i+1)*(1000/NUM_PROC); j++)
			{
				if (oriArray[j] > bigstNumber) bigstNumber = oriArray[j];
			}
			sd1->vArray[i] = bigstNumber;
			exit(0);
		}
	}
	
	//espera dos filhos
	for (i = 0; i < NUM_PROC; i++) waitpid(pid[i], &estado, 0);
	
	//print do array da memoria partilhada
	printf("sd1->vArray: ");
	for (i = 0; i < NUM_PROC; i++) printf("%d ", sd1->vArray[i]);
	
	//calculo maior numero
	bigstNumber = 0;
	for (i = 0; i < NUM_PROC; i++)
	{
		if (sd1->vArray[i] > bigstNumber) bigstNumber = sd1->vArray[i];
	}
	printf("\nBiggest Number: %d", bigstNumber);
	
	
	
	//flush shared memory
	if (munmap(sd1, dataSize) < 0) printf("\nError munmap!");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");
	
	return 0;
}
