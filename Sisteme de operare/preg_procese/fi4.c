// impreuna cu fi3.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int f;
int* nr;

int main(int argc, char** argv)
{
	f = open("fifo", O_RDONLY);
	nr = (int*)malloc(sizeof(int));
	read(f, nr, sizeof(int));
	printf("%d\n", *nr);
	free(nr);
	close(f);
	return 0;
}
