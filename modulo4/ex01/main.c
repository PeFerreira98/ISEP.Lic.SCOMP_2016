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
#define NUM_ELEM 200

int main(){
	pid_t p[NUM_PROC];
	int i, j, estado;
	sem_t *sem;
	
	sem = sem_open("semaforo", O_CREAT | O_EXCL, 0644, 1);
	
	for(i = 0; i < NUM_PROC; i++){
		
		p[i] = fork();
		
		if(p[i] ==0){
			sem_wait(sem);
			for( j = NUM_ELEM*i; j<NUM_ELEM*(i+1);j++){
				printf("%d\n", j);
			}
			printf("----\n");
			sem_post(sem);
			exit(0);
		}
	}
	for(i = 0; i < NUM_PROC; i++){
		waitpid(p[i], &estado, 0);
	}

	sem_unlink("semaforo");
	return 0;
}
