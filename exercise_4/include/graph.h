#pragma once

typedef struct _Graph Graph;

Graph* Graph_new(int);

void Graph_add_edge(Graph* graph, int source, int dest, int weight);

void Graph_remove_edge(Graph* g, int source, int dest);

int Graph_dfs(Graph* g ,int node, int arrival, int* depth);

int Graph_LCA(Graph* g, int a, int b, int* depth, int level, int weight);

void Graph_print_parent(Graph* g, int nodes_number, int* depth);

void Graph_print(Graph* g);

