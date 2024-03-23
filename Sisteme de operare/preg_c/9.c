#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_t t;
pthread_cond_t c;
char cuv[100] = "";
pthread_mutex_t m, ms;
pthread_rwlock_t rw;

void* f(void* arg)
{
	while (strcmp(cuv, "f") != 0)
	{
		pthread_rwlock_wrlock(&rw);
		scanf("%s", cuv);
		pthread_rwlock_unlock(&rw);
		pthread_rwlock_rdlock(&rw);
		printf("Am citit %s\n", cuv);
		if (strcmp(cuv, "stop") == 0)
		{
			pthread_cond_signal(&c);
			pthread_mutex_lock(&ms);
		}
		pthread_rwlock_unlock(&rw);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	
	pthread_mutex_init(&m, NULL);
	pthread_mutex_lock(&m);
	pthread_mutex_init(&ms, NULL);
        pthread_mutex_lock(&ms);
	pthread_rwlock_init(&rw, NULL);
	//pthread_cond_init(&c, &m)
	pthread_create(&t, NULL, f, NULL);
	while (strcmp(cuv, "stop") != 0)
	{
		pthread_cond_wait(&c, &m);
		pthread_mutex_unlock(&ms);
	}
	
	printf("Gata\n");
	
	pthread_mutex_unlock(&m);
	
	pthread_join(t, NULL);
	
	pthread_mutex_destroy(&m);
	pthread_rwlock_destroy(&rw);
	
	return 0;
}
