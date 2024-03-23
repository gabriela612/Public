#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_rwlock_t m;
int n, nr = 0, i;
pthread_t t[1000];

void* f(void* arg)
{
	int j = 0;
	j = j + 1;
	pthread_rwlock_wrlock(&m);
	nr = nr + j;
	pthread_rwlock_unlock(&m);
	return NULL;
}

int main(int argc, char** argv)
{
	n = atoi(argv[1]);
	pthread_rwlock_init(&m, NULL);
	
	for (i = 1; i <= n; i ++)
	{
		pthread_create(&t[i], NULL, f, NULL);
	}
	
	for (i = 1; i <= n; i ++)
	{
		pthread_join(t[i], NULL);
	}
	
	pthread_rwlock_destroy(&m);
	
	printf("nr : %d\n", nr);
	
	return 0;
}
