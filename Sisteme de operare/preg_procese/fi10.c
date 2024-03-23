#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int fi, fo;
int *primit;
int dat;
int stop1 = 1, stop2 = 1;

int main(int argc, char** argv)
{
        primit = (int*)malloc(sizeof(int));
        fo = open("fifoi", O_WRONLY);
	fi = open("fifoo", O_RDONLY);
        while (stop1 != 0 || stop2 != 0)
        {
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
                                printf("de ce s-a oprit 1?\n");
                        }
                }
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
                                printf("2 s-a oprit\n");
                        }
                }
        }
        free(primit);
	return 0;
}
