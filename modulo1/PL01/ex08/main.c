#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int MAX = 6, NUM = 20;

void insRandValues(int *vec, int size);
void insZeros(int *vec, int size);

int main(void){
	
	int i=0, k=-19, temp=0, estado=0;
	pid_t p[MAX];
	
	for (i = 0; i < MAX; i++)
	{
		k = k+NUM;
		temp = temp + 20;
		
		p[i]=fork();
		
		if(p[i]==0){
			
			for (k; k < temp; k++)
			{
				printf("%d ",k);
			}
			exit(0);
		}
	}
	
	for (i = 0; i < MAX; i++)
	{
		waitpid(p[i], &estado, 0);
	}
		
	//printf ("\n");
	return 0;
}
