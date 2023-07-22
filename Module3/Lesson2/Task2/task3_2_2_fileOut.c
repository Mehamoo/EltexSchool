#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 1\n");
		exit(EXIT_FAILURE);
	}
	
	FILE* pFile;
	if((pFile = fopen(argv[1], "r")) == NULL)
	{
		printf("Error: ошибка при открытии файла\n");
		exit(EXIT_FAILURE);
	}
	
	fseek(pFile, 0, SEEK_END);
	long size = ftell(pFile);
	rewind(pFile);

	char* text = (char*)malloc(sizeof(char) * size);
	fread(text, sizeof(char), size, pFile);
	puts(text);

	fclose(pFile);
	free(text);
	exit(EXIT_SUCCESS);
}
