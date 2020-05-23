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

	return result;
}

void Graph_print(Graph* g){

	for(int i = 1; i <= g->n_vertex; i++){
		Node* adj = g->array[POS(i)];
		printf("%d: ", i);
		while(adj != NULL){
			printf("%d -> ", adj->key);
			adj = adj->next;
		}
		printf("\n");
	}
}

void Graph_add_edge(Graph* g, int source, int dest, int weight){
	Node* new_node_dest = Node_new(dest, weight);
	Node* new_node_source = Node_new(source, weight);

	list_insert(&(g->array[POS(source)]), &new_node_dest);
	list_insert(&(g->array[POS(dest)]), &new_node_source);
}

void Graph_remove_edge(Graph* g, int source, int dest){
	list_remove(&(g->array[source]));
	list_remove(&(g->array[dest]));
}

int Graph_dfs(Graph* g ,int node, int arrival, int* depth) {

	Node* current = g->array[POS(node)];

	depth[POS(node)] = depth[POS(arrival)] + 1; // set depth
	if(arrival != 0)
		current->parent = arrival; // set parent

	printf("%d\n", node); // node visited

	int height = 0;

	while(current != NULL){
		// printf("Checko %d con %d\n", current->key, arrival);
		if(current->key != arrival){
			height = max(height, Graph_dfs(g, current->key, node, depth));
		}
		current = current->next;
	}

	return height + 1;
}

int Graph_LCA(Graph* g, int a, int b, int* depth, int level){

	int diff;

    if (depth[POS(b)] < depth[POS(a)]){
    	SWAP(a,b)
    }

	for (int i = 0; i < level; i++){
		diff = depth[POS(b)] - depth[POS(a)];
	    if (diff == 0){
	    	break; 
	    }

	    b = g->array[POS(b)]->parent;
	}

	if (a == b) 
	    return a;
    
    Node* first = g->array[POS(a)];
    Node* second = g->array[POS(b)];
  
    for (int i = level - 1; i >= 0; i--){
        if (first->parent != second->parent){
            first = g->array[POS(first->parent)];
            second = g->array[POS(second->parent)];
        }
    }

    return first->parent; 
}

void Graph_print_parent(Graph* g, int nodes_number ,int* depth){

	for(int i = 1; i <= nodes_number; i++){
		printf("%d : Parent: %d, Depth: %d\n",i ,g->array[POS(i)]->parent, depth[POS(i)]);
	}
	
}