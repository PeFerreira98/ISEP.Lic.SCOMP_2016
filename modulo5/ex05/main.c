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

#define NUM_NR 50

int resultado[NUM_ELEM];
int dados[NUM_ELEM];
pthread_mutex_t mutex[NUM_THREADS];

//-------------------------------------------------------------------------

void error_message(char* a){
	printf("Error >> %s\n", a);
}

void init_array(){
	for (int i = 0; i < NUM_ELEM; ++i){
		dados[i] = 1 + rand() % 50;
		resultado[i] = 0;
	}
}

void init_array_mutex(){
	for (int i = 0; i < NUM_THREADS; ++i)
		if (pthread_mutex_init(&mutex[i], NULL) != 0) error_message("pthread_mutex_init");
}

void delete_array_mutex(){
	for (int i = 0; i < NUM_THREADS; ++i)
		if (pthread_mutex_destroy(&mutex[i]) != 0) error_message("pthread_mutex_destroy");
}

//-------------------------------------------------------------------------

void *thread_func(void *arg){
	printf("Thread %lu Executing...\n", pthread_self());
	int value = *((int*) arg);

	int amp = NUM_ELEM/NUM_THREADS;

	int start = value * amp;
	int end = start + amp;
	
	printf("\tstart >> %d , end >> %d\n", start, end);

	for (int i = start; i < end; ++i)
		resultado[i] = dados[i]*2+10;

	//Print Section //segundo a ordem do vector

	pthread_mutex_lock(&mutex[value]);

	for (int i = start; i < end; ++i)
		printf("%d ", i);
	printf("\n");

	pthread_mutex_unlock(&mutex[value]);
	pthread_mutex_unlock(&mutex[value+1]);

	pthread_exit((void*)NULL);
}

//-------------------------------------------------------------------------

int main(){
	pthread_t thread_id[NUM_THREADS];
	int args[NUM_THREADS];
	int i;


	//Initialization Arrays
	init_array();
	init_array_mutex();

	for (int i = 1; i < NUM_THREADS; ++i)
		pthread_mutex_lock(&mutex[i]);


	//Thread Creation
	for (i = 0; i < NUM_THREADS; i++){
		args[i] = i;
		if (pthread_create(&thread_id[i], NULL, thread_func, &args[i]) != 0) error_message("pthread_create");
	}


	//Thread Join
	for (i = 0; i < NUM_THREADS; i++)
		if (pthread_join(thread_id[i], NULL) != 0) error_message("pthread_join");
		

	//Delete Mutex
	delete_array_mutex();

	return 0;
}
