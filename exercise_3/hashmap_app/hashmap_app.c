#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hashmap.h"

#define ERROR_EXIT_CODE 1

typedef void (*loadingFunction)(void*, char const*);

typedef struct {
    loadingFunction load;
    int structure;
    char const* filename;           
} Options;

typedef struct {
    int key;
    int value;
} Record;

void print_usage() {
    printf("hashmap_app < -h | -a > <seed> <filename>\n");
    printf("    -h: use an hashmap to store the csv\n");
    printf("    -a: use a static array to store csv\n");
}

int hash_fun(int* key){
	return *key;
}

int compare_keys(int* obj1 , int* obj2){
    return *obj1 - *obj2;
}

void load_data_hashmap(HashMap* hashmap , char const* filename){
	FILE* file = fopen(filename, "r");

    int* key;
    int* value;
    int lineno = 0;
    while(!feof(file)) {
    //for(int i = 0; i < 3160568; i++){

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
        //printf("%d, %d\n", *key, *value);
        HashMap_insert(hashmap, key, value);
    }
}

void load_data_array(Record array[], char const* filename){
	FILE* file = fopen(filename, "r");

	int key;
	int value;
	int lineno = 0;
	while(!feof(file)) {
    //for(int i = 0; i < 3160568; i++){
		Record record;
    	int n = fscanf(file, "%d,%d\n", &record.key, &record.value);
    	lineno++;
    	
        //printf("%d, %d\n", key, value);
        if(n != 2) {
            if(feof(file)) {
                continue;
            }

            printf("Error while reading file at line: %d\n", lineno);
            exit(ERROR_EXIT_CODE);
        }
        //printf("%d\n", lineno - 1);
		array[lineno - 1] = record;
		//printf("ciao\n");
	}
}

Options parse_options(int argc, char const *argv[]) {
    if(argc != 3) {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    Options options;

    if( !strcmp(argv[1], "-h") ) {
        options.load = (loadingFunction) load_data_hashmap;
        options.structure = 1;
    } else if( !strcmp(argv[1], "-a" ) ) {
        options.load = (loadingFunction) load_data_array;
        options.structure = 0;
    } else {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    options.filename = argv[2];

    return options;
}

void print_keys(int** keys, int size){
	for(int i = 0; i < size; i++){
		printf("%d\n", *keys[i]);
	}
}

int main(int argc, char const *argv[]){
	Options option = parse_options(argc, argv);
	if(option.structure){
		HashMap* hashmap = HashMap_new((HashFunction) hash_fun, (HashMapCmp) compare_keys);
		time_t time;
		time = clock();
		option.load(hashmap, option.filename);
		time = clock() - time;
		printf("The method took %f seconds\n", ((double) time) / CLOCKS_PER_SEC);
		//int** keys = (int**) HashMap_get_all_keys(hashmap);
		//print_keys(keys, HashMap_size(hashmap));
	}else{
		static Record structure[6321078];
		time_t time;
		time = clock();
		option.load(structure, option.filename);
		time = clock() - time;
		printf("The method took %f seconds\n", ((double) time) / CLOCKS_PER_SEC);
	}
}