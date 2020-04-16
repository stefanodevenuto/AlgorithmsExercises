#include <stdlib.h>
#include <stdio.h>
#include "../include/hashmap.h"

#define INITIAL_CAPACITY 6321078

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

HashMap* HashMap_new(HashFunction hashfun, HashMapCmp compare){
	HashMap* result = (HashMap*) malloc(sizeof(HashMap));
	result->capacity = INITIAL_CAPACITY;
	result->array = (HashNode**) calloc(result->capacity, sizeof(HashNode*));
	result->size = 0;
	result->hashfun = hashfun;
	result->compare = compare;

	return result;
}

void list_free(HashNode* head){
	while(head != NULL){
		FREE_NODE(head)
	}
}

void list_insert(HashNode** head, HashNode** new_hnode){
	(*new_hnode)->next = *head;
	(*new_hnode)->prev = NULL;
	if(*head != NULL)
		(*head)->prev = *new_hnode;
	*head = *new_hnode;
}

void list_remove(HashNode** head, HashNode** hnode){
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

int HashMap_ispresent(HashMap* hm, void* key){
	int position = hm->hashfun(key) % hm->capacity;

	if(list_search(hm->array[position], key, hm->compare) == NULL) return 0;

	return 1;
}

void HashMap_insert(HashMap* hm, void* key, void* value){

	if(!HashMap_ispresent(hm, key)){
		int position = hm->hashfun(key) % hm->capacity;
		HashNode* new_hnode = HashNode_new(key, value);
		list_insert(&hm->array[position], &new_hnode);
		hm->size++;
	}
}

void HashMap_remove(HashMap* hm, void* key){
	int position = hm->hashfun(key) % hm->capacity;
	HashNode* result = list_search(hm->array[position], key, hm->compare);
	if(result != NULL){
		list_remove(&hm->array[position], &result);
		hm->size--;
	}
}

void* HashMap_get(HashMap* hm, void* key){
	int position = hm->hashfun(key) % hm->capacity;
	HashNode* result = list_search(hm->array[position], key, hm->compare);
	if(result != NULL)
		return result->value;
	else
		return 0;
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