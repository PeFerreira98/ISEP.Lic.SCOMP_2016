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
		
		printf("Número: ");
		scanf("%d", &nr);
		printf("Valor a apostar: ");
		scanf("%d", &aposta);
		quantia = quantia - aposta;
		
		nrB = batota();
		printf("Numero saido: %d\n", nrB);	
		
		if(nr == nrB){
			printf("Parabéns, acertou!! +%d€ para a sua carteira\n", aposta);
			quantia = quantia + aposta*2;
		}
		printf("Carteira = %d€\n", quantia);		
		
	}
	
	return 0;
}
