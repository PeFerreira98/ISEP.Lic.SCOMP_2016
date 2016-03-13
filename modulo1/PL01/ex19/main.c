#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	
	char str[100];
	pid_t p;
	int ret;
	
	while(strcmp(".s",str) < 0){
		printf("Escolha um ficheiro (Para sair escreva \".s\") \n");
		scanf("%s", str);
		
		p = fork();
		if(p == -1){
			printf("Erro ao criar processo");
		}
		
		if(strcmp(".s",str) < 0){
			if(p == 0){
				ret = execlp("cp","cp", str, "./backup", (char*)NULL);
				exit(ret);
			}
		}	
	}
	
	return 0;
}
