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

void regInit(registo *vecReg){
	int i;
	for (i = 0; i < NUM_ELEM; i++)
	{
		vecReg[i].codigo_produto = rand()%200+1;
		vecReg[i].codigo_cliente = rand()%100+1;
		vecReg[i].quantidade = rand()%30+1;
	}
}

void regZeroInit(registo *vecReg){
	int i;
	for (i = 0; i < NUM_ELEM; i++)
	{
		vecReg[i].codigo_produto = 0;
		vecReg[i].codigo_cliente = 0;
		vecReg[i].quantidade = 0;
	}
}

void regPrint(registo *vecReg){
	registo rt;
	int i;
	for (i = 0; i < NUM_ELEM; i++)
	{
		rt = vecReg[i];
		printf("Reg %d, Pr: %d, Cli: %d, Qua: %d\n", i, rt.codigo_produto, rt.codigo_cliente, rt.quantidade);
	}
}

int main(void){
	
	pid_t p[NUM_PROC];
	int fd[2];
	int amp = NUM_ELEM/NUM_PROC, i, j, estado, k=0;
	registo vec[NUM_ELEM], maiores[NUM_ELEM], rAux;
	
	regInit(vec); //Inicializar vector de registos
	regZeroInit(maiores);
	regPrint(vec);
	
	pipe(fd); //Criar Pipe
	
	//Criar filhos e distribuição
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
				
	}
	close(fd[1]);
	
	//Leitura de registos e inserção no vec maiores
	while(read(fd[0], &rAux, sizeof(registo)) !=0){
		printf("nr: %d -> quant: %d \n", k, rAux.quantidade);
		maiores[k] = rAux;
		k++;
	}
	
	for(i = 0; i < NUM_PROC; i++){
		waitpid(p[i], &estado, 0);
	}

	return 0;
}
