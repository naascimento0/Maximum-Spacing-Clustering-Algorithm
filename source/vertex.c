#include "vertex.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

struct vertex
{
    char *name;
    int dimension;
    double *coordinates;
};

VertexND *VertexND_Create(char *vertex_name,int dimension, ...){
    va_list parameters;
    VertexND *new_vertex = calloc(1,sizeof(VertexND));
    new_vertex->coordinates = calloc(dimension, sizeof(double));
    new_vertex->dimension = dimension;
    new_vertex->name = strdup(vertex_name);
    va_start(parameters,dimension);
    for(int i = 0; i < dimension; i++) new_vertex->coordinates[i] = va_arg(parameters,double);
    va_end(parameters);
    return new_vertex; 
}

VertexND *Vertex_Create(char *vertex_name, int dimension){
    VertexND *new_vertex = calloc(1,sizeof(VertexND));
    new_vertex->coordinates = calloc(dimension, sizeof(double));
    new_vertex->dimension = dimension;
    new_vertex->name = strdup(vertex_name);
    return new_vertex;    
}

void vertexSetCoordinate(VertexND *v, int coordinateSlot, double value){
    if(coordinateSlot < 0 || coordinateSlot >= v->dimension) {
        printf("Vertex Set Coordinate ERROR: Out of Index\n");
        exit(EXIT_FAILURE);
    }else v->coordinates[coordinateSlot] = value;
}

double vertexCalculateDistance(VertexND *v_a, VertexND *v_b){
    if (v_a->dimension != v_b->dimension)
    {
        printf("Vertex Calculate Distance ERROR: Isn't same dimension");
        exit(EXIT_FAILURE);
    }

    double sum;
    for (int i = 0; i < v_a->dimension; i++) sum += pow((v_a->coordinates[i] - v_b->coordinates[i]),2);
    return sqrt(sum);
}

void debug_vertex(VertexND *v){
    printf("NAME: %s | COORDINATES: ", v->name);
    for (int i = 0; i < v->dimension; i++) printf("%lf ", v->coordinates[i]);
    printf("\n");
}

void VertexND_Destroy(VertexND *v){
    free(v->name);
    free(v->coordinates);
    free(v);
}