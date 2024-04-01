#include "group.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;

struct Node
{
    void *content;
    Node *next;
};

struct group
{
    int size;
    Node *head, *last;
};

Node *Node_Create(void *content, Node *next)
{
    Node *new_node = (Node *)calloc(1, sizeof(Node));
    new_node->content = content;
    new_node->next;
    return new_node;
}

void *Node_Destroy(Node *n)
{
    void *to_remove = n->content;
    free(n);
    return to_remove;
}

Group *Group_Create()
{
    return (Group *)calloc(1, sizeof(Group));
}

void groupPush(Group *g, void *content)
{
    if (g->head == NULL)
        g->last = g->head = Node_Create(content, NULL);
    else
        g->last = g->last->next = Node_Create(content, NULL);
    g->size++;
}

void *groupPop(Group *g)
{
    if (g->head == NULL && g->head == NULL)
        exit(printf("Group POP ERROR: Empty group"));
    else
    {
        Node *to_remove_node = g->head;
        g->head = g->head->next;
        g->size--;
        if (g->size <= 1)
            g->last = g->head;
        return Node_Destroy(to_remove_node);
    }
}

void groupDebugContent(Group *g, void (*ContentPrint_fn)(void *))
{
    if (g->head == NULL)
    {
        printf("GROUP: Uninitialized Group");
        return;
    }

    printf("GROUP:\n");
    printf("\t Size: %d\n", g->size);
    printf("\t Content:{");
    Node *iterator = g->head;
    int counter = 0;
    while (iterator != NULL)
    {
        ContentPrint_fn(iterator->content);
        if (counter != g->size - 1)
            printf(", ");
        iterator = iterator->next;
        counter++;
    }
    printf("}");
}
void Group_Destroy(Group *g, void (*ContentDestroy_fn)(void *))
{
    Node *iterator = g->head;
    while (iterator != NULL)
    {
        Node *to_remove_node = iterator;
        iterator = iterator->next;
        ContentDestroy_fn(Node_Destroy(to_remove_node));
    }
    free(g);
}