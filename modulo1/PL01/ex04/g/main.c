#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
	
	pid_t pids[3];
	int f, estado;
	
	for(f = 0; f<3; f++){
		pids[f] = fork();
		
		if(pids[f] == -1){
			printf("Erro ao criar processo");
			exit(-1);
		}
		
		if(pids[f]>0){
			printf("Eu sou o pai\n");
		}
		else{
			sleep(1);
			printf("Eu sou filho\n");
			exit(f+1);
		}
	}	
	for(f = 0; f < 3; f++){

		waitpid(pids[f], &estado, 0);

		if(WIFEXITED(estado))
			printf("%dº filho (PID:%d) terminou com valor de saida: %d\n", f+1, pids[f], WEXITSTATUS(estado));

	}	
		
	return 0;
}
