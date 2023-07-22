#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void squareCalc(int* mas, int size)
{
	for(int i = 0; i < size; i++)
		printf("сторона: %d\t квадрат: %d\n", mas[i], mas[i] * mas[i]);
}

void freeMas(int* child_mas, int* parent_mas)
{
	free(child_mas);
	free(parent_mas);
}

int main(int argc, char *argv[])
{	
	int n; // Количество конвертируемых в число int аргументов
	for(int i = 1; i < argc; i++)
		if(atoi(argv[i]) > 0) 
			n++;

	if(n == 0)
	{
		printf("Вычислять нечего\n");
		exit(EXIT_FAILURE);
	}
	
	// Массивы со сторонами квадратов для дочернего и родительского процессов
	int *child_mas = (int*)malloc((int) (n / 2) * sizeof(int)); 
	int *parent_mas = (int*)malloc((n % 2 == 0 ? n / 2 : (int) (n / 2) + 1) * sizeof(int));
	
	for(int i = 1, j = 0, tmp; i < argc; i++) // j - итератор для конвертируемых в число int аргументов
		if((tmp = atoi(argv[i])) > 0)
			(j < (int) (n / 2)) ? (child_mas[j++] = tmp) : (parent_mas[j++ - (int) (n / 2)] = tmp);
	
	if(n > 1)
	{
		pid_t pid;
		int rv;
		
		switch(pid = fork()) 
		{
			case -1:
			{
				perror("fork");
				freeMas(child_mas, parent_mas);
				exit(EXIT_FAILURE);
			}
			case 0:
			{
				printf("CHILD:\n");
				squareCalc(child_mas, (int) (n / 2));	
				exit(EXIT_SUCCESS);
			}
			default:
			{
				printf("PARENT:\n");
				squareCalc(parent_mas, n % 2 == 0 ? n / 2 : (int) (n / 2) + 1);
				wait(&rv);
			}
		}
	}
	else
	{
		printf("PARENT:\n");
		squareCalc(parent_mas, 1);
	}
	
	freeMas(child_mas, parent_mas);
	exit(EXIT_SUCCESS);
}
