#define BUF_SIZE 127

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/msg.h>

int read_string(char *s, int width);

typedef struct msgbuf 
{
	long mtype;
	char mtext[BUF_SIZE];
} msgbuf;

int main(int argc, char *argv[]) 
{
	if(argc != 2)
	{
		printf("Допустимое число аргументов - 1\n");
		exit(EXIT_FAILURE);
	}

	long usr;
	if((usr = (long)atoi(argv[1])) == 0) 
	{
		printf("Невозможно преобразовать аргумент %s в число\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	if(usr != 1 && usr != 2)
	{
		printf("Аргумент может быть равен либо 1, либо 2\n");
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	key_t key = ftok(".", '1');
	if (key == -1) 
	{
		perror("ftok()");
		exit(EXIT_FAILURE);
	}
	
	int msgid = msgget(key, IPC_CREAT | 0660);
	if (msgid == -1) 
	{
		perror("msgget()");
		exit(EXIT_FAILURE);
	}

	

	printf(
		"Меню:\n"
		"1 - отправить сообщение\n"
		"2 - прочитать новые сообщения\n"
		"0 - выйти\n"
	);
		
	while(1)
	{
		char item[2];
		printf(">");
		read_string(item, 2);
		switch(item[0])
		{
			case '1':
			{
				msgbuf buf;
				buf.mtype = usr;
				printf(">>");
				read_string(buf.mtext, BUF_SIZE);
				
				if (msgsnd(msgid, &buf, sizeof(buf.mtext), 0) == -1) 
				{
					perror("msgsnd()");
					exit(EXIT_FAILURE);
				}
				
				break;
			}
			case '2':
			{
				msgbuf buf;
				while (msgrcv(msgid, &buf, sizeof(buf.mtext), usr == 1 ? 2 : 1, IPC_NOWAIT) != -1)
					printf("<< %s", buf.mtext);

				break;
			}
			case '0':
				exit(EXIT_SUCCESS);
		}
	}
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
