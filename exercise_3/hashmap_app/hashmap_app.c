#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hashmap.h"

#define ERROR_EXIT_CODE 1

#define SIZE_KEYS 6321078
#define TIME_START() time = clock();
#define TIME_END() time = clock() - time;
#define TIME_CHECK() ((double) time) / CLOCKS_PER_SEC
#define RAND_SIZE 10000000

#define SWAP(array, i, j) Record temp = array[i]; \
			   			  array[i] = array[j]; \
			   			  array[j] = temp;

#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

typedef struct {
    int key;
    int value;
} Record;

void print_usage() {
    printf("hashmap_app <filename>\n");
}

int hash_fun(int* key){
	return *key;
}

int compare_keys(int* obj1 , int* obj2){
    return *obj1 - *obj2;
}

int partition(Record array[], int start, int end){
	int i = start + 1;
	int j = end;

	while(i <= j){
		if(array[i].key <= array[start].key) i++;
		else if(array[j].key > array[start].key) j--;
		else{
			SWAP(array, i, j)
			i++;
			j--;
		}
	}

	SWAP(array, start, j)

	return j;
}

void quick_sort(Record array[], int start, int end){
	if(end > start){
		int p = partition(array, start, end);
		if(p > start)
			quick_sort(array, start, p-1);
		if(p < end - 1)
			quick_sort(array, p+1, end);
	}
}

int binary_search(Record array[], int start, int end, int x){
	while (start <= end) { 
        int mid = start + (end - start) / 2; 
        if (array[mid].key == x) 
        	return mid; 
        if (array[mid].key < x) 
            start = mid + 1; 
        else
            end = mid - 1; 
    }

    return -1;
}

void load_data_hashmap(HashMap* hashmap , const char* filename){
	FILE* file = fopen(filename, "r");
    int* key;
    int* value;
    int lineno = 0;

    while(!feof(file)) {
    	key = (int*) malloc(sizeof(*key));
    	value = (int*) malloc(sizeof(*value));

        int n = fscanf(file, "%d,%d\n", key, value);
        lineno++;
        if(n != 2) {
            if(feof(file)) {
                continue;
            }

            printf("Error while reading file at line: %d\n", lineno);
            exit(ERROR_EXIT_CODE);
        }

        HashMap_insert(hashmap, key, value);
    }
}

void load_data_array(Record array[], const char* filename){
	FILE* file = fopen(filename, "r");
    int lineno = 0;
   
    while(!feof(file)) {
    	Record record;

        int n = fscanf(file, "%d,%d\n", &record.key, &record.value);
        lineno++;
        if(n != 2) {
            if(feof(file)) {
                continue;
            }

            printf("Error while reading file at line: %d\n", lineno);
            exit(ERROR_EXIT_CODE);
        }

        array[lineno - 1] = record;
    }
}

void load_keys(int* keys){
	for(int i = 0; i < RAND_SIZE; i++){
		keys[i] = rand() % RAND_SIZE+1;
	}
}

int* get_keys_hashmap(HashMap* hashmap, int* keys){
	int* hashmap_get_keys = (int*) malloc(sizeof(int) * RAND_SIZE);
	int* value;
	int j = 0;
	for(int i = 0; i < RAND_SIZE; i++){
		value = (int*) HashMap_get(hashmap, &keys[i]);
		if(value != NULL){
			hashmap_get_keys[j] = *value;
			j++;
		}
	}

	return hashmap_get_keys;
}

int* get_keys_array(Record array[], int* keys){
	int* array_get_keys = (int*) malloc(sizeof(int) * RAND_SIZE);
	int index;
	int j = 0;
	for(int i = 0;i < RAND_SIZE; i++){
		index = binary_search(array, 0, SIZE_KEYS - 1, keys[i]);
		if(index != -1){
			array_get_keys[j] = array[index].value;
			j++;
		}
	}

	return array_get_keys;
}

void check_values(int* hashmap_get_keys, int* array_get_keys){
	int size_hashmap = ARRAY_SIZE(hashmap_get_keys);
	int size_array = ARRAY_SIZE(array_get_keys);

	if(size_hashmap == size_array){
		for(int i = 0; i < size_hashmap; i++){
			if(hashmap_get_keys[i] != array_get_keys[i]){
				printf("Arrays don't match\n");
				exit(ERROR_EXIT_CODE);
			}
		}
	}else{
		printf("Arrays don't match\n");
		exit(ERROR_EXIT_CODE);
	}
}

int main(int argc, char const *argv[]){
	time_t time;
	HashMap* hashmap = HashMap_new((HashFunction) hash_fun, (HashMapCmp) compare_keys);
	static Record array[SIZE_KEYS];
	int* keys = (int*) malloc(sizeof(int) * RAND_SIZE);
		
	TIME_START()
	load_data_hashmap(hashmap, argv[1]);
	TIME_END()
	printf("Load time HashMap: %f seconds\n", TIME_CHECK());

	TIME_START()
	load_data_array(array, argv[1]);
	TIME_END()
	printf("Load time static Array: %f seconds\n", TIME_CHECK());

	TIME_START()
	quick_sort(array, 0, SIZE_KEYS);
	TIME_END()
	printf("Sorting static Array time: %f seconds\n", TIME_CHECK());

	load_keys(keys);
	printf("Keys generated correctly!\n");

	TIME_START()
	int* hashmap_get_keys = get_keys_hashmap(hashmap, keys);
	TIME_END()
	printf("Get values HashMap time: %f seconds\n", TIME_CHECK());

	TIME_START()
	int* array_get_keys = get_keys_array(array, keys);
	TIME_END()
	printf("Get values static array time: %f seconds\n", TIME_CHECK());
	
	check_values(hashmap_get_keys, array_get_keys);
	printf("Arrays checked correctly\n");
}