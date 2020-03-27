#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../Unity/unity.h"
#include "sorting.h"

#define INSERT_INT(array, elem, i) *(int*)array[i] = elem;

static int compare(int* obj1 , int* obj2){
	return *obj1 - *obj2;
}

static void print_int_array(void** array, int n_elem){
	for(int i = 0; i < n_elem; i++){
		printf("%d\t", *(int*)array[i]);
	}
	printf("\n");
}

static void** create_test(int n_elem, ...){

	va_list args;
	va_start(args, n_elem);

	void** result = (void**) malloc(sizeof(*result) * 4);

	for(int i = 0; i < n_elem; i++){
		result[i] = (int*) malloc(sizeof(int));
		INSERT_INT(result, va_arg(args, int), i)
	}

	return result;
}

static void free_array(void** array, int n_elem){
	for(int i = 0; i < n_elem; i++){
		free(array[i]);
	}

	free(array);
}

static void sorting_array_insertion_sort_null_array(){
	void ** array = NULL;

	insertion_sort(array, 0, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(NULL, array);

	free_array(array, 0);
}

static void sorting_array_insertion_sort_one_sized_array(){
	void** array = create_test(1, 1);

	insertion_sort(array, 1, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1, *(int*) array[0]);

	free_array(array, 1);
}

static void sorting_array_insertion_sort_ordered_array(){
	void** array = create_test(4, 1,2,3,4);

	insertion_sort(array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1, *(int*) array[0]);
	TEST_ASSERT_EQUAL(2, *(int*) array[1]);
	TEST_ASSERT_EQUAL(3, *(int*) array[2]);
	TEST_ASSERT_EQUAL(4, *(int*) array[3]);

	//print_int_array(array, 4);

	free_array(array, 4);
}

static void sorting_array_insertion_sort_reversed_array(){
	void** array = create_test(4, 4,3,2,1);

	insertion_sort(array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1, *(int*) array[0]);
	TEST_ASSERT_EQUAL(2, *(int*) array[1]);
	TEST_ASSERT_EQUAL(3, *(int*) array[2]);
	TEST_ASSERT_EQUAL(4, *(int*) array[3]);

	//print_int_array(array, 4);

	free_array(array, 4);
}

static void sorting_array_insertion_sort_random_array(){
	void ** array = create_test(4, 3,6,1,4);

	insertion_sort(array, 4, (SortingCmp) compare);

	TEST_ASSERT_EQUAL(1, *(int*) array[0]);
	TEST_ASSERT_EQUAL(3, *(int*) array[1]);
	TEST_ASSERT_EQUAL(4, *(int*) array[2]);
	TEST_ASSERT_EQUAL(6, *(int*) array[3]);

	//print_int_array(array, 4);

	free_array(array, 4);

}


int main(int argc, char const *argv[]){
	UNITY_BEGIN();

	RUN_TEST(sorting_array_insertion_sort_null_array);
	RUN_TEST(sorting_array_insertion_sort_one_sized_array);
	RUN_TEST(sorting_array_insertion_sort_ordered_array);
	RUN_TEST(sorting_array_insertion_sort_reversed_array);
	RUN_TEST(sorting_array_insertion_sort_random_array);

	UNITY_END();
}