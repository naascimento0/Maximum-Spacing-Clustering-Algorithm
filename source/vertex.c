#include "vertex.h"

struct vertex{
    char *name;
    int dimension;
    double *coordinates;
};

// Vertex *Vertex_Create(char *vertex_name,int dimension, ...){
//     va_list parameters;
//     Vertex *new_vertex = calloc(1,sizeof(Vertex));
//     new_vertex->coordinates = calloc(dimension, sizeof(double));
//     new_vertex->dimension = dimension;
//     new_vertex->name = strdup(vertex_name);
//     va_start(parameters,dimension);
//     for(int i = 0; i < dimension; i++) new_vertex->coordinates[i] = va_arg(parameters,double);
//     va_end(parameters);
//     return new_vertex; 
// }

Vertex* vertex_create(char *vertex_name, int dimension, double *coordinates){
    Vertex *new_vertex = calloc(1,sizeof(Vertex));
    new_vertex->coordinates = coordinates;
    new_vertex->dimension = dimension;
    new_vertex->name = vertex_name;
    return new_vertex;    
}

char *vertex_get_name(Vertex *v){
    return v->name;
}

//a função load_vertices necessita estar em vertex.c pois retorna um Vertex**
Vertex** vertex_load(FILE *input, int *amount){
	/// Contador de dimensões do ponto
	size_t size = 0;          
	char *line = NULL;
	ssize_t line_size = getline(&line,&size, input);

	int dimension = 0;
	for(int i = 0; i < line_size; i++)
		if(line[i] == ',')
			dimension++;

	rewind(input);
	*amount = line_file_counter(input);
	rewind(input);

	Vertex **vertices = malloc(sizeof(Vertex *) * (*amount));

	int k = 0;
	while((getline(&line, &size, input)) != -1){
		double *coordinates = malloc(dimension * sizeof(double));
		char *token = strtok(line, ",");
		char *name = strdup(token);

		token = strtok(NULL, ",");
		for(int i = 0; i < dimension && token != NULL; i++){
		    //printf("%s\n", token);
			coordinates[i] = atof(token);
			token = strtok(NULL, ",");
		}
		//printf("\n");
		vertices[k++] = vertex_create(name,dimension,coordinates);
		//para evitar strdup na mesma string duas vezes, retirou-se o free(name) desta função. Ademais, na função vertex_create não se faz mais strdup
	}

	free(line);
	return vertices;
}

double vertex_calculate_distance(Vertex *v_a, Vertex *v_b){
    if (v_a->dimension != v_b->dimension)
        exit(printf("Vertex Calculate Distance ERROR: Isn't same dimension"));

    double sum = 0;
    for (int i = 0; i < v_a->dimension; i++)
    	sum += pow((v_a->coordinates[i] - v_b->coordinates[i]),2);
    return sqrt(sum);
}

int vertex_sort(const void *a, const void *b){
    const Vertex **aa = (const Vertex **)a;
    const Vertex **bb = (const Vertex **)b;
    return strcmp((*aa)->name, (*bb)->name);
}

int vertex_search(const void *a, const void *b){
    const Vertex *aa = (const Vertex *)a;
    const Vertex **bb = (const Vertex **)b;
    return strcmp(aa->name, (*bb)->name);
}

void vertex_debug(Vertex *v){
    printf("NAME: %s | COORDINATES: ", v->name);
    for (int i = 0; i < v->dimension; i++) printf("%lf ", v->coordinates[i]);
    printf("\n");
}

void vertex_destroy(Vertex *v){
    free(v->name);
    free(v->coordinates);
    free(v);
}
