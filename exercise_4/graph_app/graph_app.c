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

Graph* load_tree(){

	//FILE* file = fopen(filename, "r");

    int nodes_number;
    int query_number;
    int source;
    int dest;
    int weight;

    int n = fscanf(stdin, "%d\n", &nodes_number);

    Graph* graph = Graph_new(nodes_number);
    int* depth = (int*) calloc(nodes_number, sizeof(int));
    int* weight_array = (int*) malloc(nodes_number * sizeof(int));

    memset(weight_array, -1, nodes_number * sizeof(int));  // non serve, FUNZIONA SENZA

    for(int i = 0; i < nodes_number-1; i++){                        // -1 poichè vi sono N-1 archi
        n = fscanf(stdin, "%d %d %d\n", &source, &dest, &weight);
        Graph_add_edge(graph, source, dest, weight);
    }

    int max_edge = Graph_max_edge(graph);

    int level = Graph_dfs(graph, 1, 0, depth, weight_array);

    int lca = 0;

    n = fscanf(stdin, "%d\n", &query_number);

    for(int i = 0; i < query_number; i++){
        n = fscanf(stdin, "%d %d %d\n", &source, &dest, &weight);
        if(weight > max_edge)
            printf("NO\n");
        else{
            lca = Graph_LCA(graph, source, dest, depth, weight_array, level, weight, i+1);

            if(lca){
                printf("YES\n");
            }else{
                printf("NO\n");
            }
        }
    }
}


int main(int argc, char const *argv[] ){
	//char const* input_filename = parse_options(argc, argv);
    time_t  time;
    TIME_START()
	Graph* graph = load_tree();
    TIME_END()
    //printf("Load time Graph: %f seconds\n", TIME_CHECK());
}
