#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
	
	pid_t p[5];
	int tamanho = 100, valor = 99, aux = 80, aux2 = 0;
	
	int vec[tamanho], i,j, estado;
	
	for(i = 0; i < tamanho;i ++){
		vec[i] = i;
	}
	
	for(i = 0; i < 5; i++){
		p[i] = fork();
		
		if(p[i] == 0){
			for(j = aux2; j < tamanho-aux; j++){
				if(valor == vec[j]){
					printf("Posição no vector: %d\n", j);
					exit(i+1);
					break;
				}
			}
			exit(0);
		}
		aux = aux - 20;
		aux2 = aux2 + 20;
	}
	
	for(i = 0; i < 5; i++){

		waitpid(p[i], &estado, 0);

		if(WIFEXITED(estado)){
			if(WEXITSTATUS(estado) != 0){
				printf("processo nº: %d \n", WEXITSTATUS(estado));
			}
		}
	}
	
	return 0;
}
