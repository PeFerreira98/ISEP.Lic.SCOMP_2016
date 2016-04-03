#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_ELEM 3
#define NUM_PROC 2

typedef struct{
	int cod;
	char *nome;
	double  preco;
}produto;

int main(void){
	
	pid_t p[NUM_PROC];
	int fd[2][2], i, j, estado;
	
	for(i=0;i<2;i++){
		pipe(fd[i]);
	}
	
	for (j = 0; j < NUM_PROC; j++){
		
		p[j] = fork();
		if(p[j] == 0){
			int codigo;
			produto p;
			close(fd[1][0]);//O filho escreve no 1
			close(fd[0][1]);//o filho lê do 0
			
			printf("Introduza o codigo do produto (0 para sair)\n");
			scanf("%d", &codigo);
			
			write(fd[1][1], &codigo, sizeof(int));
			close(fd[1][1]);
		
			read(fd[0][0], &p, sizeof(produto));
			printf("Nome: %s\nPreço: %f\n", p.nome, p.preco);
			close(fd[0][0]);
			
			exit(0);
		}else if(p[j]>0){
			produto p1;
			p1.cod = 2; p1.nome = "gelado"; p1.preco = 2;
			int cod;
			produto vec[NUM_ELEM]; vec[0] = p1;
			
			close(fd[1][1]);
			close(fd[0][0]);
			read(fd[1][0], &cod, sizeof(int));
			close(fd[1][0]);
			
			for( i = 0; i < NUM_ELEM; i++){
				if(vec[i].cod == cod){
					write(fd[0][1], &vec[i], sizeof(produto));
				}
			}
			
			close(fd[0][1]);
			
		}
	}
	

	for(i=0;i<NUM_PROC;i++){
		waitpid(p[i], &estado, 0);
	}
	
	return 0;
}
