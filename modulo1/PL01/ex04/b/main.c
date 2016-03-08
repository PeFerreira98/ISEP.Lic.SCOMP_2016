#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
	
	pid_t pid;
	int f;
	
	for(f = 0; f<3; f++){
		pid = fork();
		if(pid>0){
			printf("Eu sou o pai\n");
		}
		else{
			sleep(1);
			printf("Eu sou filho\n");
			
		}
	}
		
	return 0;
}
