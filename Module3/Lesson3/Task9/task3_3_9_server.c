#define BUF_SIZE 127

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

int read_string(char *s, int width);

typedef struct msgbuf 
{
	long mtype;
	char mtext[BUF_SIZE];
} msgbuf;

typedef struct user
{
	char name[BUF_SIZE];
} user;


int main(int argc, char *argv[]) 
{
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

	user* users = malloc(16 * sizeof * users);
	
	while(1)
	{	
		for(int i = 1; i <= 33; i++)
		{	
			msgbuf buf;	
			if(msgrcv(msgid, &buf, sizeof(buf.mtext), i, IPC_NOWAIT) == -1)
				continue;
			
			if(buf.mtype == 1)
			{
				free(users);
				
				 if (msgctl(msgid, IPC_RMID, NULL) == -1) 
				 {
					perror("msgctl()");
					exit(EXIT_FAILURE);
				 }
				
				exit(EXIT_SUCCESS);
			}
			else if(buf.mtype >= 2 && buf.mtype <= 17)
				strcpy(users[buf.mtype - 2].name, buf.mtext);
			else if (buf.mtype >= 18 && buf.mtype <= 33)
			{
				msgbuf bufSend;
				bufSend.mtype = 34;
				strcat(bufSend.mtext, users[buf.mtype - 18].name);
				strcat(bufSend.mtext, ": ");
				strcat(bufSend.mtext, buf.mtext);
				if (msgsnd(msgid, &bufSend, sizeof(bufSend.mtext), 0) == -1) 
				{
					perror("msgsnd()");
					exit(EXIT_FAILURE);
				}
			}
			sleep(1);
		}
	}
}
