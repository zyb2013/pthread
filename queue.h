#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct node_tag
{
	void *element;
	struct node_tag *next;
} node;

typedef struct
{
	size_t size;
	size_t max_size;
	node *head;
	node *tail;
} queue;

queue *queue_create(size_t max_size);

void queue_destroy(queue *q);

void enqueue(queue *q, void *elem);

void *dequeue(queue *q);

size_t size(queue *q);

int is_full(queue *q);

int is_empty(queue *q);

#endif