#include <stdlib.h>
#include "hashmap.h"

#define INITIAL_CAPACITY 100

#define FREE_NODE(x) HashNode* tmp; \
					 tmp = x; \
					 x = x->next; \
					 free(x);

typedef struct _HashNode{
	void* key;
	void* value;
	struct _HashNode* next;
	struct _HashNode* prev;
} HashNode;

struct _HashMap{
	HashNode** array;
	int capacity;
	int size;
	HashFunction hashfun;
	HashMapCmp compare;
};

HashNode* HashNode_new(void* key, void* value){
	HashNode* hnode = (HashNode*) malloc(sizeof(HashNode));
	hnode->key = key;
	hnode->value = value;
	hnode->next = NULL;

	return hnode;
}

HashMap* HashMap_new(HashFunction hashfun, HashMapCmp compare){
	HashMap* result = (HashMap*) malloc(sizeof(HashMap));
	result->capacity = INITIAL_CAPACITY;
	result->array = (HashNode**) malloc(sizeof(HashNode*) * result->capacity);
	result->size = 0;
	result->hashfun = hashfun;
	result->compare = compare;

	return result;
}

void HashMap_free(HashMap* hm){
	for(int i = 0; i < hm->capacity; i++){
		if(hm->array[i] != NULL){
			HashNode* head = hm->array[i];
			HashNode* tmp;
			while(head != NULL){
				FREE_NODE(head);
			}
		}
	}

	free(hm->array);
	free(hm);
}

int HashMap_empty(HashMap* hm){
	return hm->size == 0;
}

int HashMap_size(HashMap* hm){
	return hm->size;
}

void list_insert(HashNode* head, HashNode* new_hnode){
	new_hnode->next = head;
	new_hnode->prev = NULL;
	head->prev = new_hnode;
	head = new_hnode;
}

void list_remove(HashNode* head, void* key){
	
}

void HashMap_insert(HashMap* hm, void* key, void* value){
	int position = hm->hashfun(key) % hm->capacity;

	HashNode* new_hnode = HashNode_new(key, value);

	list_insert(hm->array[position], new_hnode);
}

void HashMap_remove(HashMap* hm, void* key){
	int position = hm->hashfun(key) % hm->capacity;

	list_remove(hm->array[position], key);
}
