#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"

int main(void){
	
	int vec[] = {2,6,3,4,9}, tamanho = 5, i;
	int *vec2;
		
	vec2 = (int*) malloc(1*sizeof(int));
	
	func(vec, tamanho, vec2);
	
	for (i = 0; i < tamanho; i++){
		printf("%d\n", *(vec2 + i));
	}
		
	return 0;
}
