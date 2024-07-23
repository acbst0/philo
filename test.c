#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void count(void *num)
{
	int *in = (int *)num;
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", *in);
	}
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;

	int a = 0;
	int b = 1;

	pthread_create(&thread1, NULL, count, (void *) &a);
	pthread_join(thread1, NULL);
	pthread_create(&thread2, NULL, count, (void *) &b);
	pthread_join(thread2, NULL);
}