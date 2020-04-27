#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "unity.h"
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

	HashMap* result = HashMap_new((HashFunction) hash_fun, (HashMapCmp) compare, 3);
	for(int i = 0; i < n_elem; i++){
		HashMap_insert(result, int_new(i), int_new(va_arg(args, int)));
	}

	return result;
}

static void delete_test_objects(HashMap* hm){
	int** keys = (int**) HashMap_get_all_keys(hm);
	for(int i = 0; i < HashMap_size(hm); i++){
		int* value = HashMap_get(hm, keys[i]);
		free(value);
		free(keys[i]);
	}
	free(keys);
	HashMap_free(hm);
}

static void hash_map_get_key_not_present(){
	HashMap* hm = create_test_object(4, 34,78,12,90);

	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(5)));

	delete_test_objects(hm);
}

static void hash_map_get_generic(){
	HashMap* hm = create_test_object(11, 34,78,12,90,45,65,876,23,565,87,89);

	TEST_ASSERT_EQUAL(12, *(int*) HashMap_get(hm, int_new(2)));
	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm, int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm, int_new(1)));
	TEST_ASSERT_EQUAL(90, *(int*) HashMap_get(hm, int_new(3)));

	delete_test_objects(hm);
}

static void hash_map_remove_key_not_present(){
	HashMap* hm = create_test_object(4, 34,78,12,90);

	HashMap_remove(hm, int_new(10));

	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm, int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm, int_new(1)));
	TEST_ASSERT_EQUAL(12, *(int*) HashMap_get(hm, int_new(2)));
	TEST_ASSERT_EQUAL(90, *(int*) HashMap_get(hm, int_new(3)));

	delete_test_objects(hm);
}

static void hash_map_remove_generic(){
	HashMap* hm = create_test_object(4, 34,78,12,90);

	HashMap_remove(hm, int_new(3));
	
	TEST_ASSERT_EQUAL(12, *(int*) HashMap_get(hm,int_new(2)));
	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm,int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm,int_new(1)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(3)));

	delete_test_objects(hm);
}

static void hash_map_remove_all(){
	HashMap* hm = create_test_object(4, 34,78,12,90);

	HashMap_remove_all(hm);

	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(0)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(1)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(2)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(3)));

	TEST_ASSERT_EQUAL(0, HashMap_size(hm));

	delete_test_objects(hm);

}

static void hash_map_insert_already_present(){
	HashMap* hm = create_test_object(4, 34,78,12,90);

	int* new_key = int_new(2);
	int* new_value = int_new(45);
	
	HashMap_insert(hm, new_key, new_value);

	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm,int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm,int_new(1)));
	TEST_ASSERT_EQUAL(45, *(int*) HashMap_get(hm,int_new(2)));
	TEST_ASSERT_EQUAL(90, *(int*) HashMap_get(hm,int_new(3)));
	TEST_ASSERT_EQUAL(4, HashMap_size(hm));
	
	free(new_key);
	//free(new_value);
	delete_test_objects(hm);

}

static void print_keys(HashMap* hm, int** keys){
	for(int i = 0; i < HashMap_size(hm); i++){
		printf("%d\t", *keys[i]);
	}
	printf("\n");
}

static void hash_map_get_all_keys(){
	HashMap* hm = create_test_object(4, 34,78,12,90);

	int** hashmap_keys = (int**) HashMap_get_all_keys(hm);

	//print_keys(hm, hashmap_keys);

	TEST_ASSERT_EQUAL(0, *hashmap_keys[0]);
	TEST_ASSERT_EQUAL(1, *hashmap_keys[1]);
	TEST_ASSERT_EQUAL(2, *hashmap_keys[2]);
	TEST_ASSERT_EQUAL(3, *hashmap_keys[3]);

	delete_test_objects(hm);
}




int main(){
	UNITY_BEGIN();
		RUN_TEST(hash_map_get_key_not_present);
		RUN_TEST(hash_map_get_generic);
		RUN_TEST(hash_map_remove_key_not_present);
		RUN_TEST(hash_map_remove_generic);
		RUN_TEST(hash_map_remove_all);
		RUN_TEST(hash_map_insert_already_present);
		RUN_TEST(hash_map_get_all_keys);
    UNITY_END();
}