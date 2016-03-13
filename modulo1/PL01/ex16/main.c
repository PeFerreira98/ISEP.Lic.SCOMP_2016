#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void readStr(char *inp);
int divideStr(char *inp, char **arg);
void execution(char **argum);

int main(int argc, char **argv){
	
	char impt[100], **argum;
	int i, lineSize;
	
	argum = (char**) malloc (10*sizeof(char*));
	for (i = 0; i < 10; i++)
	{
		*(argum+i) = (char*) malloc (10*sizeof(char));
	}
	
	while(1){
		readStr(impt);
		
		if(strcmp("sair", impt) == 0){
			printf("BYE-BYE!!\n");
			break;
		}
		
		lineSize = divideStr(impt, argum);
		argum[lineSize] = NULL;
		
		execution(argum);
	}
	
	for (i = 0; i < 10; i++)
	{
		free(argum[i]);
	}
	free(argum);
	return 0;
}

void readStr(char *inp){
	printf("~/SHELL$ ");
	
	fgets(inp, 100, stdin);
	
	//retira o char a mais no final da string 
	*(inp+(strlen(inp)-1)) = '\0';
}

int divideStr(char *inp, char **arg){
	int i=0;
	char *temp;
	
	temp = strtok (inp," ");
	*(arg+i) = temp;
	
	while (temp != NULL)
	{	
		*(arg+i) = temp;
		i++;
		
		temp = strtok (NULL, " ");
		//Alternativelly, a null pointer may be specified, in which case the 
		//function continues scanning where a previous successful call to the function ended.
	}
	
	return i;
}

void execution(char **argum){
	int estado;
	pid_t p;
	
	p = fork();
	
	if (p == 0)
	{
		execvp(argum[0], argum);
	}
	
	waitpid(p, &estado, 0);
}
