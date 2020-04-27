#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"

#define LOAD_FACTOR 0.75

#define FREE_NODE(hnode) HashNode* tmp; \
					 	 tmp = hnode; \
					 	 hnode = hnode->next; \
					 	 free(tmp); 

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
	int max_threshold;
	HashFunction hashfun;
	HashMapCmp compare;
};

HashNode* HashNode_new(void* key, void* value){
	HashNode* hnode = (HashNode*) malloc(sizeof(HashNode));
	hnode->key = key;
	hnode->value = value;
	hnode->next = NULL;
	hnode->prev = NULL;

	return hnode;
}

HashMap* HashMap_new(HashFunction hashfun, HashMapCmp compare, int capacity){
	HashMap* result = (HashMap*) malloc(sizeof(HashMap));
	result->capacity = capacity;
	result->array = (HashNode**) calloc(result->capacity, sizeof(HashNode*));
	result->size = 0;
	result->max_threshold = result->capacity * LOAD_FACTOR;
	result->hashfun = hashfun;
	result->compare = compare;

	return result;
}

static void list_free(HashNode* head){
	while(head != NULL){
		FREE_NODE(head)
	}
}

static void list_insert(HashNode** head, HashNode** new_hnode){
	(*new_hnode)->next = *head;
	(*new_hnode)->prev = NULL;
	if(*head != NULL)
		(*head)->prev = *new_hnode;
	*head = *new_hnode;
}

static void list_remove(HashNode** head, HashNode** hnode){
	if((*hnode)->prev != NULL)
		(*hnode)->prev->next = (*hnode)->next;
	else 
		*head = (*hnode)->next;
	if((*hnode)->next != NULL)
		(*hnode)->next->prev = (*hnode)->prev;
	free(*hnode);
}

HashNode* list_search(HashNode* head, void* key, HashMapCmp compare){
	while(head != NULL && compare(head->key, key) != 0)
		head = head->next;
	return head;
}

void HashMap_free(HashMap* hm){
	for(int i = 0; i < hm->capacity; i++)
		if(hm->array[i] != NULL)
			list_free(hm->array[i]);
		
	free(hm->array);
	free(hm);
}

int HashMap_empty(HashMap* hm){
	return hm->size == 0;
}

int HashMap_size(HashMap* hm){
	return hm->size;
}

static int get_position(HashMap* hm, void* key){
	return hm->hashfun(key) % hm->capacity;
}

int HashMap_ispresent(HashMap* hm, void* key){
	int position = hm->hashfun(key) % hm->capacity;

	if(list_search(hm->array[position], key, hm->compare) == NULL) return 0;

	return 1;
}

void rehash(HashMap* hm){
	hm->capacity *= 2;
	hm->size = 0;
	HashNode** new_array = (HashNode**) calloc(hm->capacity, sizeof(HashNode*));
	int position;
	for(int i = 0; i < hm->capacity / 2; i++){
		HashNode* head = hm->array[i];
		while(head != NULL){
			HashNode* next = head->next;

			position = get_position(hm, head->key);
			list_insert(&new_array[position], &head);
			hm->size++;

			head = next;
		}
	}

	hm->max_threshold = hm->capacity * LOAD_FACTOR;
	free(hm->array);
	hm->array = new_array;
}

void HashMap_insert(HashMap* hm, void* key, void* value){

	if(!HashMap_ispresent(hm, key)){
		int position = get_position(hm, key);
		HashNode* new_hnode = HashNode_new(key, value);
		list_insert(&(hm->array[position]), &new_hnode);
		hm->size++;
		if(hm->size == hm->max_threshold)
			rehash(hm);
	}else{
		int position = get_position(hm, key);
		HashNode* hnode = list_search(hm->array[position], key, hm->compare);
		hnode->value = value;
	}
}

void HashMap_remove(HashMap* hm, void* key){
	int position = get_position(hm, key);
	HashNode* result = list_search(hm->array[position], key, hm->compare);
	if(result != NULL){
		list_remove(&hm->array[position], &result);
		hm->size--;
	}
}

void* HashMap_get(HashMap* hm, void* key){
	int position = get_position(hm, key);
	HashNode* result = list_search(hm->array[position], key, hm->compare);
	if(result != NULL)
		return result->value;
	else
		return NULL;
}

void HashMap_remove_all(HashMap* hm){
	for(int i = 0; i < hm->capacity; i++){
		if(hm->array[i] != NULL){
			list_free(hm->array[i]);
			hm->array[i] = NULL;
		}
	}
	hm->size = 0;
}

void** HashMap_get_all_keys(HashMap* hm){
	void** keys = (void**) malloc(sizeof(void*) * hm->size);
	int k_i = 0;
	for(int i = 0; i < hm->capacity; i++){
		if(hm->array[i] != NULL){
			HashNode* head = hm->array[i];
			while(head != NULL){
				keys[k_i] = head->key;
				k_i++;
				head = head->next;
			}
		}
	}

	return keys;
}