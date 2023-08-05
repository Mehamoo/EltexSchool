#define MAX_ARGS 4
#define MAX_LEN 128
#define DIR "/usr/bin/"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct program
{
	char programName[MAX_LEN];
	char* args[128];
	int numArgs;
} program;

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

int main(int argc, char *argv[])
{	
	int numPrograms = 2;
	program* programs = (program*)malloc(numPrograms * sizeof(program));
	if(programs = NULL)
	{
		perror("(1) malloc()");
		exit(EXIT_FAILURE);
	}
	
	char strIn[MAX_LEN];
	printf(">");
	read_string(strIn, MAX_LEN);
	
	char tmpC;
	bool newProgram = true;
	for(int i = 0; i < strlen(strIn);)
	{
		char tmpStr[MAX_LEN] = {0};
		char* p = tmpStr;
		int j;
		for(j = 0;;)
		{
			tmpC = strIn[i++];
			if(tmpC == ' ' || tmpC == '\0')
				break;
			tmpStr[j++] = tmpC;
		}
		tmpStr[j] = '\0';
		
		if(j == 1 && tmpStr[0] == '|')
		{
			newProgram = true;
			numPrograms++;
			continue;
		}
		
		if(newProgram)
		{
			if(numPrograms != 1)
			{
				program* tmpPrograms = realloc(programs, numPrograms * sizeof(program));
				if (tmpPrograms == NULL)
				{
					perror("(1) realloc()");
					exit(EXIT_FAILURE);
				}
				else
					programs = tmpPrograms;
			}
			
			programs[numPrograms - 1].numArgs = 0;
			strcpy(programs[numPrograms - 1].programName, DIR);
			strcat(programs[numPrograms - 1].programName, tmpStr);
			
			++programs[numPrograms - 1].numArgs;
			programs[numPrograms - 1].args[programs[numPrograms - 1].numArgs - 1] = (char *) malloc(MAX_LEN);
			strncpy(programs[numPrograms - 1].args[programs[numPrograms - 1].numArgs - 1], programs[numPrograms - 1].programName, MAX_LEN);
			
			newProgram = false;
		}
		else
		{
			if(++programs[numPrograms - 1].numArgs == MAX_ARGS + 1)
			{
				printf("Максимальное количество аргументов - %d\n", MAX_ARGS);
				exit(EXIT_FAILURE);
			}
			
			programs[numPrograms - 1].args[programs[numPrograms - 1].numArgs - 1] = (char *) malloc(MAX_LEN);
			strncpy(programs[numPrograms - 1].args[programs[numPrograms - 1].numArgs - 1], p, MAX_LEN);
		}
	}

	for(int i = 1; i < numPrograms; i++)
	{
		programs[i].numArgs++;
		programs[i].args[programs[i].numArgs - 1] = (char*)0;
	}

	int pipeFd1[2], pipeFd2[2];

	if (pipe(pipeFd1) == -1) 
	{
		perror("(1) pipe()");
		exit(EXIT_FAILURE);
	} 

	if (pipe(pipeFd2) == -1) 
	{
		perror("(2) pipe()");
		exit(EXIT_FAILURE);
	} 

	pid_t pid, pid1;
	int rv, rv1;

	switch (pid = fork()) 
	{
		case -1:
		{
			perror("(1) fork()");
			exit(EXIT_FAILURE);
		}
		case 0:
		{
			dup2(pipeFd1[1], 1);

			close(pipeFd1[0]);

			if (execv(programs[1].programName, programs[1].args) == -1) 
			{
				perror("(1) execv()");
				exit(EXIT_FAILURE);
			}
		}
		default:
		{
			wait(&rv);

			switch(pid1 = fork())
			{
				case -1:
				{
					perror("(2) fork()");
					exit(EXIT_FAILURE);
				}
				case 0:
				{
					dup2(pipeFd2[1], 1);	
					dup2(pipeFd1[0], 0);
					
					close(pipeFd1[1]);
					close(pipeFd2[0]);

					if (execv(programs[2].programName, programs[2].args) == -1) 
					{
						perror("(2) execv()");
						exit(EXIT_FAILURE);
					}
					
					exit(EXIT_SUCCESS);
				}
				default:
				{
					wait(&rv1);
					close(pipeFd2[1]);
					close(pipeFd1[0]);
					
					dup2(pipeFd2[0], 0);
					
					if (execv(programs[3].programName, programs[3].args) == -1) 
					{
						perror("(3) execv()");
						exit(EXIT_FAILURE);
					}
				}
			}

		}

		close(pipeFd1[0]);
		close(pipeFd1[1]);
		close(pipeFd2[0]);
		close(pipeFd2[1]);
	}
	
	free(programs);
	exit(EXIT_SUCCESS);
}
