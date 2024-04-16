#include "../../headers/data_structures/list.h"

List *list_construct(){
    List *list = malloc(sizeof(List));
    list->last = list->head = NULL;
    list->size = 0;
    return list;
}

int list_size(List *l){
    return l->size;
}

void list_push_front(List *l, data_type data){
    Node *new = node_construct(data, NULL, l->head);
    if(l->head != NULL)
        l->head->prev = new;
    else
        l->last = new;
    
    l->head = new;
    l->size++;
}

void list_push_back(List *l, data_type data){
    Node *new = node_construct(data, l->last, NULL);

    if(l->last != NULL)
        l->last->next = new;
    else
        l->head = new;

    l->last = new;
    l->size++;
}

void list_destroy(List *l){

    while(l->head != NULL){

        Node *aux = l->head;
        l->head = l->head->next;
        node_destroy(aux);
    }

    free(l);
}

data_type list_pop_front(List *l){
    if(l->head == NULL)
	    exit(printf("Error: list is empty!\n"));

    Node *aux = l->head;
    data_type value = aux->value;

    l->head = aux->next;
    if(l->head != NULL)
    	l->head->prev = NULL;

    node_destroy(aux);
    l->size--;

    if(l->size <= 1)
    	l->last = l->head;

    return value;
}

int list_find(List *l, data_type data){
    Node *aux = l->head;
    int i = 0;
    while(aux != NULL){
        if(aux->value == data)
            return 1;
        aux = aux->next;
        i++;
    }
    return 0;
}

data_type list_get(List *l, int i){
    if(i >= l->size)
        exit(printf("Error: index out of bounds!\n"));

    Node *aux = l->head;
    for(int j = 0; j < i; j++)
        aux = aux->next;

    return aux->value;
}



