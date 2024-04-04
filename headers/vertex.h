#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "../headers/vertex.h"
#include "../headers/util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>

typedef struct vertex Vertex;

Vertex* vertex_create(char *vertex_name, int dimension, double *coordinates);

char *vertex_get_name(Vertex *v);

Vertex** vertices_load(FILE *input, int *amount);

double vertex_calculate_distance(Vertex *v_a, Vertex *v_b);

int vertex_sort_by_name(const void *v1, const void *v2);

int vertex_search(const void *v1, const void *v2);

void vertex_debug(Vertex *v);

void vertex_destroy(Vertex *v);




#endif
