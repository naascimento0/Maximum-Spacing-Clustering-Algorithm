#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../headers/util.h"
#include "headers/vertex.h"

// a função deixará de retornar void para retornar a estrutura dados com Point
Vertex **load_points(FILE *input){
	char *line = NULL;
	size_t size = 0;           // able to store the size of the largest possible object
	ssize_t line_size;         // can be used to also represent negative numbers
	int dimension = 0;
	int counter = 0, counter_slot = 0;


	Vertex **vertex_array = malloc(sizeof(Vertex *));

	line_size = getline(&line,&size,input);
	for (int i = 0; i < line_size; i++){
		if(line[i] == ',') dimension++;	
	}
	rewind(input);	


	while((line_size = getline(&line, &size, input)) != -1){
		char *token = strtok(line, ",");
		// vertex_array[counter] = Vertex_Create(token,dimension);
		while(token != NULL){
			printf("%s\n", token);
			token = strtok(NULL, ","); /// pode dar segmentation fault se não houver if de guarda
			// vertexSetCoordinate(vertex_array[counter],counter_slot,atof(token)); /// guardar em um array de double
			// counter_slot++;
		}
		// counter++;
	}

	
	free(line);
}

