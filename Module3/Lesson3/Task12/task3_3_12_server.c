#define BUF_SIZE 50

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <mqueue.h>
#include <sys/stat.h>

typedef struct user
{
	mqd_t mqdid;
	char name[BUF_SIZE];
} user;

int read_string(char *s, int width);

int main(int argc, char *argv[]) 
{
	struct mq_attr attr;
	attr.mq_curmsgs = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 50;
	
	mqd_t mqdid = mq_open("/mq_3_1", O_CREAT | O_RDWR, 0777, &attr);
	if (mqdid == (mqd_t) - 1)
	{
		perror("Server - (1) mq_open()");
		exit(EXIT_FAILURE);
	}

	user* users = malloc(16 * sizeof * users);
	for(int i = 0; i <= 15; i++)
	{
		char mq_name[BUF_SIZE] = {0};
		char mq_name_part[4]= {0};
		
		sprintf(mq_name_part, "%d", i + 2);
			
		strcat(mq_name, "/mq_3_");
		strcat(mq_name, mq_name_part);
		
		users[i].mqdid = mq_open(mq_name, O_CREAT | O_RDWR, 0777, &attr);
		if (users[i].mqdid == (mqd_t) - 1) 
		{
			perror("Server - (2) mq_open()");
			exit(EXIT_FAILURE);
		}
	}
	
	unsigned prio;
	
	while(1)
	{	
		mq_getattr(mqdid, &attr);
		char buf[attr.mq_msgsize];
		if (mq_receive(mqdid, buf, sizeof(buf), &prio) == -1) 
		{
			perror("Server - (1) mq_receive()");
			exit(EXIT_FAILURE);
		}
	
		if(prio == 1)
		{
			for(int i = 0; i <= 15; i++)
			{
				if (mq_close(users[i].mqdid) == -1) 
				{
					perror("Server - (1) mq_close()");
					exit(EXIT_FAILURE);
				}
			}
			
			free(users);
			if (mq_close(mqdid) == -1) 
			{
				perror("Server - (2) mq_close()");
				exit(EXIT_FAILURE);
			}
			
			exit(EXIT_SUCCESS);
		}
		else if(prio >= 2 && prio <= 17)
		{
			strcpy(users[prio - 2].name, buf);
		}
		else if(prio == 18 && prio <= 33)
		{
			char buf_send[BUF_SIZE] = {0};
			strcat(buf_send, users[prio - 18].name);
			strcat(buf_send, ": ");
			strcat(buf_send, buf);
			
			for(int i = 0; i <= 15; i++)
			{
				if(i == prio - 18)
					continue;
				
				if (mq_send(users[i].mqdid, buf_send, sizeof(buf_send), 1) == -1)
				{
					perror("Server - (1) mq_send()");
					exit(EXIT_FAILURE);
				}
			}			
		}
	}
}
