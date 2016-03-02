#include <stdio.h>
#include <string.h>

int main(void){
	
	const int qtd_procs = 2;
	pid_t pids[qtd_procs];

	int i;
	for(i = 0; i < qtd_procs; i++){
	
		pids[i] = fork();
		if(pids[i] == -1){
			printf("ERROR");
			exit(-1);
		}
		if(pids[i] == 0){
			printf("eu sou %dº filho (PID:%d)\n", i+1, getpid());
			if(i == 0) sleep(5);
			exit(i+1);
		}	
	}

	printf("eu sou o pai (PID:%d)\n", getpid());

	int estado;
	for(i = 0; i < qtd_procs; i++){

		waitpid(pids[i], &estado, 0);

		if(WIFEXITED(estado))
			printf("%d filho (PID:%d) terminou com valor de saida: %d\n", i+1, pids[i], WEXITSTATUS(estado));

	}
		
	return 0;
}
