int func (int *vec, int i, int valor){
	
	int a;
	
	for (a = 0 ; a < i; a++){
		*(vec + a) = *(vec + a) - valor;
	}
	
}
