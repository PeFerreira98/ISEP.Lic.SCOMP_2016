#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_ELEM 3
#define NUM_PROC 1


int main(void){
	
	pid_t p;
	int fd[2], fd2[2], estado, saldo = 20, num = 0, op, numA;
	
	pipe(fd);
	pipe(fd2);
	p = fork();
	
	//fd é de pai para filho
	//fd2 é de filho para pai
	
	while(saldo > 0 || num != -1){
		
		if(p == 0){
			int opt;
			close(fd[1]);
			read(fd[0], &opt, sizeof(int));
			
			if(opt == 0){
				close(fd2[1]);
				exit(0);
			}else if(opt == 1){
				int num = rand()%5+1;
				close(fd2[0]);
				write(fd2[1], &num, sizeof(int));
			}
		}
		else if(p>0){
			
			printf("Numero: ");
			scanf("%d", &num);
		
			if(num == -1 || saldo < 0){
				op = 0;
				close(fd[0]);
				write(fd[1], &op, sizeof(int));
				break;
			}else{
				op = 1;
			
				close(fd[0]);
				write(fd[1], &op, sizeof(int));
			
				close(fd2[1]);
				read(fd2[0], &numA, sizeof(int));
				printf("Numero gerado: %d\n", numA);
			
				if(numA == num){
					saldo = saldo + 10;
				}else{
					saldo = saldo - 5;
				}
				printf("Saldo actual: %d€\n", saldo);
			}
			
		}
	}
		
	waitpid(p, &estado, 0);
	
	
	return 0;
}
