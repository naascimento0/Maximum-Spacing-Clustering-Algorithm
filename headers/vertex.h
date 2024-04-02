#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <stdio.h>

typedef struct vertex Vertex;


///Vertex *Vertex_Create(char *vertex_name,int dimension, ...);

Vertex* vertex_create(char *vertex_name, int dimension, double *coordinates);

Vertex** load_vertices(FILE *input);

double vertex_calculate_distance(Vertex *v_a, Vertex *v_b);

void debug_vertex(Vertex *v);

void vertices_destroy(Vertex **v);
void vertex_destroy(Vertex *v);




#endif
