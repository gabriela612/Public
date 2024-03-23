#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t t[5];
int j;
void* rez1 = NULL;
void* rez2 = NULL;
void* r;
int ceva;

void* f(void* arg)
{
	*((int*)(r)) = 1;
	return r;
}

int main(int argc, char** argv)
{
	//r = malloc(sizeof(int)); - var1
	r = &ceva; // - var2
	for (j = 0; j <= 1; j ++)
	{
		pthread_create(&t[j], NULL, f, NULL);
	}
	pthread_join(t[0], &rez1);
	pthread_join(t[1], &rez2);
	printf("%d %d\n", *((int*)(rez1)), *((int*)(rez2)));
	return 0;
}
