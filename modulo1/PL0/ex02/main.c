#include <stdio.h>
#include <string.h>
#include "func.h"

int main(void){
	
	int vec[] = {2,6,3,4,9}, tamanho = 5, valor = 2, i;
	func(vec, tamanho, valor);
	
	for (i = 0; i < tamanho; i++){
		printf("%d\n", *(vec + i));
	}
		
	return 0;
}
