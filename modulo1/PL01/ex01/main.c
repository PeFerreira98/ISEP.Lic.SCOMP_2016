#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
	
	pid_t p, a;
	p = fork();
	if (p == -1){
		printf("Erro");
		exit(-1);
	}
	a = fork();
	if(a == -1){
		printf("Erro");
		exit(-1);
	}
	printf("Sistemas de Computadores\n");
		
	return 0;
}
