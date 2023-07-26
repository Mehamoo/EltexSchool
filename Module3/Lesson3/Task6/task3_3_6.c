#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <malloc.h>


bool blockFile = false;

void SIGUSR1_listener()
{
	blockFile = true;
} 

void SIGUSR2_listener()
{
	blockFile = false;
} 


int getRandInt(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}

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
	
	FILE* pFile;
	if ((pFile = fopen("output.txt", "w")) == NULL) 
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	fclose(pFile);
	
	srand(time(NULL));
	signal(SIGUSR1, SIGUSR1_listener);
	signal(SIGUSR2, SIGUSR2_listener);
	
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
			char* text = (char*)malloc(sizeof(char) * size * 2);
			
			for (int i = 0; i < size + 1; i++) 
			{
				while(blockFile){}
				
				FILE* pFile;
				if ((pFile = fopen("output.txt", "a+")) == NULL) 
				{
					perror("fopen");
					exit(EXIT_FAILURE);
				}
				
				fseek(pFile, 0, SEEK_END);
				long sizeFile = ftell(pFile);
				rewind(pFile);

				char* text = (char*)malloc(sizeof(char) * sizeFile);
				fread(text, sizeof(char), sizeFile, pFile);
				
				printf("File:\n");
				puts(text);
				
				fclose(pFile);
				
				if(i != size)
				{
					int n = getRandInt(0, 9);
					write(pipeFd[1], &n, sizeof(int));
					sleep(10000);
				}
			}
				
			close(pipeFd[1]);
			free(text);
			exit(EXIT_SUCCESS);
			break;
		}
		default:
		{
			int n[size];
			for (int i = 0; i < size; i++)
			{
				read(pipeFd[0], &n[i], sizeof(int));
				printf("Parent write: %d\n\n", n[i]);
				
				kill(0, SIGUSR1);
				FILE* pFile;
				if ((pFile = fopen("output.txt", "a+")) == NULL) 
				{
					perror("fopen");
					exit(EXIT_FAILURE);
				}
				
				char c;
				c = n[i] + '0';
				fwrite(&c, sizeof(char), 1, pFile);
				c = '\n';
				fwrite(&c, sizeof(char), 1, pFile);
				
				fclose(pFile);
				usleep(10000);
				kill(0, SIGUSR2);
			}
			close(pipeFd[0]);

			exit(EXIT_SUCCESS);
			break;
		}
	}
}
