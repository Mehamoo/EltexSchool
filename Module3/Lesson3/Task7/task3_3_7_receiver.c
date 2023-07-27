#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>

typedef struct msgbuf 
{
	long mtype;
	char mtext[2];
} msgbuf;

int main() 
{
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
	
	while (1) 
	{
		msgbuf buf;
		if (msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0) == -1) 
		{
			perror("msgrcv()");
			exit(EXIT_FAILURE);
		}
		
		if (buf.mtype == 255) 
			break;
		
		printf("receive: %s\n", buf.mtext);
	}

	if (msgctl(msgid, IPC_RMID, NULL) == -1) 
	{
		perror("msgctl()");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}
