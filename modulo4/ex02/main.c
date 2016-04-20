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
	int i, j, c, estado;
	sem_t *sem[NUM_PROC];

	//Semaphore & File Management
	fp = fopen("file.txt", "w+");	
	sem[0] = sem_open("semaforo", O_CREAT | O_EXCL, 0644, 1);
	sem[1] = sem_open("semaforo1", O_CREAT | O_EXCL, 0644, 0);
	sem[2] = sem_open("semaforo2", O_CREAT | O_EXCL, 0644, 0);
	sem[3] = sem_open("semaforo3", O_CREAT | O_EXCL, 0644, 0);
	sem[4] = sem_open("semaforo4", O_CREAT | O_EXCL, 0644, 0);
	
	for(i = 0; i < NUM_PROC; i++){
		
		p[i] = fork();
		if(p[i] == 0){
			
			sem_wait(sem[i]);
	
			for( j = NUM_ELEM*i; j<NUM_ELEM*(i+1); j++){
				fprintf(fp, "%d ", j);
			}
			fprintf(fp, "----\n");
			
			if(i<4) sem_post(sem[i+1]);
			
			exit(0);
		}
	}
	
	for(i = 0; i < NUM_PROC; i++) waitpid(p[i], &estado, 0);
	
	fclose(fp);
	
	//Leitura do ficheiro
	fp = fopen("file.txt", "r");
	while(1){
		
		c = fgetc(fp);
		if(feof(fp)) break; //Sai do ciclo quando EOF
		
		printf("%c", c);
	}
	fclose(fp);

	//Semaphore Management
	if(sem_unlink("semaforo") != 0) printf("Error! >> sem_unlink \n");
	if(sem_unlink("semaforo1") != 0) printf("Error! >> sem_unlink \n");
	if(sem_unlink("semaforo2") != 0) printf("Error! >> sem_unlink \n");
	if(sem_unlink("semaforo3") != 0) printf("Error! >> sem_unlink \n");
	if(sem_unlink("semaforo4") != 0) printf("Error! >> sem_unlink \n");
	
	return 0;
}
