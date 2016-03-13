#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void M(char *c){
	
	pid_t p;
	int f;
	
	p = fork();
	//p = fork();
	
	/*if(p > 0){
		printf("A\n");
		exit(0);
	}
	
	if(p==0){
		printf("B\n");
		p = fork();
	}
	
	if(p>0){
		printf("A\n");
		exit(0);
	}*/
	
	
	for(f = 0; f < 2; f++){
		if(p == 0){
			if(f==0)
			printf("B\n");
			if(f==1){
				printf("A\n");
				p = fork();
			}
				
		}
		if(p>0){
			if(f==0)printf("A\n");
			if(f==1){
				
				p = fork();
				if(p > 0){
					printf("A\n");
					exit(0);
				}
	
				if(p==0){
					printf("B\n");
					p = fork();
				}
	
				if(p>0){
					printf("A\n");
					exit(0);
				}
			}
		}
		
	}
}
