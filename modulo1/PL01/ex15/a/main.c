#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	
	pid_t p[argc-1];
	int ret, i = 1, estado;
	
	while(i < argc){
		
		p[i-1] = fork();
		
		if(p[i-1] == 0){
			ret = execlp (argv[i], argv[i], NULL);
			printf("%s : command not found\n", argv[i]);
			exit(0);
		}
		i++;
	}
	
	for(i = 0; i < argc-1; i++){
		waitpid(p[i], &estado, 0);
	}
	
	return 0;
}
