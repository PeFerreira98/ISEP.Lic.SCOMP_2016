#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct{
	char nome[100];
	int num;	
}st;

int main(void){
	
	pid_t p;
	int fd[2];
	
	pipe(fd);
	
	p = fork();
	
	if(p>0){
		st st1;
		close(fd[0]);
		
		printf("Escreva um numero: \n");
		scanf("%d", &(st1.num));
		
		printf("Escreva um nome: \n");
		scanf("%s", st1.nome);
		write(fd[1], &st1, sizeof(st1));
		
		close(fd[1]);
	}	
	if(p==0){
		st st2;
		
		close(fd[1]);
		
		read(fd[0], &st2, sizeof(st2));
		
		printf("Numero = %d\n",st2.num);
		printf("Nome = %s\n",st2.nome);
		
		close(fd[0]);
		exit(0);
	}
	
	return 0;
}
