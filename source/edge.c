#include "../headers/edge.h"

struct edge{
    double weight;
    Vertex *src;
    Vertex *dest;
};

Edge* edge_create(Vertex *src, Vertex *dest, double weight) {
    Edge* edge = malloc(sizeof(Edge));
    edge->src = src;
    edge->dest = dest;
    edge->weight = weight;
    return edge;
}

double edge_weight(Edge *e){
    return e->weight;
}

Vertex* edge_src(Edge *e){
    return e->src;
}

Vertex* edge_dest(Edge *e){
    return e->dest;
}

int edge_weight_compare(const void *a, const void *b) {
    Edge *edge_a = *(Edge**)a;
    Edge *edge_b = *(Edge**)b;
    if (edge_weight(edge_a) < edge_weight(edge_b))
        return -1;
    else if (edge_weight(edge_a) > edge_weight(edge_b))
        return 1;
    else 
        return 0;
}

void edge_debug(Edge *e, int dimension){
    vertex_debug(e->src, dimension);
    vertex_debug(e->dest, dimension);
    printf("Weight: %f\n", e->weight);
    printf("\n");
}

void edge_destroy(Edge *e){
    free(e);
}