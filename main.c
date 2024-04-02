#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/util.h"
#include "headers/vertex.h"

int main(int argc, char **argv){
	char* input_file_path = argv[1];
	int k = atoi(argv[2]);
	char* output_file_path = argv[3];

	FILE *input = fopen(input_file_path, "r");
	if(!input)
		exit(printf("ERROR: File %s did not open", input_file_path));

	Vertex **vertices = load_vertices(input);

	fclose(input);
	vertices_destroy(vertices);

	return 0;
}
