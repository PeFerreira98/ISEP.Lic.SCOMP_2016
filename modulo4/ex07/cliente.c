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

typedef struct {
	int numBilh;
} bilhete;

int main(){
	//struct timespec ts;
	time_t t;
	
	bilhete *bS1;
	sem_t *sem1, *sem2;
	
	int fd, randTime;
	int dataSize = sizeof(bilhete);
	
	//Semaphore & Memory Management	
	fd = shm_open("/sharedMemory", O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, dataSize);
	bS1 = (bilhete*)mmap(NULL, dataSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	sem1 = sem_open("sAtendedor", O_EXCL, 0644, 0);
	sem2 = sem_open("sCliente", O_EXCL, 0644, 0);


	srand((unsigned) time(&t));
	//ts.tv_sec = rand()%10+1;
	randTime = rand()%10+1;

//Start getting tickets	
	//sem_timedwait(sem1, &ts);
	sem_wait(sem1);
	sleep(randTime);
	printf("Cliente >> %d\n", bS1->numBilh);
	sem_post(sem2);


	return 0;
}
