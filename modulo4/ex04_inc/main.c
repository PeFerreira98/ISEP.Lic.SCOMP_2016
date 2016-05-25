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
	FILE *fp;
	pid_t p[NUM_PROC];
	int i, estado;
	sem_t *sem;
	
	//Semaphore Management
	sem = sem_open("semaforo", O_CREAT | O_EXCL, 0644, 1);
	
	sem_wait(sem);
			
	//File management
	fp = fopen("file.txt", "a"); //a >> Append
	fprintf(fp, "Eu sou o processo com o PID %d\n", getpid());
	fclose(fp);
			
	//Wait
	printf("Wait 2 sec...\n");
	sleep(2);
	
	sem_post(sem);

	//Semaphore Management
	if(sem_unlink("semaforo") != 0) printf("Error! >> sem_unlink \n");
	
	return 0;
}
