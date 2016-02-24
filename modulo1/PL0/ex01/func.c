int func (int *vec, int i){
	
	int soma = 0,a;
	
	for (a = 0 ; a < i; a++){
		if (*(vec + a ) % 2 == 0){
			soma = soma + *(vec + a);
		}
	}
	
	return soma;
	
}
