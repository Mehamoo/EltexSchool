#define BUF_SIZE 127

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <mqueue.h>

int read_string(char *s, int width);

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
	
	mqd_t mqdid_1 = mq_open("/mq_2_1", O_CREAT | O_RDWR, 0660, NULL);
	if (mqdid_1 == -1) 
	{
		perror("mq_open()");
		exit(EXIT_FAILURE);
	}

	mqd_t mqdid_2 = mq_open("/mq_2_1", O_CREAT | O_RDWR, 0660, NULL);
	if (mqdid_2 == -1) 
	{
		perror("mq_open()");
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
				char buf[BUF_SIZE];
				
				printf(">>");
				read_string(buf, BUF_SIZE);
				
				if (mq_send(usr == 1 ? mqdid_2 : mqdid_1, buf, sizeof(buf), 1) == -1)
				{
					perror("mq_send()");
					exit(EXIT_FAILURE);
				}
				
				break;
			}
			case '2':
			{
				
				unsigned prio;
				struct mq_attr attr;
				mq_getattr(usr == 1 ? mqdid_1 : mqdid_2, &attr);

				while (attr.mq_curmsgs > 0) 
				{
					char buf[attr.mq_msgsize];
					if (mq_receive(usr == 1 ? mqdid_1 : mqdid_2, buf, sizeof(buf), &prio) == -1) 
					{
						perror("mq_receive()");
						exit(EXIT_FAILURE);
					}
					printf("<< %s", buf);
					mq_getattr(usr == 1 ? mqdid_1 : mqdid_2, &attr);
				}
	
				break;
			}
			case '0':
			{
				if (mq_close(mqdid_1) == -1) 
				{
					perror("mq_close()");
					exit(EXIT_FAILURE);
				}
				
				if (mq_close(mqdid_2) == -1) 
				{
					perror("mq_close()");
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
