#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(void){
	
	pid_t p;
	int fd[2];
	
	pipe(fd);
	
	p = fork();
	if(p>0){
		char msg[BUFFER_SIZE] = "Hello World";
		char msg2[BUFFER_SIZE] = "Goodbye";
		close(fd[0]);
		
		printf("Pai = Hello world\n");
		write(fd[1], msg , strlen(msg));
		//sleep(1); //Sleep do Pedro
		printf("Pai = Goodbye\n");
		write(fd[1], msg2, strlen(msg));
		close(fd[1]);
	}	
	if(p==0){
		char x[BUFFER_SIZE];
		int n;
		close(fd[1]);
		
		read(fd[0], x, BUFFER_SIZE); printf("%s\n",x);
		read(fd[0], x, BUFFER_SIZE); printf("%s\n",x);
		/*while((n = read(fd[0], x, BUFFER_SIZE)) != 0){
			printf("%s\n",x);
		}*/
		
		close(fd[0]);
		exit(0);
	}
	
	return 0;
}
