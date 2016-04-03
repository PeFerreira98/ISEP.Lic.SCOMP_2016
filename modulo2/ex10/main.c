#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 100
#define NUM_ELEM 3
#define NUM_PROC 5

typedef struct{
	int cod;
	char *nome;
	double  preco;
}produto;

int main(void){
	
	pid_t p[NUM_PROC];
	int fd[NUM_PROC][2], i, aux, estado, numP = rand()%20;
	
	for(i=0;i<NUM_PROC;i++){
		pipe(fd[i]);
	}
	
	printf("Pai num: %d\n---\n", numP);
	write(fd[0][1], &numP, sizeof(int));
	
	for (i = 0; i < NUM_PROC; i++){
		
		p[i] = fork();
		if(p[i] == 0){
			srand(time(NULL)+i*3);
			int num = rand()%20;
			
			read(fd[i][0], &aux, sizeof(int));
			printf("PID: %d\nNumero: %d\n---\n", getpid(), num);
			
			if(aux>num){
				if(i==4){
					write(fd[0][1], &aux, sizeof(int));
					exit(0);
				}
				write(fd[i+1][1], &aux, sizeof(int));
			}
			else{
				if (i==4)
				{
					write(fd[0][1], &aux, sizeof(int));
					exit(0);
				}
				write(fd[i+1][1], &num, sizeof(int));
			}
			exit(0);
		}
	}
	

	for(i=0;i<NUM_PROC;i++){
		waitpid(p[i], &estado, 0);
	}
	
	read(fd[0][0], &aux, sizeof(int));
	printf("Maior: %d\n", aux);
	
	return 0;
}
