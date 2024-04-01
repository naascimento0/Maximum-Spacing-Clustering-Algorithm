#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef struct vertex VertexND;

/// @brief Cria um vértice em R^N, com N dimensões e o preenche com valores especificados
/// @param vertex_name 
/// @param dimension 
/// @param  
/// @return
VertexND *VertexND_Create(char *vertex_name,int dimension, ...);

/// @brief Cria um vértice em R^N
/// @param vertex_name 
/// @param dimension 
/// @return 
VertexND *Vertex_Create(char *vertex_name, int dimension);

/// @brief Preenche uma coordenada de um vértice especificado em R^N
/// @param v 
/// @param coordinateSlot 
/// @param value 
void vertexSetCoordinate(VertexND *v, int coordinateSlot, double value);

/// @brief Destrói o vértice especificado
/// @param v 
void VertexND_Destroy(VertexND *v);

/// @brief exibe as informações internas do vértice especificado
/// @param v 
void debug_vertex(VertexND *v);

#endif