#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	
	pid_t p;
	
	p = fork();
	if(p==0){
		printf("filho = %d\n", getpid());
	}
	if(p>0){
		printf("%d\n%d\n", getpid(),getppid());
	}
	
	return 0;
}
