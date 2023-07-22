#define MAX_LEN 127
#define DIR "/usr/bin/"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void read_string(char *s, int width)
{
	if (fgets(s, width, stdin) != 0)
	{
		size_t length = strlen(s);
		if (length > 0 && s[length-1] != '\n')
		{
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
	
	s[strlen(s) - 1] = '\0';
}

void free_mas(char** mas, int size)
{
	if(size != 0)
	{
		for(int i = 0; i < size; i++)
			free(mas[i]);
		free(mas);
	}
}

int main(int argc, char *argv[])
{	
	char programFullName[MAX_LEN * MAX_LEN], programName[MAX_LEN], tmpArg[MAX_LEN];
	char** Args;	
	int ArgsSize;
	
	printf("Program: ");
	read_string(programName, MAX_LEN);
	snprintf(programFullName, sizeof programFullName, "%s%s", DIR, programName);
	
	ArgsSize = 0;
	Args = (char**)malloc(ArgsSize);
	if (Args == NULL)
	{
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Args (write \";\" to stop):\n");
	for(int i = 0;;i++)
	{
		printf("%d: ", i);
		
		read_string(tmpArg, MAX_LEN);
			
		char** tmpArgs = (char**)realloc(Args, ++ArgsSize * sizeof(char*));
		if (tmpArgs == NULL)
		{
			printf("Memory allocation error\n");
			free(Args);
			exit(EXIT_FAILURE);
		}
		else
		{
			Args = tmpArgs;
		}
		
		Args[i] = (char *)malloc(sizeof(char) * (strlen(tmpArg) + 1)); 
		if (Args[i] == NULL)
		{
			printf("Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
	
		if(tmpArg[0] == ';')
		{
			Args[i] = (char*)0;
			break;
		}
		strcpy(Args[i], tmpArg);
	}

	pid_t pid;
	int rv;
	
	switch(pid = fork()) 
	{
		case -1:
		{
			perror("fork");
			free_mas(Args, ArgsSize);
			exit(EXIT_FAILURE);
		}
		case 0:
		{
			if(execv(programFullName, Args) == -1)
			{
				printf("Error: %s\n", strerror(errno));	
				free_mas(Args, ArgsSize);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		default:
		{
			wait(&rv);
		}
	}
	
	free_mas(Args, ArgsSize);
	exit(EXIT_SUCCESS);
}
