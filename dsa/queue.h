#include <stdio.h>
#include <stdlib.h>

#ifndef _QUEUE_H
#define _QUEUE_H

struct queue_record;
typedef struct queue_record *queue;

int queue_is_empty(queue q);
int queue_is_full(queue q);           // TODO
queue queue_create(int max_elements); // TODO
void queue_dispose(queue q);          // TODO
void queue_make_empty(queue q);
void queue_enqueue(int x, queue q);
int queue_front(queue q);    // TODO
void queue_dequeue(queue q); // TODO
static int queue_succ(int value, queue q);

#define QUEUE_MIN_QUEUE_SIZE 5

struct queue_record
{
        int capacity;
        int front;
        int rear;
        int size;
        int *array;
};

int queue_is_empty(queue q)
{
        return q->size == 0;
}

void queue_make_empty(queue q)
{
        q->size = 0;
        q->front = 1;
        q->rear = 0;
}

static int queue_succ(int value, queue q)
{
        if (++value == q->capacity)
                value = 0;
        return value;
}

void queue_enqueue(int x, queue q)
{
        if (queue_is_full(q))
        {
                perror("Full queue.");
                return;
        }
        else
        {
                q->size++;
                q->rear = queue_succ(q->rear, q);
                q->array[q->rear] = x;
        }
}

#endif
