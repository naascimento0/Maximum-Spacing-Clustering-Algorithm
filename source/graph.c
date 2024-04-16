#include "../headers/graph.h"

struct graph{
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
    DisjointSet *ds = create_disjoint_set(g->vertices_qtt);
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
            max_edges += _union(ds, index_src, index_dest);
        }
    }

    graph_msca_output(g, K, output_file_path, ds);
    destroy_disjoint_set(ds);
}

void graph_msca_output(Graph *g, int K, char *output_file_path, DisjointSet *ds){
    FILE *output = fopen(output_file_path, "w+");
    if(!output)
         exit(printf("ERROR: File %s did not open", output_file_path));

    Queue *q = queue_construct();
    char *aux = vertex_get_id(g->vertices[_find(ds, 0)]);  // get the first vertex of the k-set

    Queue *writed = queue_construct();
    queue_enqueue(writed, aux);

    for(int i = 0; i < K; i++){
    	for(int j = 0; j < g->vertices_qtt; j++){
    		if (strcmp(aux, vertex_get_id(g->vertices[_find(ds, j)])) == 0)
    			queue_enqueue(q, vertex_get_id(g->vertices[j]));   // enqueue the vertices of the k-set
        } 

    	while(!queue_empty(q)){
            char *display = queue_dequeue(q);
            if(!queue_size(q)){
                fprintf(output, "%s", display);
                break;
            }
    		fprintf(output, "%s,", display);   // display the k-set of vertices
    	}
    	fprintf(output, "\n");

        for(int j = 0; j < g->vertices_qtt; j++){
    		if (strcmp(aux, vertex_get_id(g->vertices[_find(ds, j)])) != 0 && !queue_find(writed, vertex_get_id(g->vertices[_find(ds, j)]))){
                queue_enqueue(writed, aux);   // enqueue the vertices of the k-set
                aux = vertex_get_id(g->vertices[_find(ds, j)]);
                break;
            }
        }
    }

    queue_destroy(q);
    fclose(output);
 }
