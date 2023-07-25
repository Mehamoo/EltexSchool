#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int getRandInt(const int min, const int max);

int main(int argc, char* argv[]) 
{
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 1\n");
		exit(EXIT_FAILURE);
	}
	
	int size;
	if((size = atoi(argv[1])) == 0) 
	{
		printf("Невозможно преобразовать аргумент %s в число\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));

	int pipeFd[2];
	if (pipe(pipeFd) == -1) 
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	switch (pid) 
	{
		case -1:
		{
			perror("fork");
			exit(EXIT_FAILURE);
			break;
		}
		case 0:
		{
			for (int i = 0; i < size; i++) 
			{
				int n = getRandInt(0, 9);
				write(pipeFd[1], &n, sizeof(int));
			}	
			close(pipeFd[1]);
			exit(EXIT_SUCCESS);
			break;
		}
		default:
		{
			int n[size];
			for (int i = 0; i < size; i++)
			{
				read(pipeFd[0], &n[i], sizeof(int));
				printf("%d\n", n[i]);
			}
			close(pipeFd[0]);

			FILE* pFile;
			if ((pFile = fopen("output.txt", "a+")) == NULL) 
			{
				perror("fopen");
				exit(EXIT_FAILURE);
			}
			
			char c;
			for (int i = 0; i < size; i++) 
			{
				c = n[i] + '0';
				fwrite(&c, sizeof(char), 1, pFile);
				c = '\n';
				fwrite(&c, sizeof(char), 1, pFile);
			}
			
			fclose(pFile);
			exit(EXIT_SUCCESS);
			break;
		}
	}
}

int getRandInt(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}
