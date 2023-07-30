#define BUF_SIZE 127

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
	if(argc != 3)
	{
		printf("Допустимое число аргументов - 2\n");
		exit(EXIT_FAILURE);
	}

	long usr;
	if((usr = (long)atoi(argv[1])) == 0) 
	{
		printf("Невозможно преобразовать аргумент %s в число\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if(usr < 1 || usr > 17)
	{
		printf("Допустимые значения первого аргумента от 1 до 17\n");
		exit(EXIT_FAILURE);
	}
	
	key_t key = ftok("file", '1');
	if (key == -1) 
	{
		perror("ftok()");
		exit(EXIT_FAILURE);
	}
	
	int msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1) 
	{
		perror("msgget()");
		exit(EXIT_FAILURE);
	}
	
	char usrName[BUF_SIZE];
	strcpy(usrName, argv[2]);
	msgbuf bufUsr;
	bufUsr.mtype = usr;
	strcpy(bufUsr.mtext, usrName);	
	if (msgsnd(msgid, &bufUsr, sizeof(bufUsr.mtext), 0) == -1) 
	{
		perror("msgsnd()");
		exit(EXIT_FAILURE);
	}
	
	if(usr == 1)
		exit(EXIT_SUCCESS);
	
	
				
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
				buf.mtype = usr + 16;
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
				while (msgrcv(msgid, &buf, sizeof(buf.mtext), 34, IPC_NOWAIT) != -1)
					printf("%s\n", buf.mtext);
				
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
