#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../Unity/unity.h"
#include "sorting.h"

static int* int_new(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;

    return result;
}

static int compare(int* obj1 , int* obj2){
	return *obj1 - *obj2;
}

static void print_int_array(int** array, int n_elem){
	for(int i = 0; i < n_elem; i++){
		printf("%d\t", *array[i]);
	}
	printf("\n");
}

static int** create_test(int n_elem, ...){

	va_list args;
	va_start(args, n_elem);

	int** result = (int**) malloc(sizeof(*result) * n_elem);

	for(int i = 0; i < n_elem; i++){
		result[i] = int_new(va_arg(args, int));
	}

	return result;
}

static void free_array(int** array, int n_elem){
	for(int i = 0; i < n_elem; i++){
		free(array[i]);
	}

	free(array);
}

static void sorting_array_insertion_sort_null_array(){
	int** array = NULL;

	insertion_sort((void**)array, 0, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(NULL, array);

	free_array(array, 0);
}

static void sorting_array_insertion_sort_one_sized_array(){
	int** array = create_test(1, 1);

	insertion_sort((void**)array, 1, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1, *array[0]);

	free_array(array, 1);
}

static void sorting_array_insertion_sort_ordered_array(){
	int** array = create_test(4, 1,2,3,4);

	insertion_sort((void**)array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1,  *array[0]);
	TEST_ASSERT_EQUAL(2,  *array[1]);
	TEST_ASSERT_EQUAL(3,  *array[2]);
	TEST_ASSERT_EQUAL(4,  *array[3]);

	free_array(array, 4);
}

static void sorting_array_insertion_sort_reversed_array(){
	int** array = create_test(4, 4,3,2,1);

	insertion_sort((void**)array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1,  *array[0]);
	TEST_ASSERT_EQUAL(2,  *array[1]);
	TEST_ASSERT_EQUAL(3,  *array[2]);
	TEST_ASSERT_EQUAL(4,  *array[3]);

	free_array(array, 4);
}

static void sorting_array_insertion_sort_random_array(){
	int** array = create_test(4, 3,6,1,7);

	insertion_sort((void**)array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1,  *array[0]);
	TEST_ASSERT_EQUAL(3,  *array[1]);
	TEST_ASSERT_EQUAL(6,  *array[2]);
	TEST_ASSERT_EQUAL(7,  *array[3]);

	free_array(array, 4);

}

static void sorting_array_quick_sort_null_array(){
	int** array = NULL;

	quick_sort((void**)array, 0, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(NULL, array);

	free_array(array, 0);
}

static void sorting_array_quick_sort_one_sized_array(){
	int** array = create_test(1, 1);

	quick_sort((void**)array, 1, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1,  *array[0]);

	free_array(array, 1);
}

static void sorting_array_quick_sort_ordered_array(){
	int** array = create_test(4, 1,2,3,4);

	quick_sort((void**)array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1,  *array[0]);
	TEST_ASSERT_EQUAL(2,  *array[1]);
	TEST_ASSERT_EQUAL(3,  *array[2]);
	TEST_ASSERT_EQUAL(4,  *array[3]);

	free_array(array, 4);
}

static void sorting_array_quick_sort_reversed_array(){
	int** array = create_test(4, 4,3,2,1);

	quick_sort((void**)array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1,  *array[0]);
	TEST_ASSERT_EQUAL(2,  *array[1]);
	TEST_ASSERT_EQUAL(3,  *array[2]);
	TEST_ASSERT_EQUAL(4,  *array[3]);

	free_array(array, 4);
}

static void sorting_array_quick_sort_random_array(){
	int** array = create_test(4, 3,6,1,7);

	quick_sort((void**)array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1,  *array[0]);
	TEST_ASSERT_EQUAL(3,  *array[1]);
	TEST_ASSERT_EQUAL(6,  *array[2]);
	TEST_ASSERT_EQUAL(7,  *array[3]);

	free_array(array, 4);

}


int main(int argc, char const *argv[]){
	UNITY_BEGIN();

	RUN_TEST(sorting_array_insertion_sort_null_array);
	RUN_TEST(sorting_array_insertion_sort_one_sized_array);
	RUN_TEST(sorting_array_insertion_sort_ordered_array);
	RUN_TEST(sorting_array_insertion_sort_reversed_array);
	RUN_TEST(sorting_array_insertion_sort_random_array);

	RUN_TEST(sorting_array_quick_sort_null_array);
	RUN_TEST(sorting_array_quick_sort_one_sized_array);
	RUN_TEST(sorting_array_quick_sort_ordered_array);
	RUN_TEST(sorting_array_quick_sort_reversed_array);
	RUN_TEST(sorting_array_quick_sort_random_array);

	UNITY_END();
}