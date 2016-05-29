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
int vec[NUM_ELEM];

void *thread_func(void *arg){
	int i, aux = 0;
	int num = *((int*)arg);
	//printf("%d ", num);
	
	for(i = num*(NUM_ELEM/NUM_THREADS); i < (num+1)*(NUM_ELEM/NUM_THREADS); i++){
		aux = aux + vec[i];
	}
	//printf("%d ", aux);
	pthread_exit((void*)aux);
}

void initArray(int *vec){
	int i;
	for(i = 0; i < NUM_ELEM; i++){
		vec[i] = 1;
		//printf("%d ", vec[i]);
	}
}

int main(){
	pthread_t thread_id[NUM_THREADS];
	int i, soma = 0;
	initArray(vec);
	int arg[NUM_THREADS];

	//Thread Creation
	for (i = 0; i < NUM_THREADS; i++){
		arg[i] = i;
		pthread_create(&(thread_id[i]), NULL, thread_func, &arg[i]);
	}

	int res;
	//Thread Join
	for (i = 0; i < NUM_THREADS; i++){
		pthread_join(thread_id[i], (void*)&res);
		soma = soma + res;
	}
	
	printf("\nSoma: %d\n", soma);

	return 0;
}
