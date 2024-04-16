#include "../headers/util.h"
#include "../headers/vertex.h"

int dimension_counter(FILE *file){
    size_t size = 0;          
	char *line = NULL;
	ssize_t line_size = getline(&line,&size, file);
	int dimension = 0;
	for(int i = 0; i < line_size; i++)
		if(line[i] == ',')
			dimension++;

    free(line);
    return dimension;
}
