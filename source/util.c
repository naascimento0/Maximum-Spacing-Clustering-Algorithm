#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../headers/util.h"
#include "../headers/vertex.h"

#define BUFFER_SIZE 65536

/*
função retirada do StackOverflow : https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file
*/
int line_counter(FILE *file)
{
    char buffer[BUFFER_SIZE];
    int counter = 0;
    while(1)
    {
        size_t max_size = fread(buffer, 1, BUFFER_SIZE, file);
        if (ferror(file))
            return -1;

        int i;
        for (i = 0; i < max_size; i++)
            if (buffer[i] == '\n')counter++;

        if (feof(file))
            break;
    }
    return counter;
}

// a função deixará de retornar void para retornar a estrutura dados com Point
Vertex **load_points(FILE *input){
	char *line = NULL;
	char *name = NULL;
	size_t size = 0;           // able to store the size of the largest possible object
	ssize_t line_size;         // can be used to also represent negative numbers
	int dimension = 0;
	int i, k = 0;
	int amount = 0;
	
	
	/// Contador de dimensões do ponto
	line_size = getline(&line,&size, input);
	for (int i = 0; i < size; i++) if(line[i] == ",") dimension++;
	rewind(input);

	/// implementar o sistema de contagem de linhas ANTES DE RODAR

	amount = line_counter(input);
	rewind(input);

	Vertex **vertex_array = malloc(sizeof(Vertex *) * amount);

	while((line_size = getline(&line, &size, input)) != -1){
		double *coordinates = calloc(dimension,sizeof(double));
		char *token = strtok(line, ",");
		name = strdup(token);
		i = 0;
		while(token != NULL){
			printf("%s\n", token);
			token = strtok(NULL, ",");
			coordinates[i] = atof(token);
			i++;
		}
		vertex_array[k] = Vertex_create(name,dimension,coordinates);
		k++;
		free(name);
	}

	free(line);
	return vertex_array;
}
