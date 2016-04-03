#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	
	pid_t p;

	p = fork();
	
	if (p==0)
	{
		execlp("#!/bin/etc", "-n", "Sistema de Computadores", NULL);
	}
	
		
	return 0;
}
