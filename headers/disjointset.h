#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H
#include <stdlib.h>

typedef struct disjointset DisjointSet;

DisjointSet* create_disjoint_set(int N);

int _union(DisjointSet *ds, int p, int q);

int _find(DisjointSet *ds, int i);

void destroy_disjoint_set(DisjointSet *ds);

#endif