#ifndef GROUPS_H_
#define GROUPS_H_

#include "data_structures/queue.h"
#include "disjointset.h"
#include "vertex.h"

typedef struct groups Groups;

Groups *groups_create(int k);

void groups_msca(Groups *gps, Vertex **vertices, int vertices_qtt, DisjointSet *ds);

void groups_output(Groups *gps, char *output_file_path);

void groups_destroy(Groups *gps);

#endif 