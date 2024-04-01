#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../headers/util.h"

// a função deixará de retornar void para retornar a estrutura dados com Point
void load_points(FILE *input){
	char *line = NULL;
	size_t size = 0;           // able to store the size of the largest possible object
	ssize_t line_size;         // can be used to also represent negative numbers

	while((line_size = getline(&line, &size, input)) != -1){

		char *token = strtok(line, ",");
		while(token != NULL){
			printf("%s\n", token);
			token = strtok(NULL, ",");
		}
	}

	free(line);
}
