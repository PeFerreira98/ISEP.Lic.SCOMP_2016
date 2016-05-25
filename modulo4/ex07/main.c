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
#include <time.h>

int main(){
	int tamanho = 11, i; 
	pid_t p[11];
	
	char *atend[] = {"./patendedor", NULL};
	char *cli[] = {"./pcliente", NULL};
	printf("\n");
	
	p[0] = fork();
	if (p[0]==0){
		execvp(atend[0], atend);
	}
	sleep(1);
	for (i = 1; i < tamanho; ++i)
	{
		p[1] = fork();
		if (p[1]==0){
			execvp(cli[0], cli);
		}
	}
		
	return 0;
}
