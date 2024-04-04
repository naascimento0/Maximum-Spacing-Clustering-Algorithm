#if !defined(EDGE)
#define EDGE

#include "vertex.h"

typedef struct edge Edge;

Edge* edge_create(Vertex *src, Vertex *dest, double weight);
double edge_weight(Edge *e);
Vertex *edge_src(Edge *e);
Vertex *edge_dest(Edge *e);
int edge_compare(const void *a, const void *b);
void edge_debug(Edge *v);
void edge_destroy(Edge *e);

#endif // EDGE
