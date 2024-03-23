#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long n = 0;
pthread_t t[100000];
pthread_mutex_t m;

void* f(void* arg)
{
	int i;
	pthread_mutex_lock(&m);
	for (i = 1; i <= 10000; i ++)
		n ++;
	pthread_mutex_unlock(&m);
	return NULL;
}


int main(int argc, char** argv)
{
	pthread_mutex_init(&m, NULL);
	int i;
	for (i = 1; i <= atoi(argv[1]); i ++)
		pthread_create(&t[i], NULL, f, NULL);

	for (i = 1; i <= atoi(argv[1]); i ++)
                pthread_join(t[i], NULL);
	printf("%lld\n", n);
	pthread_mutex_destroy(&m);
	
	return 0;
}
