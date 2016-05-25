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
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 5

typedef struct {
	int numero;
	char *nome;
	char *morada;
} shrData;

void *thread_func(void *arg){
	shrData *sD1 = (shrData*) arg; 
	//printf("StructData >> %d >> %s >> %s\n", sD1->numero, sD1->nome, sD1->morada);
	printf("StructData >> %d \n", sD1->numero);
	pthread_exit((void*)NULL);
}

int main(){
	pthread_t thread_id[NUM_THREADS];
	shrData sData[NUM_THREADS];
	int i;

	//Initialization Struct
	for (i = 0; i < NUM_THREADS; i++)
		sData[i].numero = i;
		//sData[i].nome = "Nome";
		//sData[i].morada = "Morada";


	//Thread Creation
	for (i = 0; i < NUM_THREADS; i++)
		pthread_create(&(thread_id[i]), NULL, thread_func, &sData[i]);


	//Thread Join
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_id[i], NULL);


	return 0;
}
