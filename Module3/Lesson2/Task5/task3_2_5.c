#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

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
	{
		struct stat st;
		char fileDir[strlen(argv[1]) + strlen(data->d_name) + 2];
		
		strcpy(fileDir, argv[1]);
		strcat(fileDir, "/");
		strcat(fileDir, data->d_name);
		strcat(fileDir, "\0");

		if (stat(fileDir, &st) == -1) 
		{
			printf("Error: ошибка при определении статуса файла\n");
			exit(EXIT_FAILURE);
		}
		
		if (S_ISLNK(st.st_mode))
			printf("символьная ссылка\t\t");
		else if (S_ISREG(st.st_mode))
			printf("файл\t\t");
		else if (S_ISDIR(st.st_mode))
			printf("каталог\t\t");
		else if (S_ISCHR(st.st_mode))
			printf("символьное устройство\t\t");
		else if (S_ISBLK(st.st_mode))
			printf("блочное устройство\t\t");
		else if (S_ISFIFO(st.st_mode))
			printf("канал FIFO\t\t");
		else if (S_ISSOCK(st.st_mode))
			printf("сокет\t\t");
			
		printf("%s\n", data->d_name);
	}
	
	closedir(pDir);
	exit(EXIT_SUCCESS);
}
