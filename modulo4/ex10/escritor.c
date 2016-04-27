#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define NUM_LEITORES 5

typedef struct{
	int flag;
	int string;
}shrData;

int main(){
	int i, fd;
	sem_t *semEsc, *semLeitor;
	char *atend[]= {"./pleitor", NULL};
	
	int dataSize = sizeof(shrData);
	shrData *sd1;
	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	sd1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	semEsc = sem_open("semaforoEscritor", O_CREAT | O_EXCL, 0644, 0);
	if(semEsc == SEM_FAILED){
		perror("Erro");
		exit(-1);
	}
	semLeitor = sem_open("semaforoLeitor", O_CREAT | O_EXCL, 0644, 0);
	if(semLeitor== SEM_FAILED){
		perror("Erro");
		exit(-1);
	}
	
	//Escrever--
	pid_t p;
	
	for(i = 0; i < 2; i++){
		if(i==0){
			sd1->string=1;	//Tem que escrever o seu PID e tempo actual assim como quantos escritores activos
			p = fork();
			if(p==0){
				execvp(atend[0], atend);
			}
		}
		if(i==1){
			sd1->string=2;
			sem_post(semEsc);
		}
		
		sem_wait(semLeitor);		
	}
	
	//----
	sem_unlink("semaforoEscritor");
	sem_unlink("semaforoLeitor");
	if (munmap(sd1, dataSize) < 0) printf("\nError munmap!");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");
	
	return 0;
}
