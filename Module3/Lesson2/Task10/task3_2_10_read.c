#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int getRandInt(const int min, const int max);

int main()
{
	int fd_fifo;
	if((fd_fifo = open("fifo", O_RDWR)) == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	
	while(1)
	{
		int num;
		if(read(fd_fifo, &num, sizeof(int)) == -1)
			perror("read()");
		else
			printf("read: %d\n", num);
	}
	
	exit(EXIT_SUCCESS);
}

int getRandInt(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}
