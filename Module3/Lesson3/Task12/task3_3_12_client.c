#define BUF_SIZE 50

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <mqueue.h>

int read_string(char *s, int width);

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
	
	struct mq_attr attr;
	attr.mq_curmsgs = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 50;
	
	mqd_t mqdid_1 = mq_open("/mq_3_1", O_CREAT | O_RDWR, 0777, &attr);
	if (mqdid_1 == (mqd_t) - 1)
	{
		perror("Client - (1) mq_open()");
		exit(EXIT_FAILURE);
	}
	
	char usrName[BUF_SIZE];
	strcpy(usrName, argv[2]);
	if (mq_send(mqdid_1, usrName, sizeof(usrName), usr) == -1)
	{
		perror("Client - (1) mq_send()");
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
				char buf[BUF_SIZE];
				
				printf(">>");
				read_string(buf, BUF_SIZE);
				
				if (mq_send(mqdid_1, buf, sizeof(buf), usr + 16) == -1)
				{
					perror("Client - (2) mq_send()");
					exit(EXIT_FAILURE);
				}
				
				break;
			}
			case '2':
			{
				char mq_name[BUF_SIZE] = {0};
				char mq_name_part[4]= {0};
				
				sprintf(mq_name_part, "%d", (int)usr);

				strcat(mq_name, "/mq_3_");
				strcat(mq_name, mq_name_part);
				
				mqd_t mqdid_read = mq_open(mq_name, O_CREAT | O_RDWR, 0777, &attr);
				if (mqdid_read == (mqd_t) - 1) 
				{
					perror("Client - (2) mq_open()");
					exit(EXIT_FAILURE);
				}
				
				unsigned prio;
				mq_getattr(mqdid_read, &attr);

				while (attr.mq_curmsgs > 0) 
				{
					char buf[attr.mq_msgsize];
					if (mq_receive(mqdid_read, buf, sizeof(buf), &prio) == -1) 
					{
						perror("Client - (1) mq_receive()");
						exit(EXIT_FAILURE);
					}
					printf("%s\n", buf);
					mq_getattr(mqdid_read, &attr);
				}
				
				if (mq_close(mqdid_read) == -1) 
				{
					perror("Client - (1) mq_close()");
					exit(EXIT_FAILURE);
				}
				break;
			}
			case '0':
			{
				if (mq_close(mqdid_1) == -1) 
				{
					perror("Client - (2) mq_close()");
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
			}
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
