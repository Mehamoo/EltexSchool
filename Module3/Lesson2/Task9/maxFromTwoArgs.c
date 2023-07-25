#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{	
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 2\n");
		exit(EXIT_FAILURE);
	}

	int n1, n2;

	if((n1 = atoi(argv[0])) == 0) 
	{
		printf("Невозможно преобразовать аргумент %s в число\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	if((n2 = atoi(argv[1])) == 0) 
	{
		printf("Невозможно преобразовать аргумент %s в число\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	printf("Максимальное среди %d и %d - %d\n", n1, n2, n1 > n2 ? n1 : n2);
	exit(EXIT_SUCCESS);
}
