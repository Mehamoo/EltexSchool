#define MAX_LEN 127

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void fileIn(char* fileDir);
int read_string(char *s, int width);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 1\n");
		exit(EXIT_FAILURE);
	}
	
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
				fileIn(argv[1]);
				break;
			}
			case '0':
				exit(EXIT_SUCCESS);
		}
	}
}

void fileIn(char* fileDir)
{
	char s[MAX_LEN];
	printf("Строка: ");
	int strLen = read_string(s, MAX_LEN - 1);	

	FILE* pFile;
	if((pFile = fopen(fileDir, "a+")) == NULL)
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
