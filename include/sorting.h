#pragma once

typedef int (*SortingCmp)(void*, void*) ;

void insertion_sort(void** array, int n_elem, SortingCmp);

void quick_sort(void** array, int n_elem, SortingCmp);
