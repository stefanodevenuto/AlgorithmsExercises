#pragma once

typedef struct _HashMap HashMap;
typedef int (*HashFunction)(void*) ;
typedef int (*HashMapCmp)(void*, void*) ;

HashMap* HashMap_new(HashFunction, HashMapCmp);

void HashMap_free(HashMap* hm);

int HashMap_ispresent(HashMap* hm, void* key);

void HashMap_insert(HashMap* hm, void* key, void* value);

void HashMap_remove(HashMap* hm, void* key);

void* HashMap_get(HashMap* hm, void* key);

int HashMap_empty(HashMap* hm);

int HashMap_size(HashMap* hm);

void HashMap_remove_all(HashMap* hm);

void** HashMap_get_all_keys(HashMap* hm);

