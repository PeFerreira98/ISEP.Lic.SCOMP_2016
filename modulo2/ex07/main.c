#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define NUM_PROC 10

typedef struct{
	char *msg;
	int ronda;
}s;

int main(void){
	
	pid_t p[NUM_PROC];
	int fd[2];
	int i, estado;
	s s1;
	
	pipe(fd);
	
	for(i = 0; i < NUM_PROC; i++){
		p[i] = fork();
		if(p[i] == 0){
			close(fd[1]);
			s sF;
		
			read(fd[0], &sF, BUFFER_SIZE);
			printf("Mensagem: %s\nPid: %d\nRonda: %d\n---\n", sF.msg, getpid(), sF.ronda);
			close(fd[0]);
			exit(sF.ronda);
		}
	}
	
	for(i = 0; i < NUM_PROC; i++){
		if(p[i] > 0){
			s1.msg = "win";
			s1.ronda = i+1;
			close(fd[0]);
			write(fd[1], &s1, BUFFER_SIZE);
			sleep(2);
		}
	}
	
	close(fd[1]);
	
	for(i = 0; i < NUM_PROC; i++){
		waitpid(p[i], &estado, 0);
		printf("Pid: %d Ronda: %d\n", p[i], WEXITSTATUS(estado));
	}
		
	return 0;
}
