#include <stdio.h>
#include <pthread.h>

void* f(void* arg)
{
	printf("ceva ");
	
	return NULL;
}

pthread_t t;

int main(int argc, char** argv)
{
	
	pthread_create(&t, NULL, f, NULL);
	
	pthread_join(t, NULL);
	
	return 0;
}
