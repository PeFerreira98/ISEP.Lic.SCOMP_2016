#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int NPROC = 6, NUM = 120;

int main(void){
	
	int i=0, k=1, temp=0, estado=0;
	pid_t p[NPROC];
	
	k = k - NUM/NPROC;
	
	for (i = 0; i < NPROC; i++)
	{
		k = k + NUM/NPROC;
		temp = temp + NUM/NPROC;
		//printf("from %d to %d\n", k, temp);
		
		p[i]=fork();
		
		if(p[i]==0){
			
			for (; k <= temp; k++)
			{
				printf("%d ",k);
			}
			printf("\n");
			exit(0);
		}
	}
	
	for (i = 0; i < NPROC; i++)
	{
		waitpid(p[i], &estado, 0);
	}
	
	return 0;
}

//b - Maior parte das experiencias sim. 
//Não. Devido ao facto de não controlarmos qual o filho que executa primeiro.
