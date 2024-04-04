#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/util.h"
#include "../headers/vertex.h"

#define BUFFER_SIZE 65536

/*
função retirada do StackOverflow : https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file
*/
int line_file_counter(FILE *file){
    char buffer[BUFFER_SIZE];
    int counter = 0;
    while(1){
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