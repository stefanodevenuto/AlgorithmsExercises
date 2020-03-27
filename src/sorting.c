#include <stdio.h>
#include "sorting.h"

static void swap(void** array, int i, int j){
	void* tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void insertion_sort(void** array, int n_elem, SortingCmp compare){	
	
	if(array == NULL) return;

	for(int i = 1; i < n_elem; i++){
		for(int j = i; j > 0 && compare(array[j - 1],array[j]) > 0; j--){
			swap(array, j, j - 1);
		}
	}
}

void quick_sort(void** array, SortingCmp compare){
	printf("quick_sort\n");
}