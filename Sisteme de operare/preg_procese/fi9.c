#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int fi;
int fo;
int *primit;
int dat;
int stop1 = 1, stop2 = 1;

int main(int argc, char** argv)
{
	//open("fifoi", O_CREAT);
	fi = open("fifoi", O_RDONLY);
	primit = malloc(sizeof(int));
	fo = open("fifoo", O_WRONLY);
	while (stop1 != 0 || stop2 != 0)
	{
		if (stop1 != 0)
		{
			scanf("%d", &dat);
			if (dat != 0)
			{
				printf("Am %d\n", dat);
				write(fo, &dat, sizeof(int));
			}
			else
			{
				close(fo);
				stop1 = 0;
				printf("1 s-a oprit\n");
			}
		}
		if (stop2 != 0)
		{
			if (read(fi, primit, sizeof(int)) > 0)
			{
				printf("am primit %d\n", *primit);
			}
			else
			{
				close(fi);
				stop2 = 0;
				printf("de ce s-a oprit 2?\n");
			}
		}
	}
	free(primit);
	return 0;
}
