#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <Windows.h>
#include "thread_pool.h"

void *print(void *arg)
{
	printf("thead:%ld i=%d\n", pthread_self(), *(int *) arg);
	Sleep(2);
	return NULL;
}

int main()
{
	int i;
	thread_pool *pool = thread_pool_create(2);
	for (i = 0; i < 3; i++)
	{
		thread_pool_add_task(pool, print, &i);
	}

	printf("Main thread...\n");
	getchar();
	return 0;
}