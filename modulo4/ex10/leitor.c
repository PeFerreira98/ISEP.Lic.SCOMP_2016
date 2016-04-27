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


#define NUM_LEITORES 5

typedef struct{
	int flag;
	int string;
}shrData;

int main(){
	int fd, i;
	
	int dataSize = sizeof(shrData);
	shrData *sd1;
	fd = shm_open("/sharedMemory", O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	sd1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	sem_t *semEsc, *semLeitor;
	semEsc = sem_open("semaforoEscritor", O_EXCL, 0644, 0);
	semLeitor = sem_open("semaforoLeitor", O_EXCL, 0644, 0);
	if(semLeitor== SEM_FAILED){
		perror("Erro");
		exit(-1);
	}
	
	//Levanta---
	pid_t p[NUM_LEITORES];
	int estado;
	
	for(i = 0; i < NUM_LEITORES; i++){
		p[i] = fork();
		if(p[i] == 0){
			printf("%d :%d\n", sd1->string, i+1); //Falta meter String em vez de int
			exit(0);
		}
		if(i==NUM_LEITORES-1){
			for(i = 0; i < NUM_LEITORES; i++){
				waitpid(p[i], &estado, 0);
			}
			i=-1; //-1 para no fim deste ciclo voltar a i = 0 e fazer outro ciclo for
			sem_post(semLeitor);
			sem_wait(semEsc);
		}		
	}
	
	for(i = 0; i < NUM_LEITORES; i++){
		waitpid(p[i], &estado, 0);
	}	
	//----
	
	//if (munmap(sd1, dataSize) < 0) printf("\nError munmap!\n");
	
	return 0;
}
