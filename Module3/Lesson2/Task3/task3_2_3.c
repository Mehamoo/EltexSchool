#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]) 
{
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 1\n");
		exit(EXIT_FAILURE);
	}
	
	DIR* pDir;
	struct dirent* data;
	
	if((pDir = opendir(argv[1])) == NULL)
	{
		printf("Error: ошибка при открытии директории\n");
		exit(EXIT_FAILURE);
	}
	
	while ((data = readdir(pDir)) != NULL) 
		printf("%s\n", data->d_name);

	closedir(pDir);
	exit(EXIT_SUCCESS);
}
