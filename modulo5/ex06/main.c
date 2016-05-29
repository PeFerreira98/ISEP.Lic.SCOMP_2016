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

#define NUM_TRAIN 10
#define NUM_RAIL 3

typedef struct
{
	int numero;
	char origem;
	char destino;
} comboio;

comboio comboios[NUM_TRAIN];
pthread_mutex_t caminho[NUM_RAIL];

//-------------------------------------------------------------------------

void error_message(char* a){
	printf("Error >> %s\n", a);
}

void init_array_mutex(){
	for (int i = 0; i < NUM_RAIL; ++i)
		if (pthread_mutex_init(&caminho[i], NULL) != 0) error_message("pthread_mutex_init");
}

void delete_array_mutex(){
	for (int i = 0; i < NUM_RAIL; ++i)
		if (pthread_mutex_destroy(&caminho[i]) != 0) error_message("pthread_mutex_destroy");
}

//-------------------------------------------------------------------------

char *hora(){
  	return "hh:mm:ss";
}

void linha(comboio *c1, int id_linha){

	if(pthread_mutex_lock(&caminho[id_linha]) != 0) error_message("pthread_mutex_lock");

	printf("Comboio %d, Origem %c, Destino %c,", 
		c1->numero, c1->origem, c1->destino);
	
	if (id_linha == 0)  printf(" Linha A-B\n");
	if (id_linha == 1)  printf(" Linha B-C\n");
	if (id_linha == 2)  printf(" Linha C-D\n");

	sleep(1);

	if(pthread_mutex_unlock(&caminho[id_linha]) != 0) error_message("pthread_mutex_unlock");
}

void *thread_trip_func(void *arg){
	//printf("Thread %lu Executing...\n", pthread_self());
	comboio* c1 = (comboio*) arg;

	char start = c1->origem;
	char end = c1->destino;

	char* departureHour = hora();

	if (start == 'A')
	{
		if (end == 'B') { linha(c1, 0); }
		if (end == 'C') { linha(c1, 0); linha(c1, 1); }
		if (end == 'D') { linha(c1, 0); linha(c1, 2); }
	}

	if (start == 'B')
	{
		if (end == 'A') { linha(c1, 0); }
		if (end == 'C') { linha(c1, 1); }
		if (end == 'D') { linha(c1, 2); }
	}

	if (start == 'C')
	{
		if (end == 'A') { linha(c1, 1); linha(c1, 0); }
		if (end == 'B') { linha(c1, 1); }
		if (end == 'D') { linha(c1, 1); linha(c1, 2); }
	}

	if (start == 'D')
	{
		if (end == 'A') { linha(c1, 2); linha(c1, 0); }
		if (end == 'B') { linha(c1, 2); }
		if (end == 'C') { linha(c1, 2); linha(c1, 1); }
	}

	printf("\tTerminus >> Comboio %d (%c-%c) >> Partida %s >> Chegada %s\n", 
		c1->numero, c1->origem, c1->destino, departureHour, hora());

	pthread_exit((void*)NULL);
}

//-------------------------------------------------------------------------

int main(){
	pthread_t thread_id[NUM_TRAIN];
	int i;


	//Initialization Arrays
	init_array_mutex();

	for (int i = 0; i < NUM_TRAIN; ++i)
	{
		comboios[i].numero = i;
		comboios[i].origem =  65 + rand()%(NUM_RAIL);
		comboios[i].destino =  65 + rand()%(NUM_RAIL);

		if (comboios[i].origem == comboios[i].destino)
		{
			comboios[i].origem =  'D';
			comboios[i].destino =  'A';
		}
	}


	//Thread Creation
	for (i = 0; i < NUM_TRAIN; i++){
		if (pthread_create(&thread_id[i], NULL, thread_trip_func, &comboios[i]) != 0) error_message("pthread_create");
	}


	//Thread Join
	for (i = 0; i < NUM_TRAIN; i++)
		if (pthread_join(thread_id[i], NULL) != 0) error_message("pthread_join");
		

	//Delete Mutex
	delete_array_mutex();

	return 0;
}
