#pragma once

typedef struct _Graph Graph;

Graph* Graph_new(int);

void Graph_add_edge(Graph* graph, int source, int dest, int weight);

void Graph_remove_edge(Graph* g, int source, int dest);

int Graph_dfs(Graph* g ,int node, int arrival, int* depth, int* weight_array);

int Graph_LCA(Graph* g, int a, int b, int* depth, int* weight_array, int level, int weight, int test);

void Graph_print_parent(Graph* g, int nodes_number, int* depth, int* weight_array);

void Graph_print(Graph* g);

int Graph_max_edge(Graph* g);

