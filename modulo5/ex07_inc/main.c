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

#define NUM_PRODUTOS 30
#define NUM_HIPERMERCADOS 3

typedef struct
{
	int id_h;
	int id_p;
	int x;
} produto;

produto vec[NUM_PRODUTOS];
produto vec1[NUM_PRODUTOS];
produto vec2[NUM_PRODUTOS];
produto vec3[NUM_PRODUTOS];

int index1;
int index2;
int index3;
int globalResult;

pthread_mutex_t hyperMutex[NUM_HIPERMERCADOS];
pthread_mutex_t globalMutex;

//-------------------------------------------------------------------------

void error_message(char* a){
	printf("Error >> %s\n", a);
}

void init_array_vecs(){
	for (int i = 0; i < NUM_PRODUTOS; ++i)
	{
		vec[i].id_h = 1 + rand() % (NUM_HIPERMERCADOS);
		vec[i].id_p = 1 + rand() % 9;
		vec[i].x = 1 + rand() % 99; 

		vec1[i].id_h = 0;
		vec1[i].id_p = 0;
		vec1[i].x = 0;

		vec2[i].id_h = 0;
		vec2[i].id_p = 0;
		vec2[i].x = 0;

		vec3[i].id_h = 0;
		vec3[i].id_p = 0;
		vec3[i].x = 0;
	}
}

void init_array_mutex(){
	for (int i = 0; i < NUM_HIPERMERCADOS; ++i)
		if (pthread_mutex_init(&hyperMutex[i], NULL) != 0) error_message("pthread_mutex_init");
	
	if (pthread_mutex_init(&globalMutex, NULL) != 0) error_message("pthread_mutex_init");
}

void delete_array_mutex(){
	for (int i = 0; i < NUM_HIPERMERCADOS; ++i)
		if (pthread_mutex_destroy(&hyperMutex[i]) != 0) error_message("pthread_mutex_destroy");
	
	if (pthread_mutex_destroy(&globalMutex) != 0) error_message("pthread_mutex_destroy");
}

//-------------------------------------------------------------------------

void *thread_counter(void * arg){
	printf("SubThread %lu Executing...\n", pthread_self());

	int threadNum = *((int*)arg);
	int value=0;

	if(threadNum == 1){
		for (int i = 0; i < NUM_PRODUTOS; ++i)
			value += vec1[i].x;

		if(pthread_mutex_lock(&globalMutex) != 0) error_message("pthread_mutex_lock");
		if(value < index2 && value < index3) globalResult = 1;
		if(pthread_mutex_unlock(&globalMutex) != 0) error_message("pthread_mutex_unlock");
	}

	if(threadNum == 2){
		for (int i = 0; i < NUM_PRODUTOS; ++i)
			value += vec2[i].x;

		if(pthread_mutex_lock(&globalMutex) != 0) error_message("pthread_mutex_lock");
		if(value < index1 && value < index3) globalResult = 2;
		if(pthread_mutex_unlock(&globalMutex) != 0) error_message("pthread_mutex_unlock");
	}

	if(threadNum == 3){
		for (int i = 0; i < NUM_PRODUTOS; ++i)
			value += vec3[i].x;

		if(pthread_mutex_lock(&globalMutex) != 0) error_message("pthread_mutex_lock");
		if(value < index1 && value < index2) globalResult = 3;
		if(pthread_mutex_unlock(&globalMutex) != 0) error_message("pthread_mutex_unlock");
	} 


	pthread_exit((void*)NULL);
}

void *thread_hyper(void *arg){
	printf("Thread %lu Executing...\n", pthread_self());

	pthread_t thread_id;

	int threadNum = *((int*)arg);
	int amp = NUM_PRODUTOS/NUM_HIPERMERCADOS;
	int i = 0;

	int start = threadNum * amp;
	int end = start + amp;
	
	printf("\tstart >> %d , end >> %d\n", start, end);

	for (i = start; i < end; ++i){
		if (vec[i].id_h == 1){
			if(pthread_mutex_lock(&hyperMutex[0]) != 0) error_message("pthread_mutex_lock");
			vec1[index1++] = vec[i];
			if(pthread_mutex_unlock(&hyperMutex[0]) != 0) error_message("pthread_mutex_unlock");
		} 

		if (vec[i].id_h == 2){
			if(pthread_mutex_lock(&hyperMutex[1]) != 0) error_message("pthread_mutex_lock");
			vec2[index2++] = vec[i];
			if(pthread_mutex_unlock(&hyperMutex[1]) != 0) error_message("pthread_mutex_unlock");
		}

		if (vec[i].id_h == 3){
			if(pthread_mutex_lock(&hyperMutex[2]) != 0) error_message("pthread_mutex_lock");
			vec3[index3++] = vec[i];
			if(pthread_mutex_unlock(&hyperMutex[2]) != 0) error_message("pthread_mutex_unlock");
		}
	}



	//if (pthread_create(&thread_id, NULL, thread_hyper, &threadNum) != 0) error_message("pthread_create");
	//execute thread_count
	//if (pthread_join(thread_id, NULL) != 0) error_message("pthread_join");

	pthread_exit((void*)NULL);
}

//-------------------------------------------------------------------------

int main(){
	pthread_t thread_id[NUM_HIPERMERCADOS];
	int i, args[NUM_HIPERMERCADOS];


	//Initialization Arrays
	init_array_mutex();
	init_array_vecs();
	index1 = 0; index2 = 0; index3 = 0;
	globalResult = 0;


	//Thread Creation
	for (i = 0; i < NUM_HIPERMERCADOS; i++){
		args[i] = i;
		if (pthread_create(&thread_id[i], NULL, thread_hyper, &args[i]) != 0) error_message("pthread_create");
	}
	

	//Thread Join
	for (i = 0; i < NUM_HIPERMERCADOS; i++)
		if (pthread_join(thread_id[i], NULL) != 0) error_message("pthread_join");
		

	//Delete Mutex
	delete_array_mutex();

	for (int i = 0; i < NUM_PRODUTOS; ++i)
	{
		if(vec1[i].id_p == 0 && vec2[i].id_p == 0 && vec3[i].id_p == 0) break;
		printf("%d - %d - %d\n", vec1[i].id_p, vec2[i].id_p, vec3[i].id_p);
	}

	printf("globalResult >> %d\n", globalResult);

	return 0;
}
