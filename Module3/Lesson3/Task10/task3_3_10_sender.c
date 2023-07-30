#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <mqueue.h>

int getRandInt(const int min, const int max)
{
	return rand() % (max - min + 1) + min;
}

int main() 
{
	srand(time(NULL));

	mqd_t mqdid = mq_open("/mq_1", O_CREAT | O_WRONLY, 0660, NULL);
	if (mqdid == -1) 
	{
		perror("mq_open()");
		exit(EXIT_FAILURE);
	}

	for(unsigned i = 0; i < 5; i++)
	{
		int num =  getRandInt(0, 9);

		char buf[2];
		buf[0] = num + '0';
		buf[1] = '\0';
		
		if (mq_send(mqdid, buf, sizeof(buf), 2) == -1)
		{
			perror("mq_send()");
			exit(EXIT_FAILURE);
		}
		printf("send: %d\n", num);
	}
	
	char buf[2];
	if (mq_send(mqdid, buf, sizeof(buf), 1) == -1)
	{
		perror("mq_send()");
		exit(EXIT_FAILURE);
	}
		
	if (mq_close(mqdid) == -1) 
	{
		perror("mq_close()");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}
