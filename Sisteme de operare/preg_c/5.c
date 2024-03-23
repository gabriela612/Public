#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


pthread_t t1, t2;
pthread_mutex_t m1, m2;

void* f1(void* arg)
{
	printf("f1 - incerc m1\n");
	pthread_mutex_lock(&m1);
	printf("f1 - am m1\n");
	printf("f1 - dau drumul la m2\n");
	pthread_mutex_unlock(&m2);
	printf("f1 - am dat drumul la m2\n");
	printf("f1 - dau drumul la m1\n");
	pthread_mutex_unlock(&m1);
	printf("f1 - am dat drumul la m1\n");
	return NULL;
}

void* f2(void* arg)
{
	printf("f2 - dau drumul la m1\n");
	pthread_mutex_unlock(&m1);
	printf("f2 - am dat drumul la m1\n");
	printf("f2 - incerc m2\n");
	pthread_mutex_lock(&m2);
	printf("f2 - am luat m2\n");
	printf("f2 - dau drumul la m2\n");
	pthread_mutex_unlock(&m2);
	printf("f2 - am dat drumul la m2\n");
        return NULL;
}


int main(int argc, char** argv)
{
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	
	pthread_mutex_lock(&m1);
	pthread_mutex_lock(&m2);
	
	pthread_create(&t1, NULL, f1, NULL);
	pthread_create(&t2, NULL, f2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	printf("final\n");
	
	pthread_mutex_destroy(&m1);
	pthread_mutex_destroy(&m2);
	return 0;
}
