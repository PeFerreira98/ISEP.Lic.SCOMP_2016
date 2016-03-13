#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "batota.h"

int main(){
	
	int quantia = 25, nr, nrB, aposta;
	
	while (quantia > 0){
		printf("Número (1-5): ");
		scanf("%d", &nr);
		
		printf("Valor a apostar: ");
		scanf("%d", &aposta);
		
		if(aposta <= quantia){
			quantia = quantia - aposta;
		
			nrB = batota();
			printf("Numero saido: %d\n", nrB);	
		
			if(nr == nrB){
				printf("Parabéns, acertou!! +%d€ para a sua carteira\n", aposta);
				quantia = quantia + aposta*2;
			}
		}
		
		else{
			printf("Não tem dinheiro suficiente para fazer a aposta!\n");
		} 
			
		printf("Carteira = %d€\n\n", quantia);		
	}
	
	printf("GAME OVER!\n");
	
	return 0;
}
