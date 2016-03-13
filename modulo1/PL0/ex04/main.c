#include <stdio.h>
#include <string.h>
#include "func.h"

int main(void){
	
	int vec[] = {2,6,3,4,9}, tamanho = 5, soma = 0;
	int x = func(vec, tamanho, soma);
	
	printf("Soma dos numeros pares = %d\n", x);
		
	return 0;
}
