// impreuna cu fi7.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int f;
int i,* n, *v;

int main(int argc, char** argv)
{
	f = open("fifo", O_RDONLY);
	n = (int*)malloc(sizeof(int));
	read(f, n, sizeof(int));
	v = (int*)malloc((int)(sizeof(int)) * *n);
	//for (i = 1; i <= *n; i ++)
	//{
	read(f, v, (int)(sizeof(int)) * *n);
	//printf("%d, ", *nr);
	//}
	for (i = 0; i < *n; i ++)
		printf("%d, ", v[i]);
	printf("\n");
	close(f);
	free(v);
	free(n);
	return 0;
}
