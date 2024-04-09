#include "../headers/graph.h"

struct graph {
    Vertex **vertices;
    int vertices_qtt;
    int dimension;
    Edge **edges;
    int edges_qtt;
};

Graph* graph_create(FILE *input) {
    Graph *g = malloc(sizeof(Graph));

    g->dimension = dimension_counter(input);
	rewind(input);

    g->vertices = vertices_load(input, (&g->vertices_qtt));     // loading vertices from input
    qsort(g->vertices, g->vertices_qtt, sizeof(Vertex*), vertex_id_compare);      // sorting vertices by their id

    g->edges_qtt = ((g->vertices_qtt * g->vertices_qtt - g->vertices_qtt) / 2);   
    g->edges = malloc(sizeof(Edge*) * g->edges_qtt);

    // creating all possible edges between vertices
    int current_edge = 0;
    for(int i = 0; i < g->vertices_qtt; i++){
        for(int j = i + 1; j < g->vertices_qtt; j++)
            g->edges[current_edge++] = edge_create(g->vertices[i], g->vertices[j], vertex_calculate_distance(g->vertices[i], g->vertices[j], g->dimension));
    }

    qsort(g->edges, g->edges_qtt, sizeof(Edge*), edge_weight_compare);    // sorting edges by their weight

    return g;
}

void graph_destroy(Graph *g) {
    for(int i = 0; i < g->vertices_qtt; i++)
        vertex_destroy(g->vertices[i]);
    
    for(int i = 0; i < g->edges_qtt; i++)
        edge_destroy(g->edges[i]);
    
    free(g->vertices);
    free(g->edges);
    free(g);
}

//maximum spacing clustering algorithm
void graph_msca(Graph *g, int K, char *output_file_path){
    int *parent = malloc(sizeof(int) * g->vertices_qtt);    // union-find indexes array
    int *sz = malloc(sizeof(int) * g->vertices_qtt);        // size of each tree

    for(int i = 0; i < g->vertices_qtt; i++){
        sz[i] = 1;      // tree size initially is 1
        parent[i] = i;  // each vertex is their own parent
    }
    
    // Kruskal modified to generate a MSCA
    int max_edges = g->vertices_qtt - K;
    int index_src, index_dest;
    for(int i = 0; i < max_edges; i++){
        Vertex *src = edge_src(g->edges[i]);
        Vertex *dest = edge_dest(g->edges[i]);
        
        Vertex **p = bsearch(&src, g->vertices, g->vertices_qtt, sizeof(Vertex*), vertex_id_compare);
        Vertex **q = bsearch(&dest, g->vertices, g->vertices_qtt, sizeof(Vertex*), vertex_id_compare);
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
    
    char *aux = vertex_get_id(g->vertices[parent[0]]);
    int x = 0;

    for (int i = 1; i < K; i++)
    {
        for (int j = 0; j < g->vertices_qtt; j++){
            if (strcmp(aux, vertex_get_id(g->vertices[parent[j]])) == 0)
            {
                fprintf(output, "%s,", vertex_get_id(g->vertices[j]));
            }
        }

        while (strcmp(aux, vertex_get_id(g->vertices[x])) == 0)
        {
            x++;
        }

        aux = vertex_get_id(g->vertices[parent[x]]);
        x++;
        printf("\n");
    }

    fclose(output);
}

int _union(int p, int q, int *parent, int *sz){
    int i = _find(p, parent);
    int j = _find(q, parent);
    if(i == j){
        return 1;  
    }else if(sz[i] < sz[j]){
        parent[i] = j; sz[j] += sz[i]; 
    }else{
        parent[j] = i; sz[i] += sz[j];
    }
    return 0;
}

int _find(int i, int *parent){
    while (i != parent[i]){
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

