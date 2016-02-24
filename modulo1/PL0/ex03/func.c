int func (int *vec, int i, int soma){
	i--;
	printf("%d >> %d\n", i, *(vec+i));
	
	if(i==0){
		if (*(vec) % 2 == 0)
		{
			soma = soma + *(vec);
		}	
		return soma;
	}
	
	
	if (*(vec+i) % 2 == 0)
	{
		soma = soma + *(vec+i);
	}
		
	return func(vec, i, soma);
}
