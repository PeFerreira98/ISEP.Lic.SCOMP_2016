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

#define NUM_PROC 5

int main(){
	pid_t p;
	int estado;
	sem_t *sem;
	
	sem = sem_open("semaforo", O_CREAT | O_EXCL, 0644, 0);
	
	p = fork();
	
	if(p == 0){
		sem_wait(sem);
		printf("Sou filho\n");
		exit(0);
	}
	if(p > 0){
		printf("Sou pai\n");
		sem_post(sem);
	}
	
	waitpid(p, &estado, 0);

	sem_unlink("semaforo");
	return 0;
}
