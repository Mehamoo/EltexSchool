#define MAX_LEN 255
#define MAX_LEN_IN 31

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void read_string(char *s, int width);

int main(int argc, char* argv[]) 
{
	char dir[MAX_LEN] = "/";
	DIR* pDir;
	struct dirent* data;
	
	while(1)
	{
		printf("Текущий каталог: %s\n\n", dir);
	
		if((pDir = opendir(dir)) == NULL)
		{
			printf("Error: ошибка при открытии директории\n");
		}
		else
		{	
			while ((data = readdir(pDir)) != NULL) 
			{
				struct stat st;
				char fileDir[strlen(dir) + strlen(data->d_name) + 2];
				
				strcpy(fileDir, dir);
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
		}		
		printf(
			"\nДействия:\n"
			"1 - перейти к следующему каталогу\n"
			"2 - вернуться на каталог назад\n"
			"0 - выйти\n"
		);		
				
		char strIn[MAX_LEN_IN];
		bool leave = false;
		while(1)
		{
			char item[MAX_LEN_IN];
			printf(">");
			read_string(item, MAX_LEN);
			switch(item[0])
			{
				case '1':
				{
					printf("Каталог: ");
					read_string(strIn, MAX_LEN_IN);
					strcat(dir, strIn);
					strcat(dir, "/");
					
					leave = true;
					break;
				}
				case '2':
				{
					if(dir[1] == '\0')
						break;
						
					int i = strlen(dir);
					dir[--i] = '\0';
					char *pChar = strrchr(dir, 47);
					for(;; i--)
						if(&dir[i] != pChar)
							dir[i] = '\0';
						else
							break;
							
					leave = true;
					break;
				}
				case '0':
					exit(EXIT_SUCCESS);
			}
			
			if(leave)
				break;
		}
		
		closedir(pDir);
	}
}

void read_string(char *s, int width)
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
	
	s[strlen(s) - 1] = '\0';
}
