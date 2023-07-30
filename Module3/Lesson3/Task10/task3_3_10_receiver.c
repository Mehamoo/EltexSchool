#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <mqueue.h>

int main() 
{
	mqd_t mqdid = mq_open("/mq_1", O_CREAT | O_RDONLY | O_NONBLOCK, 0660, NULL);
	if (mqdid == -1) 
	{
		perror("mq_open()");
		exit(EXIT_FAILURE);
	}
	
	struct mq_attr attr;
    	mq_getattr(mqdid, &attr);
	
	while (1) 
	{
		char buf[attr.mq_msgsize];
		unsigned prio;
		
		if (mq_receive(mqdid, buf, sizeof(buf), &prio) == -1) 
		{
			perror("mq_receive()");
			exit(EXIT_FAILURE);
		}
	
		if (prio == 1) 
			break;
		
		printf("receive: %s\n", buf);
	}

	if (mq_unlink("/mq_1") == -1) 
	{
		perror("mq_unlink()");
		exit(EXIT_FAILURE);
    	}

	exit(EXIT_SUCCESS);
}
