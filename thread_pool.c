#include "thread_pool.h"

#include <stdlib.h>

thread_pool *thread_pool_create(size_t thread_count)
{
	int i;
	thread_pool *pool = (thread_pool *) malloc(sizeof(thread_pool));
	pool->threads = (pthread_t *) malloc(sizeof(pthread_t) * thread_count);
	pthread_mutex_init(&pool->lock, NULL);
	pthread_cond_init(&pool->task_ready, NULL);
	pool->tasks = queue_create(thread_count);
	for (i = 0; i < thread_count; i++)
	{
		pthread_create(&pool->threads[i], NULL, worker_thread, pool);
	}
	return pool;
}

void thread_pool_add_task(thread_pool *pool, void *(*routin)(void *arg), void *arg)
{
	task *t;
	pthread_mutex_lock(&pool->lock);
	t = (task *) malloc(sizeof(task));
	t->routin = routin;
	t->arg = arg;
	enqueue(pool->tasks, t);
	pthread_cond_signal(&pool->task_ready);
	pthread_mutex_unlock(&pool->lock);
}

void *worker_thread(void *arg)
{
	task *t;
	thread_pool *pool = (thread_pool *) arg;
	while (1)
	{
		pthread_mutex_lock(&pool->lock);
		while (is_empty(pool->tasks))
		{
			pthread_cond_wait(&pool->task_ready, &pool->lock);
		}
		t = (task *) dequeue(pool->tasks);
		pthread_mutex_unlock(&pool->lock);
		t->routin(arg);
		free(t);
	}
	return NULL;
}

void thread_pool_destroy(thread_pool *pool)
{

}