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
#define NUM_ELEM 100


typedef struct
{
	int threadNumber;
	int intervalo[NUM_THREADS];
	int arr[NUM_ELEM];
	int target;
} shrData;


void init_struct(shrData *sD1){
	sD1->threadNumber = 0;

	for (int i = 0; i < NUM_THREADS; ++i)
		sD1->intervalo[i] = i * (NUM_ELEM/NUM_THREADS);

	for (int i = 0; i < NUM_ELEM; ++i)
		sD1->arr[i] = i;

	sD1->target = 22;
}

void *thread_func(void *arg){
	printf("Thread %lu Executing...\n", pthread_self());
	shrData *sD1 = (shrData*) arg;

	int start = sD1->intervalo[sD1->threadNumber];
	int target = sD1->target;

	int i = 0;
	int end = start + NUM_ELEM/NUM_THREADS;

	printf("\tstart >> %d , end >> %d , target >> %d\n", start, end, target);

	for (i = start; i < end; ++i)
	{
		if (sD1->arr[i] == target) 
			printf("\tFound It! Pos >> %d\n", i);
	}

	pthread_exit((void*)NULL);
}

int main(){
	pthread_t thread_id[NUM_THREADS];
	shrData sData;
	int i;

	//Initialization Struct
	init_struct(&sData);


	//Thread Creation
	for (i = 0; i < NUM_THREADS; i++){
		sData.threadNumber = i;
		pthread_create(&(thread_id[i]), NULL, thread_func, &sData);
	}


	//Thread Join
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_id[i], NULL);


	return 0;
}
