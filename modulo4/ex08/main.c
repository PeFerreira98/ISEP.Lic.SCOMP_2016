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

#define NUM_CLIENTES 2

typedef struct{
	cliente c;
	int opt;
}shrData;

int main(){
	int i, fd, opt = 40;
	sem_t *semProc;
	char *atend[]= {"./plevanta", NULL};
	char *atend2[]= {"./pconsulta", NULL};
	
	cliente vec[NUM_CLIENTES], c1, c2;
	c1.id = 1; c1.saldo = 200;
	c2.id = 2; c2.saldo = 500;
	vec[0] = c1; vec[1] = c2;
	
	int dataSize = sizeof(shrData);
	shrData *sd1;
	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	sd1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	semProc = sem_open("semaforoProcesso", O_CREAT | O_EXCL, 0644, 0);
	if(semProc == SEM_FAILED){
		perror("Erro");
		exit(-1);
	}
	
	//Servidor---
	pid_t p;
	
	for(i = 0; i < NUM_CLIENTES; i++){
		printf("---Cliente ID: %d---\n", vec[i].id);
		sd1->c = vec[i];
		while(opt!=0){
			printf("---\nConsulta de saldo-1\nTransferencias-2\nSair-0\n\n");
			scanf("%d", &opt);
			p = fork();
			if(p==0){
				if(opt == 2){
					execvp(atend[0], atend);
					exit(-1);
				}
				if(opt==1){
					execvp(atend2[0], atend2);
					exit(-1);
				}
			}
			
			if(opt != 0 && opt && 1 && opt != 2){
				printf("Opção invalida!\n");
				sem_post(semProc);
			}
			if(opt == 0) {
				sem_post(semProc);
			}
			sem_wait(semProc);
		}
		opt = 404; //numero aleatorio para nao dar erro na iteração seguinte
	}
	
	//----
	sem_unlink("semaforoProcesso");
	if (munmap(sd1, dataSize) < 0) printf("\nError munmap!");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");
	
	return 0;
}
