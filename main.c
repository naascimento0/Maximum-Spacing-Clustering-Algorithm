#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/graph.h"

int main(int argc, char **argv){
	char* input_file_path = argv[1];
	int k = atoi(argv[2]);
	char* output_file_path = argv[3];

	FILE *input = fopen(input_file_path, "r");
	if(!input)
		exit(printf("ERROR: File %s did not open", input_file_path));

	Graph *graph = graph_create(input);
	graph_msca(graph, k, output_file_path);
	graph_destroy(graph);

	fclose(input);

	return 0;
}
