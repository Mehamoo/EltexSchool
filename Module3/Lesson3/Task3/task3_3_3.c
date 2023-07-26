#define FIILE_DIR "/home/EltexSchool/Module3/Lesson3/Task3/file.txt"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void SIGIGT_listener()
{
	static short i = 1;
	if (i++ == 3)
		exit(EXIT_SUCCESS);
}

int main()
{
	signal(SIGINT, SIGIGT_listener);

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
