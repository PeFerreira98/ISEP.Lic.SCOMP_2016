#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1000
#define NUM_ELEM 3
#define NUM_PROC 1


int main(void){
	
	pid_t p;
	FILE * fp;
	int fd[2], estado;
	
	pipe(fd);
	
	p = fork();
	
	if(p > 0){
		fp = fopen("fx.txt", "w+");
		close(fd[0]); 
		write(fd[1], fp, sizeof(fp));
		close(fd[1]);
	}
	
	if(p == 0){
		close(fd[1]); 
		dup2(fd[0], 0); 
		close(fd[0]);
	
		execlp("od","od", (char*)NULL);
		perror("exec error"); 
		
		exit(1); 
	}  
	
	close(fd[1]);
		
	waitpid(p, &estado, 0);
	
	
	return 0;
}
