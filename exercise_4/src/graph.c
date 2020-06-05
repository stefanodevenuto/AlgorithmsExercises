#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define POS(x) x - 1
#define SWAP(a, b) int temp = a; \
				   a = b; \
				   b = temp;

typedef struct _Node{
	int key;
	int weight;
	struct _Node* next;
	int parent;
	int depth;
}Node;

typedef struct _Graph{
	int n_vertex;
	int max_edge;
	Node** array;
}Graph;

static void list_insert(Node** head, Node** new_node){
	(*new_node)->next = *head;
	*head = *new_node;
}

static void list_remove(Node** head){
	Node* tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

static int max(int a, int b){
	if(a > b) return a;
	else return b;
}

Node* Node_new(int key, int weight){
	Node* node = (Node*) malloc(sizeof(Node));
	node->key = key;
	node->weight = weight;
	node->next = NULL;
	node->parent = -1;

	return node;
}

Graph* Graph_new(int n_vertex){
	Graph* result = (Graph*) malloc(sizeof(Graph));
	result->array = (Node**) calloc(n_vertex, sizeof(Node*));
	result->n_vertex = n_vertex;
	result->max_edge = -1;

	return result;
}

void Graph_print(Graph* g){

	for(int i = 1; i <= g->n_vertex; i++){
		Node* adj = g->array[POS(i)];
		printf("%d:\t", i);
		while(adj != NULL){
			printf("%d | %d -> ", adj->key, adj->weight);
			adj = adj->next;
		}
		printf("\n");
	}
}

void Graph_add_edge(Graph* g, int source, int dest, int weight){
	Node* new_node_dest = Node_new(dest, weight);
	Node* new_node_source = Node_new(source, weight);

	if(weight > g->max_edge)
		g->max_edge = weight;

	list_insert(&(g->array[POS(source)]), &new_node_dest);
	list_insert(&(g->array[POS(dest)]), &new_node_source);
}

int Graph_dfs(Graph* g ,int node, int parent, int* depth, int* weight_array) {

	Node* current = g->array[POS(node)];

	if(POS(parent) == -1)
		depth[POS(node)] = 1;
	else
		depth[POS(node)] = depth[POS(parent)] + 1;

	if(parent != 0){
		current->parent = parent;
	}

	int height = 0;

	while(current != NULL){
		
		if(current->key != parent){
			height = max(height, Graph_dfs(g, current->key, node, depth, weight_array));
		}

		if(current->key == parent){
			weight_array[POS(node)] = current->weight;
		}
		current = current->next;
	}

	return height + 1;
}

int Graph_answer_query(Graph* g, int first, int second, int* depth, int* weight_array, int level, int weight, int test){

	int diff;

    if (depth[POS(second)] < depth[POS(first)]){
    	SWAP(first,second)
    }

	for (int i = 0; i < level; i++){
		diff = depth[POS(second)] - depth[POS(first)];

	    if (diff == 0) break; 
	    
	    if(weight_array[POS(second)] > weight)
	    	return 1;

	    second = g->array[POS(second)]->parent;
	}

	if (first == second)
		return 0;
  
    for (int i = level - 1; i >= 0; i--){
        if (first != second){
        	
        	if(weight_array[POS(first)] > weight || weight_array[POS(second)] > weight){
        		return 1;
        	}

            first = g->array[POS(first)]->parent;
            second = g->array[POS(second)]->parent;
        }else break;
    }

    return 0; 
}

int Graph_max_edge(Graph* g){
	return g->max_edge;
}