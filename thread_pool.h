#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <pthread.h>
#include "queue.h"

typedef struct
{
	size_t thread_count;
	pthread_t *threads;
	queue *tasks;
	pthread_mutex_t lock;
	pthread_cond_t task_ready;
} thread_pool;

typedef struct
{
	void *(*routin)(void *arg);
	void *arg;
} task;

thread_pool *thread_pool_create(size_t thread_count);

void thread_pool_add_task(thread_pool *pool, void *(*routin)(void *arg), void *arg);

void thread_pool_destroy(thread_pool *pool);

void *worker_thread(void *arg);

#endif