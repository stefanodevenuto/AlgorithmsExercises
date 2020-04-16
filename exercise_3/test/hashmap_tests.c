#include <stdlib.h>
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

static HashMap* create_test_object(int** keys){

	HashMap* result = HashMap_new((HashFunction) hash_fun, (HashMapCmp) compare);
	
	HashMap_insert(result, keys[0], int_new(34));
	HashMap_insert(result, keys[1], int_new(78));
	HashMap_insert(result, keys[2], int_new(12));
	HashMap_insert(result, keys[3], int_new(90));

	return result;
}

static int** create_test_keys(){
	int** keys = (int**) malloc(sizeof(*keys) * 4);
	for(int i = 0; i < 4; i++){
		keys[i] = int_new(i);
	}

	return keys;
}

static void delete_test_objects(HashMap* hm, int** keys){
	for(int i = 0; i < 4; i++){
		int* value = HashMap_get(hm, keys[i]);
		free(value);
		free(keys[i]);
	}

	free(keys);
	HashMap_free(hm);
}

static void hash_map_get_key_not_present(){
	int** keys = create_test_keys();
	HashMap* hm = create_test_object(keys);

	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(5)));

	delete_test_objects(hm, keys);
}

static void hash_map_get_generic(){
	int** keys = create_test_keys();
	HashMap* hm = create_test_object(keys);

	TEST_ASSERT_EQUAL(12, *(int*) HashMap_get(hm, int_new(2)));
	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm, int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm, int_new(1)));
	TEST_ASSERT_EQUAL(90, *(int*) HashMap_get(hm, int_new(3)));

	delete_test_objects(hm, keys);
}

static void hash_map_remove_key_not_present(){
	int** keys = create_test_keys();
	HashMap* hm = create_test_object(keys);

	HashMap_remove(hm, int_new(10));

	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm, int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm, int_new(1)));
	TEST_ASSERT_EQUAL(12, *(int*) HashMap_get(hm, int_new(2)));
	TEST_ASSERT_EQUAL(90, *(int*) HashMap_get(hm, int_new(3)));

	delete_test_objects(hm, keys);
}

static void hash_map_remove_generic(){
	int** keys = create_test_keys();
	HashMap* hm = create_test_object(keys);

	HashMap_remove(hm, int_new(3));
	
	TEST_ASSERT_EQUAL(12, *(int*) HashMap_get(hm,int_new(2)));
	TEST_ASSERT_EQUAL(34, *(int*) HashMap_get(hm,int_new(0)));
	TEST_ASSERT_EQUAL(78, *(int*) HashMap_get(hm,int_new(1)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(3)));

	delete_test_objects(hm, keys);
}

static void hash_map_remove_all(){
	int** keys = create_test_keys();
	HashMap* hm = create_test_object(keys);

	HashMap_remove_all(hm);

	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(0)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(1)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(2)));
	TEST_ASSERT_EQUAL(0, HashMap_get(hm,int_new(3)));

	delete_test_objects(hm, keys);

}

static void print_keys(HashMap* hm, int** keys){
	for(int i = 0; i < HashMap_size(hm); i++){
		printf("%d\t", *keys[i]);
	}
	printf("\n");
}

static void hash_map_get_all_keys(){
	int** keys = create_test_keys();
	HashMap* hm = create_test_object(keys);

	int** hashmap_keys = (int**) HashMap_get_all_keys(hm);

	//print_keys(hm,keys);

	TEST_ASSERT_EQUAL(0, *hashmap_keys[0]);
	TEST_ASSERT_EQUAL(1, *hashmap_keys[1]);
	TEST_ASSERT_EQUAL(2, *hashmap_keys[2]);
	TEST_ASSERT_EQUAL(3, *hashmap_keys[3]);

	delete_test_objects(hm, keys);
}



int main(){
	UNITY_BEGIN();
		RUN_TEST(hash_map_get_key_not_present);
		RUN_TEST(hash_map_get_generic);
		RUN_TEST(hash_map_remove_key_not_present);
		RUN_TEST(hash_map_remove_generic);
		RUN_TEST(hash_map_remove_all);
		RUN_TEST(hash_map_get_all_keys);
    UNITY_END();
}