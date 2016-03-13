#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char cria_gemeos(pid_t lista[2]);

int main(void){
	int i = 0;
	pid_t listaTotal[6];
	
	for (i = 0; i < 3; i++)
	{
		printf("%c\n", cria_gemeos(listaTotal+i*2));
	}
		
	return 0;
}

char cria_gemeos(pid_t lista[2]){
	int i = 0, estado = 0;
	
	for (i = 0; i < 2; i++)
	{
		*(lista+i) = fork();
		
		if(*(lista+i)==0){
			printf("I'm %d son with pid %d and ppid %d\n", i, getpid(), getppid());
			if (i == 0)
				exit('a');
				
			if(i == 1)
				exit('b');
		}
	}
	
	for (i = 0; i < 2; i++)
	{
		waitpid(*(lista+i), &estado, 0);
		printf("I'm the father with son %d and return %c\n", *(lista+i), WEXITSTATUS(estado));
	}
	
	return 'p';
}
