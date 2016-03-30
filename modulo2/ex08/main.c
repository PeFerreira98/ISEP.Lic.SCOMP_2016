#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define NUM_PROC 10
#define NUM_ELEM 50000

typedef struct{
	int codigo_cliente;
	int codigo_produto;
	int quantidade;
}registo;

int main(void){
	
	pid_t p[NUM_PROC];
	int fd[2], amp = NUM_ELEM/NUM_PROC, i, j, estado;
	registo r1, r2, r3, vec[NUM_ELEM],rAux;
	
	//Falta metodo preencheVector()
	r1.codigo_cliente = 2;
	r1.codigo_produto = 1;
	r1.quantidade = 10;
	
	r2.codigo_cliente = 2;
	r2.codigo_produto = 1;
	r2.quantidade = 21;
	
	r3.codigo_cliente = 20202;
	r3.codigo_produto = 1;
	r3.quantidade = 30;
	
	vec[0] = r1; vec[1] = r2; vec[2] = r3;
	
	for(i = 3; i < NUM_ELEM; i++){
		vec[i] = r1;
	}
	
	pipe(fd);
	
	for(i = 0; i < NUM_PROC; i++){
		p[i] = fork();
		
		if(p[i] == 0){
			close(fd[0]);
			for(j = amp * i; j < amp*(i+1); j++){
				if(vec[j].quantidade > 20){
					write(fd[1], &vec[j], sizeof(registo));
				}
			}
			close(fd[1]);
			exit(0);
		}
		
		read(fd[0], &rAux, sizeof(registo));
		//falta metodo addRegisto(registo r)
		printf("fdd: %d \n", rAux.codigo_cliente);
	}
	close(fd[1]);	
	
	for(i = 0; i < NUM_PROC; i++){
		waitpid(p[i], &estado, 0);
	}
		
	return 0;
}
