#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "sorting.h"

#define ERROR_EXIT_CODE 1

// Defines the type of records read from file
typedef struct {
    int id;
    char* first_field;
    int second_field;
    float third_field;
} Record;

typedef struct {
	int size;
	Record** records;
} RecordArray;

typedef struct {
    SortingCmp comparison_fun;  	// comparison function to be used 
                                    // when sorting the array by field
    int type;						// type of sorting alghoritm
    char const* filename;           // name of the file to be read
} Options;

int compare_first_field(Record* rec1, Record* rec2) {
    return strcmp(rec1->first_field, rec2->first_field);
}

int compare_second_field(Record* rec1, Record* rec2) {
	return rec1->second_field - rec2->second_field;
}

float compare_third_field(Record* rec1, Record* rec2) {
	return rec1->third_field - rec2->third_field;
}

void print_usage() {
    printf("sorting_app < -i | -q > < -1 | -2 | -3 > <filename>\n");
    printf("    -i: sorting values using insertion sort\n");
    printf("    -q: sorting values using quick-sort\n");
    printf("\n");
    printf("    -1: sort according to the first field ascending order\n");
    printf("    -2: sort according to the second field ascending order\n");
    printf("    -3: sort according to the third field ascending order\n");
}

Options parse_options(int argc, char const *argv[]) {
    if(argc != 4) {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    Options options;

    if( !strcmp(argv[2], "-1") ) {
        options.comparison_fun = (SortingCmp) compare_first_field;
    } else if( !strcmp(argv[2], "-2" ) ) {
        options.comparison_fun = (SortingCmp) compare_second_field;
    } else if( !strcmp(argv[2], "-2" ) ){
    	options.comparison_fun = (SortingCmp) compare_second_field;
    } else {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    options.filename = argv[3];

    return options;
}

RecordArray* load_data(char const* filename ) {
    FILE* file = fopen(filename, "r");

    RecordArray* array = (RecordArray*) malloc(sizeof(RecordArray));
    array->records = (Record**) malloc(sizeof(Record*));

    #define MAX_BUF_LEN 1024

    char first_field[MAX_BUF_LEN];
    int second_field;
    float third_field;

    int lineno = 0;
    for(int i = 0; i < 30; i++){
    //while(!feof(file)) {
        Record* record = (Record*) malloc(sizeof(Record));

        int n = fscanf(file, "%*d,%1024[^,],%d,%f\n", first_field, &second_field, &third_field);
        lineno++;

        if(n != 3) {
            if(feof(file)) {
                continue;
            }

            printf("Error while reading file at line: %d\n", lineno);
            exit(ERROR_EXIT_CODE);
        }

        record->first_field = strndup(first_field, MAX_BUF_LEN);
        record->second_field = second_field;
        record->third_field = third_field;

        array->records = (Record**) realloc(array->records, sizeof(Record*) * lineno);

        array->records[lineno - 1] = record;
    }

    array->size = lineno;

    return array;
}
 
void print_array(RecordArray* array) {
	printf("STAMPA\n");
    for(int i=0; i < array->size; i++) {
        Record* rec = array->records[i];
        printf("ID: %d\t", i+1);
        printf("first: %30s\t", rec->first_field);
        printf("second: %10d\t", rec->second_field);
        printf("third: %20f\n",rec->third_field);
    }
}

void free_data(RecordArray* array) {
    for(int i=0; i<array->size; i++) {
        Record* rec = array->records[i];
        free(rec->first_field);
        free(rec);
    }

    free(array->records);
    free(array);
}

int main(int argc, char const *argv[]){

	RecordArray* array = load_data(argv[1]);
	//ciao(array);
	//Record* rec = array[0];
	//printf("second: %d\n", rec->second_field);

	printf("FINE LOAD\n");
	
	//printf("size: %d\n", size);
	//print_array(array);
	printf("Sorting...\n");

    //insertion_sort((void**)array->records, array->size, (SortingCmp) compare_first_field);
    //insertion_sort((void**)array->records, array->size, (SortingCmp) compare_second_field);
    quick_sort((void**)array->records, array->size, (SortingCmp) compare_second_field);
    //insertion_sort((void**)array->records, array->size, (SortingCmp) compare_third_field);

    print_array(array);
    free_data(array);
}