#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STR_SIZE 50
#define NR_DISC 10

typedef struct {
	int numero;
	char nome[STR_SIZE]; 
	int disciplinas[NR_DISC];
	int flag;
} aluno;

void initArray(int *arr){
	int i;
	for (i = 0; i < NR_DISC; i++)
	{
		arr[i] = rand()%21;
	}
}

int main(){
	int fd, estado, i, inf[3], dataSize = sizeof(aluno);
	pid_t pid;
	aluno *a;
	
	inf[0] = 0;	//Nota maxima
	inf[1] = 21;//Nota minima
	inf[2] = 0;	//Média

	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	a = (aluno*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	a->flag = 0;
	
	pid = fork();
	if(pid == 0){
		while(a->flag==0);
		for(i = 0; i < NR_DISC; i++){
			inf[2] = inf[2] + a->disciplinas[i];
			if(inf[0] < a->disciplinas[i]) inf[0] = a->disciplinas[i];
			if(inf[1] > a->disciplinas[i]) inf[1] = a->disciplinas[i];
		}
		inf[2] = inf[2] / NR_DISC;
		printf("Nota maxima: %d\nNota minima:%d\nMédia: %d\n", inf[0], inf[1], inf[2]);
		exit(0);		
	}
	
	initArray(a->disciplinas);
	
	a->flag = 1;
	
	waitpid(pid, &estado, 0);
	
		
	//memory management
	if (munmap(a, dataSize) < 0) printf("\nError munmap!");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");
	
	return 0;
}
