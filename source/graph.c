#include "../headers/graph.h"

struct graph {
    Vertex **vertices;
    int qnt_vertices;
    Edge **edges;
    int qnt_edges;
};

Graph* graph_create(FILE *input) {
    Graph *g = malloc(sizeof(Graph));

    g->vertices = vertices_load(input, (&g->qnt_vertices));     // loading vertices from input
    qsort(g->vertices, g->qnt_vertices, sizeof(Vertex*), vertex_sort_by_id);      // sorting vertices by their id

    g->qnt_edges = ((g->qnt_vertices * g->qnt_vertices - g->qnt_vertices) / 2);   
    g->edges = malloc(sizeof(Edge *) * g->qnt_edges);

    // creating all possible edges between vertices
    int current_edge = 0;
    for(int i = 0; i < g->qnt_vertices; i++){
        for(int j = i + 1; j < g->qnt_vertices; j++)
            g->edges[current_edge++] = edge_create(g->vertices[i], g->vertices[j], vertex_calculate_distance(g->vertices[i], g->vertices[j]));
    }

    qsort(g->edges, g->qnt_edges, sizeof(Edge*), edge_compare);    // sorting edges by their weight

    return g;
}

void graph_destroy(Graph *g) {
    for(int i = 0; i < g->qnt_vertices; i++)
        vertex_destroy(g->vertices[i]);
    
    for(int i = 0; i < g->qnt_edges; i++)
        edge_destroy(g->edges[i]);
    
    free(g->vertices);
    free(g->edges);
    free(g);
}

//maximum spacing clustering algorithm
void graph_mscaaa(Graph *g, int K, char *output_file_path){
    int *parent = malloc(sizeof(int) * g->qnt_vertices);    // union-find indexes array
    int *sz = malloc(sizeof(int) * g->qnt_vertices);        // size of each tree

    for(int i = 0; i < g->qnt_vertices; i++){
        sz[i] = 1;      // tree size initially is 1
        parent[i] = i;  // each vertex is their own parent
    }
    
    // Kruskal modified to generate a MSCA
    int max_edges = g->qnt_vertices - K;
    int index_src, index_dest;
    for(int i = 0; i < max_edges; i++){
        Vertex *src = edge_src(g->edges[i]);
        Vertex *dest = edge_dest(g->edges[i]);
        
        Vertex **p = bsearch(&src, g->vertices, g->qnt_vertices, sizeof(Vertex*), vertex_sort_by_id);
        Vertex **q = bsearch(&dest, g->vertices, g->qnt_vertices, sizeof(Vertex*), vertex_sort_by_id);
        if(p != NULL && q != NULL){     // TO DO: uma olhada
            index_src = p - g->vertices;    // pointer arithmetic
            index_dest = q - g->vertices;   // pointer arithmetic
            max_edges += _union(index_src, index_dest, parent, sz);
        }
    }

    free(parent);
    free(sz);
}

void graph_msca_output(Graph *g, int K, char *output_file_path, int *parent){
    // output incompleto
    FILE *output = fopen(output_file_path, "w+");
    if(!output)
        exit(printf("ERROR: File %s did not open", output_file_path));
    
    char *aux = vertex_get_name(g->vertices[parent[0]]);
    int x = 0;

    for (int i = 1; i < K; i++)
    {
        for (int j = 0; j < g->qnt_vertices; j++){
            if (strcmp(aux, vertex_get_name(g->vertices[parent[j]])) == 0)
            {
                fprintf(output, "%s,", vertex_get_name(g->vertices[j]));
            }
        }

        while (strcmp(aux, vertex_get_name(g->vertices[x])) == 0)
        {
            x++;
        }

        aux = vertex_get_name(g->vertices[parent[x]]);
        x++;
        printf("\n");
    }

    fclose(output);
}

int _union(int p, int q, int *parent, int *sz){
    int i = _find(p, parent);
    int j = _find(q, parent);
    if(i == j)
        return 1;  
    if(sz[i] < sz[j])
        parent[i] = j; sz[j] += sz[i]; 
    else
        parent[j] = i; sz[i] += sz[j]; 
    return 0;
}

int _find(int i, int *parent){
    while (i != parent[i]){
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

