#ifndef __COMPARISON_H_CR4__ 
#define __COMPARISON_H_CR4__ 

int *BubbleSort(int *arr, size_t size);
int *SelectionSort(int *arr, size_t size);
int *InsertionSort(int *array, size_t size);

int BinarySearch(int *arr, size_t size, int n);
int BinarySearchRecursive(int *array, int start_index, int end_index, int element);
int MergeSort(int *arr_to_sort, size_t num_elements);



int CompareInts(const void *n1, const void *n2);
void MakeRandomArr_5K(int *arr);
void PrintArr_5k(int *arr);

int partition(int arr[], int low, int high);
void quicksort(int Arr[], int low, int high);


#endif /* __COMPARISON_H_CR4__ */
