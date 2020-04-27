#pragma once

typedef struct _HashMap HashMap;
typedef int (*HashFunction)(void*) ;
typedef int (*HashMapCmp)(void*, void*) ;

/*
 * Create a new HashMap.
 * Parameters:
 * 	  HashFunction is pointer to a function that
 *	  return a number given a key.
 *    HashMapCmp is a pointer to a function that
 *	  compare two keys in the hashmap. The library assumes
 *	  that the function returns 0 if they are equal.
 */
HashMap* HashMap_new(HashFunction, HashMapCmp, int);

/*
 * Frees the memory allocated by HashMap_new.
 * Note: it does not frees the memory of the objects
 *       key and value in the hashmap.
 */
void HashMap_free(HashMap* hm);

/*
 * Check if an association is present
 * passing a key. Returns 1 if is present,
 * 0 otherwise.
 */
int HashMap_ispresent(HashMap* hm, void* key);

/*
 * Insert a new <key,value> association 
 * in the hashmap. Requires the addres of
 * the Hash Map.
 */
void HashMap_insert(HashMap* hm, void* key, void* value);

/*
 * Remove an association given a key.
 */
void HashMap_remove(HashMap* hm, void* key);

/*
 * Get the value of an association given a key.
 * Note: it returns 0 if the association with
 * 		 that key is not present in the hashmap. 
 */
void* HashMap_get(HashMap* hm, void* key);

/*
 * Check if the hashmap has no associations. 
 * Returns 1 if that condition is true,
 * 0 otherwise.
 */
int HashMap_empty(HashMap* hm);

/*
 * Returns the number of association
 * currently present in the hasmap.
 */
int HashMap_size(HashMap* hm);

/*
 * Remove all the association in the hashmap
 */
void HashMap_remove_all(HashMap* hm);

/*
 * Returns all the keys used in the associations,
 * in the form of an array.
 * Note: the array is allocated dinamically and
 *		 must be freed.
 */
void** HashMap_get_all_keys(HashMap* hm);

