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
#include "struct.h"

typedef struct{
	cliente c;
}shrData;

int main(){
	int fd;
	
	int dataSize = sizeof(shrData);
	shrData *sd1;
	fd = shm_open("/sharedMemory", O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	sd1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	sem_t *semProc;
	semProc = sem_open("semaforoProcesso", O_EXCL, 0644, 0);
	
	//Levanta---
	int qt;
	printf("---CONSULTA---\nSaldo disponivel: %d\n",sd1->c.saldo);
	
	sem_post(semProc);
	//----
	
	if (munmap(sd1, dataSize) < 0) printf("\nError munmap!\n");
	
	return 0;
}
