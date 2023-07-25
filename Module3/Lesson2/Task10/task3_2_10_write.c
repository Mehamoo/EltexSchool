#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int getRandInt(const int min, const int max);

int main()
{
	unlink("fifo");
	if((mkfifo("fifo", 0666)) == -1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	
	int fd_fifo;
	if((fd_fifo = open("fifo", O_RDWR)) == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	
	while(1)
	{
		int num = getRandInt(0, 9);
		write(fd_fifo, &num, sizeof(int));
		printf("write: %d\n", num);	
		sleep(10);
	}
		
	exit(EXIT_SUCCESS);
}

int getRandInt(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}
