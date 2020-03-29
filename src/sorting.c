#include <stdio.h>
#include "sorting.h"

#define SWAP(array, i, j) void* tmp = array[i]; \
						  array[i] = array[j]; \
						  array[j] = tmp;

static int partition(void** array, int start, int end, SortingCmp compare){
	int i = start + 1;
	int j = end;

	while(i <= j){
		if(compare(array[i], array[start]) <= 0) i++;
		else if(compare(array[j], array[start]) > 0) j--;
		else{
			SWAP(array, i, j)
			i++;
			j--;
		}
	}

	SWAP(array, start, j)

	return j;
}

void insertion_sort(void** array, int n_elem, SortingCmp compare){	
	
	if(array == NULL) return;

	for(int i = 1; i < n_elem; i++){
		for(int j = i; j > 0 && compare(array[j - 1],array[j]) > 0; j--){
			SWAP(array, j, j - 1)
		}
	}
}

static void quick_sort_implementation(void** array, int start, int end, SortingCmp compare){
	if(end > start){
		int p = partition(array, start, end, compare);
		if(p > start)
			quick_sort_implementation(array, start, p-1, compare);
		if(p < end - 1)
			quick_sort_implementation(array, p+1, end, compare);
	}
}

void quick_sort(void** array, int n_elem, SortingCmp compare){

	if(array == NULL) return;

	quick_sort_implementation(array, 0, n_elem - 1, compare);
}
