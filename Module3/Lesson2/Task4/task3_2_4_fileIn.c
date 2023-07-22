#define MAX_LEN 127
#define FILE_DIR "/home/EltexSchool/Module3/Lesson2/Task4/"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

bool fileCheck(char* fileName);
void fileCreate(char* fileName);
void fileIn(char* fileName);
int read_string(char *s, int width);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 1\n");
		exit(EXIT_FAILURE);
	}
	
	bool res = fileCheck(argv[1]);
	char fileFullName[MAX_LEN];
	snprintf(fileFullName, sizeof fileFullName, "%s%s", FILE_DIR, argv[1]);
	if(!res)
		fileCreate(fileFullName);
	
	printf(
		"Меню:\n"
		"1 - ввести строку для записи\n"
		"0 - выйти\n"
	);
		
	while(1)
	{
		char item[MAX_LEN];
		printf(">");
		read_string(item, MAX_LEN);
		switch(item[0])
		{
			case '1':
			{
				fileIn(fileFullName);
				break;
			}
			case '0':
				exit(EXIT_SUCCESS);
		}
	}
}

bool fileCheck(char* fileName)
{
	DIR* pDir;
	struct dirent* data;
	
	if((pDir = opendir(".")) == NULL)
	{
		printf("Error: ошибка при открытии директории\n");
		exit(EXIT_FAILURE);
	}

	while ((data = readdir(pDir)) != NULL)
	{
		if(strcmp(data->d_name, fileName) == 0)
		{
			closedir(pDir);
			return true;
		}
	}
	closedir(pDir);
	return false;
}

void fileCreate(char* fileName)
{
	printf(
	"Файл %s отсутствует. Желаете создать его?\n"
	"1 - да, 0 - нет, выйти\n", 
	fileName);
	
	char item[MAX_LEN];
	while(1)
	{
		printf(">");
		read_string(item, MAX_LEN);
		switch(item[0])
		{
			case '1':
			{
				FILE* pFile;
				if((pFile = fopen(fileName, "w")) == NULL)
				{
					printf("Error: ошибка при создании файла\n");
					exit(EXIT_FAILURE);
				}
				fclose(pFile);
				return;
			}
			case '0':
				exit(EXIT_SUCCESS);
		}
	}
}

void fileIn(char* fileName)
{
	char s[MAX_LEN];
	printf("Строка: ");
	int strLen = read_string(s, MAX_LEN - 1);	

	FILE* pFile;
	if((pFile = fopen(fileName, "a+")) == NULL)
	{
		printf("Error: ошибка при открытии файла\n");
		exit(EXIT_FAILURE);
	}
	fwrite(s, sizeof(char), strLen, pFile);
	fclose(pFile);
}

int read_string(char *s, int width)
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
	
	return strlen(s);
}
