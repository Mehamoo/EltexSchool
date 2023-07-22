#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 1\n");
		exit(EXIT_FAILURE);
	}
	
	int file;
	if((file = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Error: ошибка при открытии файла\n");
		exit(EXIT_FAILURE);
	}
	
	int size = lseek(file, 0, SEEK_END);
	lseek(file, 0, SEEK_SET);

	char* text = (char*)malloc(sizeof(char) * size);
	read(file, text, size);
	puts(text);

	close(file); 
	exit(EXIT_SUCCESS);
}
