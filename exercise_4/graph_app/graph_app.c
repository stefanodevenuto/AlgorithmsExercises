#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "graph.h"

#define TIME_START() time = clock();
#define TIME_END() time = clock() - time;
#define TIME_CHECK() ((double) time) / CLOCKS_PER_SEC

void print_usage() {
    printf("Usage: graph <filename>\n");
}

char const* parse_options(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("Parameters error\n");
        print_usage();
        exit(1);
    }

    char const* filename = argv[1];
    return filename;
}

Graph* load_tree(const char* filename){

	FILE* file = fopen(filename, "r");

    int nodes_number;
    int query_number;
    int source;
    int dest;
    int weight;

    int n = fscanf(file, "%d\n", &nodes_number);

    Graph* graph = Graph_new(nodes_number);
    int* depth = (int*) calloc(nodes_number, sizeof(int));
    int* weight_array = (int*) malloc(nodes_number * sizeof(int));

    memset(weight_array, -1, nodes_number * sizeof(int));

    for(int i = 0; i < nodes_number-1; i++){                        // -1 poichè vi sono N-1 archi
        n = fscanf(file, "%d %d %d\n", &source, &dest, &weight);
        Graph_add_edge(graph, source, dest, weight);
    }

    int level = Graph_dfs(graph, 1, 0, depth, weight_array);

    //Graph_print_parent(graph, nodes_number, depth);
    int lca = 0;

    n = fscanf(file, "%d\n", &query_number);

    //printf("LCA: %d\n", Graph_LCA(graph, 2, 5, depth, level, weight));

    for(int i = 0; i < query_number; i++){
        n = fscanf(file, "%d %d %d\n", &source, &dest, &weight);
        //level = Graph_dfs(graph, source, dest, depth);

        //printf("INTERROGAZIONE: %d -----> %d con costo %d\n", source, dest, weight);
        lca = Graph_LCA(graph, source, dest, depth, weight_array, level, weight, i+1);

        if(lca){
            printf("YES\n");
            //write YES
        }else{
            printf("NO\n");
            //write NO
        }
        //printf("LCA (%d, %d): %d\n", source, dest, );
    }

    //Graph_print_parent(graph, nodes_number ,depth, weight_array);
    //Graph_print(graph);
}


int main(int argc, char const *argv[] ){
	char const* input_filename = parse_options(argc, argv);
    time_t  time;
    TIME_START()
	Graph* graph = load_tree(input_filename);
    TIME_END()
    //printf("Load time Graph: %f seconds\n", TIME_CHECK());

    
    
    //Graph_dfs(graph, 2, 1);

	//answer_queries(tree);
}
