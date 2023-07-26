#define FIILE_DIR "/home/EltexSchool/Module3/Lesson3/Task1/file.txt"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
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

	exit(EXIT_SUCCESS);
}
