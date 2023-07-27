#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/msg.h>

int getRandInt(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}

typedef struct msgbuf 
{
	long mtype;
	char mtext[2];
} msgbuf;

int main() 
{
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

	for(int i = 0; i < 5; i++)
	{
		int num =  getRandInt(0, 9);
		printf("send: %d\n", num);
		
		msgbuf buf = {1, num + '0'};
		if (msgsnd(msgid, &buf, sizeof(buf.mtext), 0) == -1) 
		{
			perror("msgsnd()");
			exit(EXIT_FAILURE);
		}
	}
	
	msgbuf buf = {255, '0'};
	if (msgsnd(msgid, &buf, sizeof(buf.mtext), 0) == -1) 
	{
		perror("msgsnd()");
		exit(EXIT_FAILURE);
	}
}
