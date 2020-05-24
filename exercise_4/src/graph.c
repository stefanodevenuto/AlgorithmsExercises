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

int Graph_dfs(Graph* g ,int node, int arrival, int* depth, int* weight_array) {

	Node* current = g->array[POS(node)];

	if(POS(arrival) == -1)
		depth[POS(node)] = 1;
	else
		depth[POS(node)] = depth[POS(arrival)] + 1; // set depth

	if(arrival != 0){
		current->parent = arrival; // set parent
	}

	int height = 0;

	while(current != NULL){
		
		if(current->key != arrival){
			height = max(height, Graph_dfs(g, current->key, node, depth, weight_array));
		}

		if(current->key == arrival){
			weight_array[POS(node)] = current->weight;
		}
		current = current->next;
	}

	return height + 1;
}

int Graph_LCA(Graph* g, int a, int b, int* depth, int* weight_array, int level, int weight, int test){

	int diff;

    if (depth[POS(b)] < depth[POS(a)]){
    	SWAP(a,b)
    }

	for (int i = 0; i < level; i++){
		diff = depth[POS(b)] - depth[POS(a)];

	    if (diff == 0) break; 
	    
	    if(weight_array[POS(b)] > weight)
	    	return 1;

	    b = g->array[POS(b)]->parent;
	}

	if (a == b)
		return 0;
  
    for (int i = level - 1; i >= 0; i--){
        if (a != b){
        	
        	if(weight_array[POS(a)] > weight || weight_array[POS(b)] > weight){
        		return 1;
        	}

            a = g->array[POS(a)]->parent;
            b = g->array[POS(b)]->parent;
        }else break;
    }

    return 0; 
}

int Graph_max_edge(Graph* g){
	return g->max_edge;
}

void Graph_print_parent(Graph* g, int nodes_number ,int* depth, int* weight_array){
	int peso = -1;
	for(int i = 1; i <= nodes_number; i++){
		if(g->array[POS(g->array[POS(i)]->parent)] != NULL){
			peso = g->array[POS(g->array[POS(i)]->parent)]->weight;
		}else peso = -1;
		printf("%d : Parent: %d, Weight: %d, Depth: %d\n",i ,g->array[POS(i)]->parent, peso, depth[POS(i)]);
	}
	printf("PROVE\n");
	
	for(int i = 1; i <= nodes_number; i++){
		printf("Node: %d, Parent: %d, Weight: %d\n", i, g->array[POS(i)]->parent, weight_array[POS(i)]);
	}
	
}