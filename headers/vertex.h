#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "../headers/vertex.h"
#include "../headers/util.h"

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex Vertex;

Vertex* vertex_create(char *vertex_name, double *coordinates);

char* vertex_get_id(Vertex *v);

Vertex** vertices_load(FILE *input, int *amount);

double vertex_calculate_distance(Vertex *v_a, Vertex *v_b, int dimension);

int vertex_id_compare(const void *a, const void *b);

void vertex_destroy(Vertex *v);

#endif
