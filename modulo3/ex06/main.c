#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NUM_PROC 10

typedef struct {
	char pathArray[NUM_PROC][100];
	char wordArray[NUM_PROC][20];
	int ocurArray[NUM_PROC];
	int flag;
} shrData;

void initArrays(shrData *sd){
	int i=0;
	
	//Init array de path
	for (i = 0; i < NUM_PROC; i++)
	{
		strcpy(sd->pathArray[i], "Words.txt");
	}
	strcpy(sd->pathArray[0], "Words2.txt");
	
	//Init array de words
	strcpy(sd->wordArray[0], "process");
	strcpy(sd->wordArray[1], "child");
	strcpy(sd->wordArray[2], "parent");
	strcpy(sd->wordArray[3], "determine");
	strcpy(sd->wordArray[4], "producer");
	strcpy(sd->wordArray[5], "10");
	strcpy(sd->wordArray[6], "open");
	strcpy(sd->wordArray[7], "pedro");
	strcpy(sd->wordArray[8], "marcos");
	strcpy(sd->wordArray[9], "consumer");
	
	//Init array occurrences
	for (i = 0; i < NUM_PROC; i++)
	{
		sd->ocurArray[i] = 0;
	}
	
	sd->flag = 1;
}

void printStruct(shrData *sd){
	int i;
	for (i = 0; i < NUM_PROC; i++)
	{
		printf("%s\n", sd->pathArray[i]);
		printf("%s\n", sd->wordArray[i]);
		printf("%d\n", sd->ocurArray[i]);
	}
	printf("flag -> %d\n", sd->flag);
}

int main(){
	int fd, estado, i;
	int dataSize = sizeof(shrData);
	char x[20];
	FILE *fp;
	pid_t pid[NUM_PROC];
	shrData *sd1;

	//criar shared memory
	fd = shm_open("/sharedMemory", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	sd1 = (shrData*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	sd1->flag = 0; //Meter flag a 0

	//criação dos filhos e procura
	for (i = 0; i < NUM_PROC; i++){
		
		pid[i] = fork();
		if(pid[i] == 0){
			
			while(sd1->flag == 0); //Espera pela flag = 1
			
			fp = fopen(sd1->pathArray[i], "r"); //open file
			
			//read & compare word (assumindo que cada palavra é menor que 20 letras)
			while (fscanf(fp, " %19s", x) == 1) {
				if(0 == strcmp(x, sd1->wordArray[i])){
					puts(x);
					sd1->ocurArray[i]++;
				}
			}
	
			//close file and exit
			fclose(fp);
			exit(0);
		}
	}
	
	initArrays(sd1); //inicializar shrData (parent only)
	
	//espera dos filhos
	for (i = 0; i < NUM_PROC; i++) waitpid(pid[i], &estado, 0);
	
	//print do array de ocorrencias
	printf("sd1->ocurArray: ");
	for (i = 0; i < NUM_PROC; i++) printf("%d ", sd1->ocurArray[i]);
	
	
	//flush shared memory
	if (munmap(sd1, dataSize) < 0) printf("\nError munmap!");
	if (shm_unlink("/sharedMemory") < 0) printf("\nError shm_unlink!");	
	printf("\n");
	
	return 0;
}
