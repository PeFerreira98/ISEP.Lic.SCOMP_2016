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
	char str[BUFFER_SIZE];
	int fd[2], estado, n;
	
	pipe(fd);
	p = fork();
	
	if(p == 0){
		close(fd[0]); 
		dup2(fd[1], 1); 
		close(fd[1]);
	
		execlp("sort","sort", "fx.txt", (char*)NULL);
		perror("exec error"); 
		
		exit(1); 
	}  
	
	close(fd[1]);
	
	while((n = read(fd[0], str, BUFFER_SIZE)) !=0){
		str[n-1] = 0;
		printf("Pai leu: %s\n",str);
	}
	
	close (fd[0]);
		
	waitpid(p, &estado, 0);
	
	
	return 0;
}
