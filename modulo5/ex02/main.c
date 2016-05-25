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
#define NUM_ELEM 1000

int arr[NUM_ELEM];
int target;

void init_array(){
	for (int i = 0; i < NUM_ELEM; ++i)
		arr[i] = i;
}

void *thread_func(void *arg){
	printf("Thread %lu Executing...\n", pthread_self());
	int value = *((int*) arg);

	int amp = NUM_ELEM/NUM_THREADS;

	int start = value * amp;
	int end = start + amp;

	int i = 0;
	

	printf("\tstart >> %d , end >> %d , target >> %d\n", start, end, target);

	for (i = start; i < end; ++i)
	{
		if (arr[i] == target) 
			printf("\t\tFound It! Pos >> %d\n", i);
	}

	pthread_exit((void*)NULL);
}

int main(){
	pthread_t thread_id[NUM_THREADS];
	int args[NUM_THREADS];
	int i;


	//Initialization Array
	init_array();
	target = 21;


	//Thread Creation
	for (i = 0; i < NUM_THREADS; i++){
		args[i] = i;
		pthread_create(&thread_id[i], NULL, thread_func, &args[i]);
	}


	//Thread Join
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_id[i], NULL);


	return 0;
}
