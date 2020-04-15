#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "../Unity/unity.h"
#include "hashmap.h"

static int* int_new(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;

    return result;
}

static int compare(int* obj1 , int* obj2){
    return *obj1 - *obj2;
}

static int hash_fun(int* key){
	return *key;
}

static HashMap* create_test_object(int n_elem, ...){

	va_list args;
	va_start(args, n_elem);

	HashMap* result = HashMap_new((HashFunction) hash_fun, (HashMapCmp) compare);
	
	for(int i = 0; i < n_elem; i++){
		int a = va_arg(args, int);
		HashMap_insert(result, int_new(i), int_new(a));
	}

	return result;
}

static void hash_map_get(){
	HashMap* hm = create_test_object(4, 34,78,12,90);
	
	TEST_ASSERT_EQUAL(12, *(int*) HashMap_get(hm, int_new(2)));
	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm, int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm, int_new(1)));
	TEST_ASSERT_EQUAL(90, *(int*) HashMap_get(hm, int_new(3)));

	HashMap_free(hm);
}

static void hash_map_remove(){
	HashMap* hm = create_test_object(4, 10,20,30,40);

	HashMap_remove(hm, int_new(3));
	
	TEST_ASSERT_EQUAL(30, *(int*) HashMap_get(hm,int_new(2)));
	TEST_ASSERT_EQUAL(10, *(int*) HashMap_get(hm,int_new(0)));
	TEST_ASSERT_EQUAL(20, *(int*) HashMap_get(hm,int_new(1)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(3)));

	HashMap_free(hm);
}

static void hash_map_remove_all(){
	HashMap* hm = create_test_object(5, 10,20,30,40,50);

	HashMap_remove_all(hm);

	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(0)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(1)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(2)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(3)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(4)));

	HashMap_free(hm);

}

//static void print_values()

int main(){
	UNITY_BEGIN();
		RUN_TEST(hash_map_get);
		RUN_TEST(hash_map_remove);
		RUN_TEST(hash_map_remove_all);
    UNITY_END();
}