#define FIILE_DIR "/home/EltexSchool/Module3/Lesson3/Task4/file.txt"

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

int main()
{
	signal(SIGINT, SIG_listener);
	signal(SIGQUIT, SIG_listener);
	
	FILE* pFile;
	int i = 0;

	while (1) 
	{
		if((pFile = fopen(FIILE_DIR, "a+")) == NULL)
		{
			printf("Error: ошибка при открытии файла\n");
			exit(EXIT_FAILURE);
		}

		fprintf(pFile, "%d\n", i++);

		fclose(pFile);
		sleep(1);
	}
}
