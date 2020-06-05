#pragma once

typedef struct _Graph Graph;

/*
 * Create a new Graph structure
 */
Graph* Graph_new(int);

/*
 * Add a weighted edge from a node
 * to another the Graph  
 */
void Graph_add_edge(Graph* graph, int source, int dest, int weight);

/*
 * Make a DFS visit of the Graph
 *
 */
int Graph_dfs(Graph* g ,int node, int arrival, int* depth, int* weight_array);

/*
 * Answer the given query by an adapted
 * version of the LCA alghoritm
 */
int Graph_answer_query(Graph* g, int a, int b, int* depth, int* weight_array, int level, int weight, int test);

/*
 * Print the Graph
 */
void Graph_print(Graph* g);

/*
 * Returns the weight of the edge 
 * of the most heavy one 
 */
int Graph_max_edge(Graph* g);

