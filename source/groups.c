#include "../headers/groups.h"

struct groups{
    List **groups;
    int k;
};

Groups *groups_create(int k){
    Groups *gps = malloc(sizeof(Groups));
    gps->groups = malloc(sizeof(List*) * k);
    gps->k = k;
    for(int i = 0; i < k; i++){
        gps->groups[i] = list_construct();
    }
    return gps;
}

void groups_msca(Groups *gps, Vertex **vertices, int vertices_qtt, DisjointSet *ds){
    char *aux = vertex_get_id(vertices[_find(ds, 0)]);  // get the first vertex of the k-set

    Queue *writed = queue_construct();
    queue_enqueue(writed, aux);

    for(int i = 0; i < gps->k; i++){
    	for(int j = 0; j < vertices_qtt; j++){
    		if (strcmp(aux, vertex_get_id(vertices[_find(ds, j)])) == 0)
                list_push_back(gps->groups[i], vertex_get_id(vertices[j]));   // enqueue the vertices of the k-set
        } 

        for(int j = 0; j < vertices_qtt; j++){
    		if (strcmp(aux, vertex_get_id(vertices[_find(ds, j)])) != 0 && !queue_find(writed, vertex_get_id(vertices[_find(ds, j)]))){
                queue_enqueue(writed, aux);   // enqueue the vertices of the k-set
                aux = vertex_get_id(vertices[_find(ds, j)]);
                break;
            }
        }
    }

    queue_destroy(writed);
}

void groups_output(Groups *gps, char *output_file_path){
    FILE *output = fopen(output_file_path, "w+");
    if(!output)
         exit(printf("ERROR: File %s did not open", output_file_path));

    for(int k = 0; k < gps->k; k++){
        for (int i = 0; i < list_size(gps->groups[k]); i++)
        {
            char *aux = list_get(gps->groups[k], i);
            if (i == list_size(gps->groups[k]) - 1)
                fprintf(output, "%s", aux);
            
            fprintf(output, "%s,", aux);
        }

        fprintf(output, "\n");
    }

    fclose(output);
}

void groups_destroy(Groups *gps){
    for(int i = 0; i < gps->k; i++){
        list_destroy(gps->groups[i]);
    }
    free(gps->groups);
    free(gps);
}