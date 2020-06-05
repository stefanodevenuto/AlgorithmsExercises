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

// Structure to store Record association
typedef struct {
    int key;	// Key of the association
    int value;	// Value of the association
} Record;

static int* int_new(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;

    return result;
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
        int mid = (start + end) / 2; 
        if (array[mid].key == x) 
        	return mid; 
        if (array[mid].key < x) 
            start = mid + 1; 
        else
            end = mid - 1; 
    }

    return -1;
}

void print_usage() {
    printf("Usage: hashmap_app <filename>\n");
}

char const* parse_options(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    char const* filename = argv[1];
    return filename;
}

// Load the Records in the Hashmap
void load_data_hashmap(HashMap* hashmap , const char* filename){
	FILE* file = fopen(filename, "r");
    int lineno = 0;
    int key;
    int value;
    time_t time;
    
    TIME_START()

    while(!feof(file)) {
        int n = fscanf(file, "%d,%d\n", &key, &value);
        lineno++;
        if(n != 2) {
            if(feof(file)) {
                continue;
            }

            printf("Error while reading file at line: %d\n", lineno);
            exit(ERROR_EXIT_CODE);
        }

        HashMap_insert(hashmap, int_new(key), int_new(value));
    }

    TIME_END()
	printf("Load time HashMap: %f seconds\n", TIME_CHECK());
}

// Load the Records in the Static Array
void load_data_array(Record array[], const char* filename){
	FILE* file = fopen(filename, "r");
    int lineno = 0;
    time_t time;
    
    TIME_START()
   
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

    TIME_END()
	printf("Load time static Array: %f seconds\n", TIME_CHECK());

}

// Generate random keys to retrieve
void load_keys(int* keys){
	srand(time(NULL));
	for(int i = 0; i < RAND_SIZE; i++){
		keys[i] = rand() % (RAND_SIZE+1);
	}
}

//Retrieve the association from the HashMap
int get_values_hashmap(HashMap* hashmap, int* hashmap_values, int* keys){
	void* value;
	int n_value = 0;
	time_t time;
	
	TIME_START()

	for(int i = 0; i < RAND_SIZE; i++){
		value = HashMap_get(hashmap, &keys[i]);
		if(value != NULL){
			hashmap_values[n_value] = *(int*)value;
			n_value++;
		}
	}

	TIME_END()
	printf("HashMap got %d values in %f seconds\n", n_value,TIME_CHECK());

	return n_value;
}

// Retrieve the association from the Static Array
int get_values_array(Record array[], int* array_values, int* keys){
	int index;
	int n_value = 0;
	time_t time;

	TIME_START()

	for(int i = 0; i < RAND_SIZE; i++){
		index = binary_search(array, 0, SIZE_KEYS-1, keys[i]);
		if(index != -1){
			array_values[n_value] = array[index].value;
			n_value++;
		}
	}

	TIME_END()
	printf("Static array got %d values in %f seconds\n", n_value, TIME_CHECK());

	return n_value;
}

// Compare the resulting values from the two structures
int check_values(int* hashmap_values, int* array_values, int hashmap_value_size, int array_value_size){

	if(hashmap_value_size != array_value_size){
		printf("Arrays don't match , different sizes");
		return 0;
	}
	
	for(int i = 0; i < hashmap_value_size; i++){
		if(hashmap_values[i] != array_values[i]){
			printf("Arrays don't match at %d position\n", i+1);
			return 0;
		}
	}

	return 1;
}

void free_data(HashMap* hashmap, int* keys, int* hashmap_values, int* array_values){
	free(keys);
	free(hashmap_values);
	free(array_values);

	int** hashmap_keys = (int**) malloc(sizeof(*hashmap_keys) * HashMap_size(hashmap));
	HashMap_get_all_keys(hashmap, (void**) hashmap_keys);

	for(int i = 0; i < HashMap_size(hashmap); i++){
		int* value = HashMap_get(hashmap, hashmap_keys[i]);
		free(value);
		free(hashmap_keys[i]);
	}

	free(hashmap_keys);
	HashMap_free(hashmap);
}

int main(int argc, char const *argv[]){

	char const* filename = parse_options(argc, argv);
	time_t time;

	HashMap* hashmap = HashMap_new((HashFunction) hash_fun, (HashMapCmp) compare_keys);
	static Record array[SIZE_KEYS];

	load_data_hashmap(hashmap, filename);
	
	load_data_array(array, filename);

	TIME_START()
	quick_sort(array, 0, SIZE_KEYS - 1);
	TIME_END()
	printf("Sorting static Array time: %f seconds\n", TIME_CHECK());

	int* keys = (int*) malloc(sizeof(int) * RAND_SIZE);
	load_keys(keys);
	printf("Keys generated correctly!\n");

	int* hashmap_values = (int*) malloc(sizeof(int) * RAND_SIZE);
	int hashmap_value_size = get_values_hashmap(hashmap, hashmap_values, keys);

	int* array_values = (int*) malloc(sizeof(int) * RAND_SIZE);
	int array_value_size = get_values_array(array, array_values, keys);
	
	if(check_values(hashmap_values, array_values, hashmap_value_size, array_value_size))
		printf("Arrays checked correctly\n");

	free_data(hashmap, keys, hashmap_values, array_values);
}