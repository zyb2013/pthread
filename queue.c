
#include <stdlib.h>

#include "queue.h"

queue *queue_create(size_t max_size)
{
	queue *q = (queue *) malloc(sizeof(queue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	q->max_size = max_size;
	return q;
}

void queue_destroy(queue *q)
{
	while (q->head != NULL)
	{
		node *tmp = q->head->next;
		free(q->head);
		q->head = tmp;
		q->size--;
	}
	q->max_size = 0;
}

void enqueue(queue *q, void *elem)
{
	node *pNode = (node *) malloc(sizeof(node));
	pNode->element = elem;
	if (q->head == NULL)
	{
		q->head = q->tail = pNode;
	}
	q->tail->next = pNode;
	q->tail = pNode;
	pNode->next = NULL;
	q->size++;
}

void *dequeue(queue *q)
{
	node *tmp = q->head->next;
	void *elem = q->head->element;
	free(q->head);
	q->head = tmp;
	q->size--;
	return elem;
}

size_t size(queue *q)
{
	return q->size;
}

int is_full(queue *q)
{
	return q->size == q->max_size;
}

int is_empty(queue *q)
{
	return q->size == 0;
}