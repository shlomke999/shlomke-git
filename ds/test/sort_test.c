#include <stdio.h> /*for printing*/
#include <string.h>/*for memcpy*/
#include <time.h>/*for time*/
#include <stdlib.h>/*rand*/


#include "../include/sort.h"


int CompareInts(const void *n1, const void *n2)
{
	return (*(int *)n1 - *(int *)n2);
}
 



int int_arr[5000] = {0};

void MakeRandomArr_5K(int *arr)
{	
	int random_n = 0;
	size_t i = 0;
	for(i=0; i<5000; ++i)
	{
		random_n = rand();
		if(0 == random_n%100)
		{
			random_n*= -1;
		}
		arr[i] = (random_n % 5000);
	}
}

void PrintArr_5k(int *arr)
{
	size_t i = 0;
	for(i=0; i<5000; ++i)
	{
		printf("%d, ",arr[i]);
	}
	printf(" \n\n\n\n");
}


void PrintArr_10(int *arr)
{
	size_t i = 0;
	for(i=0; i<10; ++i)
	{
		printf("%d, ",arr[i]);
	}
	printf(" \n\n\n\n");
}


int main()
{
	int size = 5, i = 0;
	int array[5] = { 11,9,6,16,7 };
	int binary_arr[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	int merge_sort_arr[10] = {20, 16, 14, 12, 10, 11, 10, 9, 8, 6};

  	clock_t tic_bub = 0;
  	clock_t toc_bub = 0;
	clock_t tic_sel = 0;
  	clock_t toc_sel = 0;	 
  	clock_t tic_ins = 0;
  	clock_t toc_ins = 0;
  	clock_t tic_qs = 0;
  	clock_t toc_qs = 0; 
  	
  	int int_arr_copy1[5000] = {0};
  	int int_arr_copy2[5000] = {0};
  	int int_arr_copy3[5000] = {0};
  	int int_arr_copy4[5000] = {0};
  	
 	MakeRandomArr_5K(int_arr);
 	
 	memcpy(int_arr_copy1, int_arr, 5000*sizeof(int));

 	memcpy(int_arr_copy2, int_arr, 5000*sizeof(int));
 	memcpy(int_arr_copy3, int_arr, 5000*sizeof(int));
 	memcpy(int_arr_copy4, int_arr, 5000*sizeof(int));
 	
 
	printf("***Bubble sorted array below***\n\n\n\n");
	tic_bub = clock();
	BubbleSort(int_arr_copy1, 5000);
	toc_bub = clock();
 
	printf("***Selection sorted array below***\n\n\n\n");
	tic_sel = clock();
	SelectionSort(int_arr_copy2, 5000);
	toc_sel = clock();
	
 
	printf("***Insertion sorted array below***\n\n\n\n");
	tic_ins = clock();
	InsertionSort(int_arr_copy3, 5000);
	toc_ins = clock();
	
 
	printf("***quick sort***\n\n\n\n");
	tic_qs = clock();
	qsort(int_arr_copy4 ,5000, 4, CompareInts);
	toc_qs = clock();
	
	

printf("****************************buble*****************************\n\n\n");
PrintArr_5k(int_arr_copy1);
printf("****************************select*****************************\n\n\n");
PrintArr_5k(int_arr_copy2);
printf("****************************insert*****************************\n\n\n");
PrintArr_5k(int_arr_copy3);
printf("****************************quick*****************************\n\n\n");
PrintArr_5k(int_arr_copy4);
printf("------------------------------------------------------------------------\n");

 
printf("Time elapsed for BubbleSort: %f seconds\n",(double)(toc_bub - tic_bub) / CLOCKS_PER_SEC);
printf("Time elapsed for SelectionSort: %f seconds\n", (double)(toc_sel - tic_sel) / CLOCKS_PER_SEC);
printf("Time elapsed for InsertionSort: %f seconds\n", (double)(toc_ins - tic_ins) / CLOCKS_PER_SEC);
printf("Time elapsed for qsort: %f seconds\n", (double)(toc_qs - tic_qs) / CLOCKS_PER_SEC);


printf("**************************** binary search *****************************\n\n\n");

printf ("result for binary search with number 11 should be -1 ->: %d\n", BinarySearch(binary_arr, 10, 11));
printf ("result for binary search with number 12 should be 12 ->: %d\n", BinarySearch(binary_arr, 10, 12));
printf ("result for binary search with number 18 should be 18 ->: %d\n", BinarySearch(binary_arr, 10, 18));
printf ("result for binary search with number 6 should be 6 ->: %d\n", BinarySearch(binary_arr, 10, 6));


printf("**************************** binary search recursive *****************************\n\n\n");

printf ("result for binary search with number 11 should be -1 ->: %d\n", BinarySearchRecursive(binary_arr, 0, 10, 11));
printf ("result for binary search with number 18 should be 12 ->: %d\n", BinarySearchRecursive(binary_arr, 0, 10, 12));
printf ("result for binary search with number 18 should be 18 ->: %d\n", BinarySearchRecursive(binary_arr, 0, 10, 18));
printf ("result for binary search with number 6 should be 6 ->: %d\n", BinarySearchRecursive(binary_arr, 0, 10, 6));
printf ("result for binary search with number 20 should be 20 ->: %d\n", BinarySearchRecursive(binary_arr, 0, 10, 20));


printf("**************************** merge sort *********************\n\n\n");
printf ("before sort:\n");
PrintArr_10(merge_sort_arr);
MergeSort(merge_sort_arr, 10);
printf ("after sort:\n");
PrintArr_10(merge_sort_arr);



printf("**************************** quick sort *******************\n\n\n");
printf("before sort:\n");
for(i = 0; i < size; i++) 
	{
		printf("%d ",array[i]);
	}
	printf("\n");

	quicksort(array, 0, size - 1);  

printf("after sort:\n");	  
	for(i = 0; i < size; i++) 
	{
		printf("%d ",array[i]);
	}
printf("\n");

	return 0;
}










