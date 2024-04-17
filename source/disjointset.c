#include "../headers/disjointset.h"

struct disjointset{
    int *parent; 
    int *size;   
    int n;       
};

DisjointSet* create_disjoint_set(int N){
    DisjointSet *ds = malloc(sizeof(DisjointSet));
    ds->parent = malloc(sizeof(int) * N);
    ds->size = malloc(sizeof(int) * N);
    ds->n = N;
    
    for(int i = 0; i < N; i++){
        ds->parent[i] = i;  // each vertex is its own parent
        ds->size[i] = 1;   // tree size initially is 1
    }
    return ds;
}

int _union(DisjointSet *ds, int p, int q){
    int i = _find(ds, p);
    int j = _find(ds, q);
    if(i == j){
        return 1;  
    }else if(ds->size[i] < ds->size[j]){
        ds->parent[i] = j; ds->size[j] += ds->size[i]; 
    }else{
        ds->parent[j] = i; ds->size[i] += ds->size[j];
    }
    return 0;
}

int _find(DisjointSet *ds, int i){
    while (i != ds->parent[i]){
        ds->parent[i] = ds->parent[ds->parent[i]];
        i = ds->parent[i];
    }
    return i;
}


void destroy_disjoint_set(DisjointSet *ds){
    free(ds->parent);
    free(ds->size);
    free(ds);
}
