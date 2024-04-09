#include "../headers/vertex.h"

struct vertex{
    char *id;
    double *coordinates;
};

Vertex* vertex_create(char *vertex_id, double *coordinates){
    Vertex *new_vertex = calloc(1,sizeof(Vertex));
    new_vertex->coordinates = coordinates;
    new_vertex->id = vertex_id;
    return new_vertex;    
}

char* vertex_get_id(Vertex *v){
    return v->id;
}

Vertex** vertices_load(FILE *input, int *amount){
	int dimension = dimension_counter(input);
	rewind(input); // return to the beginning of the file

	Vertex **vertices = malloc(sizeof(Vertex*) * 50);
	int max_size = 50;

	char *line = NULL;
	size_t size = 0;    
	int k = 0;
	while((getline(&line, &size, input)) != -1){	// reading a point and its coordinates 
		double *coordinates = malloc(dimension * sizeof(double));
		char *token = strtok(line, ",");
		char *id = strdup(token);

		token = strtok(NULL, ",");
		for(int i = 0; i < dimension && token != NULL; i++){  // loop to get only coordinates
		    //printf("%s\n", token);
			coordinates[i] = atof(token);
			token = strtok(NULL, ",");
		}
		//printf("\n");
		if(k >= max_size){		// Vertex** realloc
			max_size *= 2;
			Vertex **vertices = realloc(vertices, sizeof(Vertex) * max_size);
		}
		vertices[k++] = vertex_create(id, coordinates);
	}

	(*amount) = 50;
	free(line);
	return vertices;
}

double vertex_calculate_distance(Vertex *v_a, Vertex *v_b, int dimension){
    double sum = 0;
    for (int i = 0; i < dimension; i++)
    	sum += pow((v_a->coordinates[i] - v_b->coordinates[i]),2);
    return sqrt(sum);
}

int vertex_id_compare(const void *a, const void *b){
    const Vertex **aa = (const Vertex**)a;
    const Vertex **bb = (const Vertex**)b;
    return strcmp((*aa)->id, (*bb)->id);
}

void vertex_debug(Vertex *v, int dimension){
    printf("id: %s | COORDINATES: ", v->id);
    for (int i = 0; i < dimension; i++) printf("%lf ", v->coordinates[i]);
    printf("\n");
}

void vertex_destroy(Vertex *v){
    free(v->id);
    free(v->coordinates);
    free(v);
}
