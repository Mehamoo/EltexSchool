#define FIILE_DIR "/home/EltexSchool/Module3/Lesson3/Task5/file.txt"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void SIG_listener(int signal)
{
	printf("Процесс завершился сигналом ");
	signal == 2 ? printf("SIGINT\n") : printf("SIGQUIT\n");
	exit(EXIT_SUCCESS);
}

void setSigListener()
{
	signal(SIGINT, SIG_listener);
	signal(SIGQUIT, SIG_listener);
}

void setSigIGN()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int main()
{
	setSigListener();

	FILE* pFile;
	int i = 0;

	while (1) 
	{	
		
		if((pFile = fopen(FIILE_DIR, "a+")) == NULL)
		{
			printf("Error: ошибка при открытии файла\n");
			exit(EXIT_FAILURE);
		}
		else
			setSigIGN();
			
		fprintf(pFile, "%d\n", i++);
		sleep(1);
		
		fclose(pFile);
		setSigListener();
		sleep(1);
	}
}
