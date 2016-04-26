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

int main(){
	pid_t p;
	int estado, i;
	sem_t *semP;
	sem_t *semF;
	
	semP = sem_open("semaforo", O_CREAT | O_EXCL, 0644, 1);
	if(semP == SEM_FAILED){
		perror("Erro");
		exit(-1);
	}
	semF = sem_open("semaforoF", O_CREAT | O_EXCL, 0644, 0);
	if(semF == SEM_FAILED){
		perror("Erro");
		exit(-1);
	}
	
	p = fork();
	if(p < 0){
		perror("Erro fork");
		exit(-1);
	}
	
	for(i=0; i<10; i++){
		if(p == 0){
			sem_wait(semF);
			printf("Sou filho\n");
			sem_post(semP);
		}
		if(p > 0){
			sem_wait(semP);
			printf("Sou pai\n");
			sem_post(semF);
		}
	}
	if(p == 0) exit(0);
	
	waitpid(p, &estado, 0);
	
	sem_unlink("semaforoF");
	sem_unlink("semaforo");
	return 0;
}
