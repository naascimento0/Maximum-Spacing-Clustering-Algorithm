#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>	
#include "headers/graph.h"

int main(int argc, char **argv){
	if(argc < 4)
		exit(printf("ERROR: Missing arguments!\n"));

	char* input_file_path = argv[1];
	int k = atoi(argv[2]);
	char* output_file_path = argv[3];

	FILE *input = fopen(input_file_path, "r");
	if(!input)
		exit(printf("ERROR: File %s did not open", input_file_path));

	clock_t start = clock();
	Graph *graph = graph_create(input);
	graph_msca(graph, k, output_file_path);
	clock_t end = clock();
	graph_destroy(graph);

	fclose(input);

	double seconds = ((double) end - start) / CLOCKS_PER_SEC;
    printf ("\n tempo gasto: %lf \n ", seconds);

	return 0;
}
