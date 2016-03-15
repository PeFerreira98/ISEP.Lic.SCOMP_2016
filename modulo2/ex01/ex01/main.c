#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	
	pid_t p;
	int pid = getpid();
	int fd[2];
	
	printf("Pid do pai = %d\n", pid);
	pipe(fd);
	
	p = fork();
	if(p>0){
		close(fd[0]);
		write(fd[1], &pid, sizeof(int));
		close(fd[1]);
	}	
	if(p==0){
		int x;
		read(fd[0], &x, sizeof(int));
		close(fd[1]);
		printf("Pid atraves do filho = %d\n",x);
		close(fd[0]);
		exit(0);
	}
	
	return 0;
}
