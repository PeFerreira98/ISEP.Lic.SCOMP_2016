#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	
	pid_t p;
	int fd[2];
	
	pipe(fd);
	
	p = fork();
	
	if(p>0){
		char nome[100];
		int num;
		close(fd[0]);
		
		printf("Escreva um numero: \n");
		scanf("%d", &num);
		write(fd[1], &num, sizeof(int));
		
		printf("Escreva um nome: \n");
		scanf("%s", nome);
		write(fd[1], nome, 100);
		
		close(fd[1]);
	}	
	if(p==0){
		int n;
		char nom[100];
		close(fd[1]);
		
		read(fd[0], &n, sizeof(int));	
		read(fd[0], nom, 100);
		
		printf("Numero = %d\n",n);
		printf("Nome = %s\n",nom);
		
		close(fd[0]);
		exit(0);
	}
	
	return 0;
}
