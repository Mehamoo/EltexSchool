#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid_1, pid_2;
	uid_t uid;
	gid_t gid;
	
	pid_1 = getpid();
	printf("pid = getpid(): %d\n", pid_1);
	pid_2 = getppid();
	printf("getppid(): %d\n", pid_2);
	uid = getuid();
	printf("getuid(): %d\n", uid);
	uid = geteuid();
	printf("geteuid(): %d\n", uid);
	gid = getgid();
	printf("getgid(): %d\n", gid);
	pid_2 = getsid(pid_1);
	printf("getsid(pid): %d\n", pid_2);
	
	return 0;
}
