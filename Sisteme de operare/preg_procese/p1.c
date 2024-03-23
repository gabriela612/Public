#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int p[2];
int a = 7;
char b = 'a';
char* c = "ceva";

int main(int argc, char** argv)
{
	pipe(p);
	if (fork() == 0)
	{
		close(p[0]);
		a ++;
		b ++;
		c = "merge_foarte_bine";
		write(p[1], &a, sizeof(int));
		write(p[1], &b, sizeof(char));
		write(p[1], &c, sizeof(c));
		a ++;
		write(p[1], &a, sizeof(int));
		close(p[1]);
		exit(0);
	}
	close(p[1]);
	read(p[0], &a, sizeof(int));
	read(p[0], &b, sizeof(char));
        read(p[0], &c, sizeof(c));
	read(p[0], &a, sizeof(int));
	printf("%d\n%c\n%s\n", a, b, c);
	close(p[0]);
	wait(0);
	return 0;
}


