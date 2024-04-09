#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"

typedef struct graph Graph;

Graph *graph_create(FILE *input);

void graph_destroy(Graph *g);

void graph_msca(Graph *g, int K, char *output_file_path);

void graph_msca_output(Graph *g, int K, char *output_file_path, int *parent);

int _union(int p, int q, int *parent, int *sz);

int _find(int i, int *parent);

#endif 
