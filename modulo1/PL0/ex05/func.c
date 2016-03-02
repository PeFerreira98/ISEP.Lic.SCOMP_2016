#include <stdlib.h>

void func (int *vec, int i, int *vec2){
	
	int a, b = 0;
	vec2 = (int*) realloc(vec2, i * sizeof(int));
	
	for (a = i-1; a >= 0; a--){
		*(vec2 + b) = *(vec + a);
		b++;		
	}
}
