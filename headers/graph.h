#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"
#include "disjointset.h"
#include "data_structures/queue.h"
#include "groups.h"

typedef struct graph Graph;

Graph *graph_create(FILE *input);

void graph_msca(Graph *g, int K, char *output_file_path);

void graph_destroy(Graph *g);

#endif 
