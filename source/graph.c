#include "graph.h"

struct graph {
    Vertex **vertices;
    int qnt_vertices;
    Edge **edges;
    int qnt_edges;
};

Graph *graph_create(FILE *input) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = vertex_load(input, (&g->qnt_vertices));
    qsort(g->vertices, g->qnt_vertices, sizeof(Vertex *), vertex_sort);
    g->qnt_edges = (((g->qnt_vertices * g->qnt_vertices) - g->qnt_vertices) / 2);
    g->edges = (Edge **)malloc(sizeof(Edge *) * g->qnt_edges);

    int current_edge = 0;

    for (int i = 0; i < g->qnt_vertices; i++)
    {
        for (int j = i + 1; j < g->qnt_vertices; j++)
        {   
            g->edges[current_edge] = edge_create(g->vertices[i], g->vertices[j], vertex_calculate_distance(g->vertices[i], g->vertices[j]));
            current_edge++;
        }
    }
    //printf("Edges: %d\n", current_edge);
    qsort(g->edges, g->qnt_edges, sizeof(Edge *), edge_compare);

    for (int i = 0; i < g->qnt_edges; i++)
    {
        //printf("Edge %d\n", i);
        //edge_debug(g->edges[i]);
    }

    return g;
}

void graph_destroy(Graph *g) {
    for (int i = 0; i < g->qnt_vertices; i++)
    {
        vertex_destroy(g->vertices[i]);
    }
    for (int i = 0; i < g->qnt_edges; i++)
    {
        edge_destroy(g->edges[i]);
    }
    free(g->vertices);
    free(g->edges);
    free(g);
}

void graph_msca(Graph *g, int K, char *output_file_path){
    int *parent = (int *)malloc(sizeof(int) * g->qnt_vertices);
    int *sz = (int *)malloc(sizeof(int) * g->qnt_vertices);

    for (int i = 0; i < g->qnt_vertices; i++)
    {
        sz[i] = 1;
        parent[i] = i;
    }
    
    int max_edges = g->qnt_vertices - K;

    int index_src, index_dest;
    for (int i = 0; i < max_edges; i++)
    {
        Vertex *src = edge_src(g->edges[i]);
        Vertex *dest = edge_dest(g->edges[i]);
        
        Vertex **p = (Vertex **)bsearch(&src, g->vertices, g->qnt_vertices, sizeof(Vertex *), vertex_sort);
        Vertex **q = (Vertex **)bsearch(&dest, g->vertices, g->qnt_vertices, sizeof(Vertex *), vertex_sort);
        if (p != NULL && q != NULL) {
            index_src = p - g->vertices;
            index_dest = q - g->vertices;
            max_edges += _union(index_src, index_dest, parent, sz);
        }
    }

    for (int i = 0; i < g->qnt_vertices; i++)
    {
        printf("name: %s parent:%d\n", vertex_get_name(g->vertices[i]), parent[i]);
    }


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

    free(parent);
    free(sz);
}

int _union(int p, int q, int *parent, int *sz) {
    int i = _find(p, parent);
    int j = _find(q, parent);
    if (i == j) return 1;
    if (sz[i] < sz[j]) { parent[i] = j; sz[j] += sz[i]; }
    else { parent[j] = i; sz[i] += sz[j]; }
    return 0;
}

int _find(int i, int *parent) {
    while (i != parent[i]) {
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

