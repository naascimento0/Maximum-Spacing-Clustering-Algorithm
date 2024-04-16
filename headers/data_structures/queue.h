#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue Queue;

Queue *queue_construct();

void queue_enqueue(Queue *queue, data_type value);

data_type queue_dequeue(Queue *queue);

int queue_empty(Queue *queue);

int queue_size(Queue *queue);

void queue_destroy(Queue *queue);

#endif
