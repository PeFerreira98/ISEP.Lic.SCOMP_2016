#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define NUM_ELEM 10
#define NUM_PROC 5

int main(void){
	
	pid_t p[NUM_PROC];
	int matrix[NUM_PROC][2];
	int vec1[NUM_ELEM], vec2[NUM_ELEM], i, j, aux, tot=0, estado;
	
	//Preencher vectores
	for(i = 0; i < NUM_ELEM; i++){
		vec1[i] = 2;
		vec2[i] = 2;
	}
	
	//Criar Pipes
	for(i = 0; i < NUM_PROC; i++){
		pipe(matrix[i]);
	}
	
	//ciclo de criação de filhos e respectivas somas/escritas nos pipes
	for(i = 0; i < NUM_PROC; i++){
		
		p[i] = fork();
		if(p[i] == 0){
			int total;
			close(matrix[i][0]);
			for(j = ((NUM_ELEM/NUM_PROC)*i); j < ((NUM_ELEM/NUM_PROC)*i +(NUM_ELEM/NUM_PROC)); j++){
				total += vec1[j] + vec2[j];
			}
			write(matrix[i][1], &total, sizeof(int));
			close(matrix[i][1]);
			exit(0);				
		}
	}
	
	//ciclo de leitura de pipes
	for (i = 0; i < NUM_PROC; i++)
	{
		read(matrix[i][0],&aux,sizeof(int));		
		tot = tot + aux;
	}
	
	
	for(i = 0; i < NUM_PROC; i++){
		waitpid(p[i], &estado, 0);
	}
	
	printf("%d:\n", tot);
	
	return 0;
}
