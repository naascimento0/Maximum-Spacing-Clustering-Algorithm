#include "../../headers/data_structures/queue.h"

struct Queue{
    List *list;
};

Queue *queue_construct(){
    Queue *queue = (Queue*)calloc(1, sizeof(Queue));
    queue->list = list_construct();
    return queue;
}

void queue_enqueue(Queue *queue, data_type value){
    list_push_back(queue->list, value);
}

data_type queue_dequeue(Queue *queue){
    return list_pop_front(queue->list);
}

int queue_empty(Queue *queue){
    return queue->list->head == NULL;
}

int queue_size(Queue *queue){
    return queue->list->size;
}

void queue_destroy(Queue *queue){
    list_destroy(queue->list);
    free(queue);
}

int queue_find(Queue *queue, data_type value){
    return list_find(queue->list, value);
}







