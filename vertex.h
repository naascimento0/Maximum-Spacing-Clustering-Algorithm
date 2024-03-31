#ifndef _VERTEX_H_
#define _VERTEX_H_



typedef struct vertex VertexND;


///VertexND *VertexND_Create(char *vertex_name,int dimension, ...);

VertexND *Vertex_Create(char *vertex_name, int dimension);

void vertexSetCoordinate(VertexND *v, int coordinateSlot, double value);

void VertexND_Destroy(VertexND *v);

void debug_vertex(VertexND *v);

#endif