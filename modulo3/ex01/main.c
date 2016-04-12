#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>


typedef struct{
	int num;
	int nome;
} shared_data_type;

int main(void){
	
	int fd, data_size = sizeof(shared_data_type);
	shared_data_type *shared_data;
	
	fd = shm_open("/shmex01", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	
	int a = ftruncate(fd, data_size);
	if (a == -1){
		printf("ERRO");
	}
	
	shared_data = (shared_data_type*)mmap(NULL, data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	shared_data->num = 2;
	shared_data->nome = 2;
	
	munmap(shared_data,data_size);
	
	return 0;
}
