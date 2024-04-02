#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef struct vertex Vertex;


///Vertex *Vertex_Create(char *vertex_name,int dimension, ...);

Vertex *Vertex_Create(char *vertex_name, int dimension, double *coordinates);

void vertexSetCoordinate(Vertex *v, int coordinateSlot, double value);

void Vertex_Destroy(Vertex *v);

void debug_vertex(Vertex *v);

#endif