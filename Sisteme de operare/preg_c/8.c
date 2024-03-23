#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

char s[100] = "";
pthread_t t1, t2, t3;
pthread_rwlock_t m;
pthread_mutex_t mu;

void* f1(void* arg)
{
	char a[100];
	while (strcmp(s, "STOP") != 0)
	{
		pthread_mutex_lock(&mu);
		printf("Introduceti cuvantul : ");
		scanf("%s", a);
		printf("\n");
		pthread_mutex_unlock(&mu);
		pthread_rwlock_wrlock(&m);
		strcpy(s, a);
		pthread_rwlock_unlock(&m);
	}
	return NULL;
}

void* f2(void* arg)
{
	char a[100] = "", nou[100];
	while (strcmp(a, "STOP") != 0)
	{
		pthread_rwlock_rdlock(&m);
		strcpy(nou, s);
		pthread_rwlock_unlock(&m);
		if (strcmp(nou, a) != 0)
		{
			//pthread_mutex_lock(&mu);
			printf("\nAm primit : %s\n", nou);
			//pthread_mutex_unlock(&mu);
			strcpy(a, nou);
		}
	}
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_rwlock_init(&m, NULL);
	
	pthread_mutex_init(&mu, NULL);
	
	pthread_create(&t1, NULL, f1, NULL);
	pthread_create(&t2, NULL, f2, NULL);
	pthread_create(&t3, NULL, f2, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	
	pthread_mutex_destroy(&mu);
	
	pthread_rwlock_destroy(&m);
	
	return 0;
}
