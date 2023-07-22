#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printArgs(int argc, char *argv[])
{
	for(short i=0; i<argc; i++)
		printf("%d: %s\n", i, argv[i]);
}

void printExit()
{
	printf("Successful exit...\n");
}

int main(int argc, char *argv[])
{
	if (atexit(printExit))
		printf("Failure exit...\n");
		
	pid_t pid;
	int rv;
	
	switch(pid = fork()) 
	{
		case -1:
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		case 0:
		{
			printf("CHILD:\n");
			printArgs(argc, argv);
			exit(EXIT_SUCCESS);
		}
		default:
		{
			printf("PARENT:\n");
			printArgs(argc, argv);
			wait(&rv);
		}
	}
	
	exit(EXIT_SUCCESS);
}
