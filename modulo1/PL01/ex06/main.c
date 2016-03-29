#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int MAX = 10;

void insRandValues(int *vec, int size);
void insZeros(int *vec, int size);

int main(void){
	
	int dados[MAX], resultado[MAX];
	int MAX_half = MAX/2, i=0, estado;
	pid_t p;
	
	insZeros(dados, MAX);
	insZeros(resultado, MAX);
	
	insRandValues(dados, MAX);
	
	for (i = 0; i < MAX; i++)
	{
		printf("%d ", dados[i]);
	}
	printf("\n");
	
	
	p = fork();
	
	if (p == 0) //child only
	{
		for (i = 0; i < MAX_half; i++)
		{
			*(resultado+i) = dados[i] * 4 + 20;
		}
		
		for (i = 0; i < MAX_half; i++)
		{
			printf("%d ", resultado[i]);
		}
		
		exit(0);
	}

	for (i = MAX_half; i < MAX; i++)
	{
		*(resultado+i) = dados[i] * 4 + 20;
	}
	
	//wait for child to finalize
	waitpid(p, &estado, 0);
	
	for (i = 0; i < MAX; i++)
	{
		printf("%d ", resultado[i]);
	}
	
	printf("\n");
	return 0;
}

void insRandValues(int *vec, int size){
	int i=0;
	for (i = 0; i < size; i++)
	{
		*(vec+i) = rand() % 20;
	}
}

void insZeros(int *vec, int size){
	int i=0;
	for (i = 0; i < size; i++)
	{
		*(vec+i) = 0;
	}
}
