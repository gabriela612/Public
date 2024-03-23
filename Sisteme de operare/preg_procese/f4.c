#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int n, i;

int main(int argc, char** argv)
{
	n = atoi(argv[1]);
	for (i = 1; i <= n; i ++)
	{
		if (fork() != 0)
		{
			wait(0);
			break;
		}
		else
			printf("pid: %d, ppid: %d\n", getpid(), getppid());
	}
	
	return 0;
}
