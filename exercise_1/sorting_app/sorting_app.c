#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting.h"
#include "dyn_array.h"

#define ERROR_EXIT_CODE 1

#define TIME_START() time = clock();
#define TIME_END() time = clock() - time;
#define TIME_CHECK() ((double) time) / CLOCKS_PER_SEC

// Defines the type of records read from file
typedef struct {
    char* first_field;
    int second_field;
    float third_field;
} Record;

// Options accepted by this program
typedef struct {
    SortingCmp comparison_fun;  	// comparison function used to sort by field 
    int alghoritm;					// type of sorting alghoritm
    char const* filename;           // name of the file to be read
} Options;

int compare_first_field(Record* rec1, Record* rec2) {
    return strcmp(rec1->first_field, rec2->first_field);
}

int compare_second_field(Record* rec1, Record* rec2) {
	return rec1->second_field - rec2->second_field;
}

int compare_third_field(Record* rec1, Record* rec2) {
	float result = rec1->third_field - rec2->third_field;

	if(result > 0) 
		return 1;
	else if(result < 0) 
		return -1;
	else 
		return 0;
}

void print_usage() {
    printf("sorting_app < -i | -q > < -1 | -2 | -3 > <filename>\n");
    printf("    -i: sorting values using insertion sort\n");
    printf("    -q: sorting values using quick-sort\n");
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

    if( !strcmp(argv[1], "-i") ) {
        options.alghoritm = 0;
    } else if( !strcmp(argv[1], "-q" ) ) {
        options.alghoritm = 1;
    } else {
        printf("Parameters error");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    if( !strcmp(argv[2], "-1") ) {
        options.comparison_fun = (SortingCmp) compare_first_field;
    } else if( !strcmp(argv[2], "-2" ) ) {
        options.comparison_fun = (SortingCmp) compare_second_field;
    } else if( !strcmp(argv[2], "-3" ) ){
    	options.comparison_fun = (SortingCmp) compare_third_field;
    } else {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    options.filename = argv[3];

    return options;
}

void load_data( DynArray* array, char const* filename ) {
    FILE* file = fopen(filename, "r");

    #define MAX_BUF_LEN 1024

    char first_field[MAX_BUF_LEN];
    int second_field;
    float third_field;

    int lineno = 0;
    while(!feof(file)) {

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

        DynArray_insert(array, record);
    }
}
 
void print_array(DynArray* array) {
    for(int i=0; i < DynArray_size(array); i++) {
        Record* rec = DynArray_get(array, i);
        printf("First: %30s\t", rec->first_field);
        printf("Second: %10d\t", rec->second_field);
        printf("Third: %20f\n",rec->third_field);
    }
}

void free_data(DynArray* array) {
    for(int i=0; i<DynArray_size(array); i++) {
        Record* rec = DynArray_get(array, i);
        free(rec->first_field);
        free(rec);
    }

    DynArray_free(array);
}

// MAIN
// Usage: sorting_app < -i | -q > < -1 | -2 > <filename>
int main(int argc, char const *argv[]){

	Options options = parse_options(argc, argv);
    DynArray* array = DynArray_new();
    time_t time;

	load_data(array, options.filename);

	TIME_START()
    if(options.alghoritm)
        quick_sort(DynArray_get_raw_array(array), DynArray_size(array), (SortingCmp) options.comparison_fun);
    else
        insertion_sort(DynArray_get_raw_array(array), DynArray_size(array), (SortingCmp) options.comparison_fun);
    TIME_END()

    free_data(array);

    printf("The method took %f seconds\n", TIME_CHECK());
}