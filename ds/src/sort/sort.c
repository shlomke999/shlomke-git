#include <time.h>/*show the time*/
#include <stdio.h> /*printf*/
#include <string.h>/*memcpy*/
#include <stddef.h>/*size_t*/
#include <stdlib.h> /*malloc*/


#include "../../include/sort.h"



/* Status : approved.
 * Reviewer : michael aponin.
 * Description : sort array by comparing 2 numbers at a time.	
 * Arguments : array, array size	
 * Return : sorted array.
 */
int *BubbleSort(int *arr, size_t size)
{
	size_t temp = 0, i = 0, j = 0;
	
	for (i = 0; i < size - 1; ++i)
	{
		for (j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j +1 ] = temp;
			}
		}
	}
	return arr;
}


/* Status : approved.
 * Reviewer : michael aponin.
 * Description : sort array by rpeatedlly looking for lowest number and swap it
 to the right place.	
 * Arguments : array, array size	
 * Return : sorted array.
 */
int *SelectionSort(int *arr, size_t size)
{
	size_t i = 0, j = 0, swap = 0, position = 0;
	
	for (i = 0; i < (size - 1); ++i)
	{
		position = i;
		for (j = i + 1; j < size; ++j)
		{
			if (arr[position] > arr[j])
			{
				position = j;
			}			
		}
		if (position != i)
		{
			swap = arr[i];
			arr[i] = arr[position];
			arr[position] = swap;
		}
	} 
	return arr;
}

/* Status : approved.
 * Reviewer : michael aponin.
 * Description : sort array by rpeatedlly taking the next number and swap it to
 the right place.	
 * Arguments : array, array size	
 * Return : sorted array.
 */
int *InsertionSort(int *array, size_t size) 
{ 
    size_t i = 0;
    int j = 0, element = 0;
    
    for (i = 1; i < size; i++) 
    {
    	 element = array[i]; 
    	 j = i - 1;
    	 /* Move elements of arr, that are greater than key by one position */
    	 while (j >= 0 && array[j] > element) 
    	 { 
             array[j + 1] = array[j]; 
             j = j - 1; 
         } 
         array[j + 1] = element; 
    } 
    return array;
}   


/* Status : approved.
 * Reviewer :  nimrod. 
 * Description : perform binary search in array.
 to the right place.	
 * Arguments : sorted array, array size	
 * Return : sorted array.
 */
int BinarySearch(int *arr, size_t size, int num_to_search)
{
	int start = 0, end = size - 1, middle = size / 2;
	while (start != end) 
	{
		if (arr[middle] == num_to_search)
		{
			return arr[middle];
		}
		else if (arr[middle] < num_to_search)
		{
			start = middle + 1;
			middle = (start + end) / 2;
		}
		else if((arr[middle]) > num_to_search)
		{
			end = middle - 1;
			middle = (start + end) / 2; 
		}
	}
	return -1;
}



/* Status : approved.
 * Reviewer :  nimrod.
 * Description : perform binary search in array.
 to the right place.	
 * Arguments : sorted array, array size	
 * Return : sorted array.
 */
int BinarySearchRecursive(int *array, int start_index, int end_index, int element)
{
   if (end_index >= start_index)
   {
      int middle = start_index + (end_index - start_index ) / 2;
      
      if (array[middle] == element)
      {
         return array[middle];
      }
      if (array[middle] > element)
      {
         return BinarySearchRecursive(array, start_index, middle - 1, element);
      }
      return BinarySearchRecursive(array, middle + 1, end_index, element);
   }
   return -1;
}




/* MergeSort
description:  recieves pointer to start of array of integers and sorts the array .  
status: approved.   
reviewer:   elad.
args: pointer to start of array of integers + num of elements
return: 0 at finish 
*/
void MergerTwo(int *array , int left , int right, int middle )
{
	int i = 0;
	int j = 0;
	
	int k = left;
	int num_elements_left_arr = middle - left + 1;   /*num elements = index + 1*/ 
	int num_elements_right_arr = right - middle; 
	
	int *left_arr_mem = NULL;
	int *right_arr_mem = NULL; 
	
	/* memory for both arrays */
	
	left_arr_mem = (int *)malloc(num_elements_left_arr*sizeof(int));
	if (left_arr_mem == NULL)
	{
		printf("memory allocation failed, exiting \n");
		exit(0);
	}
	
	right_arr_mem = (int *)malloc(num_elements_right_arr*sizeof(int));
	if (right_arr_mem == NULL)
	{
		printf("memory allocation failed, exiting \n");
		exit(0);
	}

	/*copy left of array to left memory , right of array to right memory */
	
	for ( i = 0; i < num_elements_left_arr ; ++i )
	{
		left_arr_mem[i] = array[left+i];
	}
	
	for ( i = 0 ; i < num_elements_right_arr ; ++i )
	{
		right_arr_mem[i] = array[middle+1+i];
	}
	
	/*merge left and right memory into original array */
	
	i = 0;
	
	while ( i < num_elements_left_arr && j < num_elements_right_arr )
	{
		if (left_arr_mem[i] <= right_arr_mem[j])
		{
			array[k] = left_arr_mem[i];
			++i;
		}
		
		else
		{
			array[k] = right_arr_mem[j];
			++j;
		}
		
		++k;
	}
	

	
	/*insert remaining elements from right memory and left memory into array */
	
	while (i < num_elements_left_arr)
	{
		array[k] = left_arr_mem[i];
		++i;
		++k;
	}

	while (j < num_elements_right_arr)
	{
		array[k] = right_arr_mem[j];
		++j;
		++k;
	}
	
	/*free temp memory*/

	free(left_arr_mem);
	free(right_arr_mem);
	
}


void MergerOne( int *array , int left, int right )
{
	int middle;
	
	if (left < right)
	{
		middle = left + (right-left)/2;
		
		MergerOne(array,left,middle);

		MergerOne(array,middle+1,right);

		MergerTwo(array , left , right , middle);
	
	}
}


int MergeSort(int *arr_to_sort, size_t num_elements)
{
	int left = 0;
	int right = num_elements-1;
	

	MergerOne(arr_to_sort, left, right);
	
	return 0;
}



/*approved by ran*/
								/*quick sort*/
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
    int j;
	for (j = low; j <= high - 1; j++) 
	{
		if (arr[j] <= pivot) 
		{
			++i;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);  
	return (i + 1);
}


void quicksort(int Arr[], int low, int high)
{
	if (low < high)
	 {
		int pi = partition(Arr, low, high);
		quicksort(Arr, low, pi - 1);
		quicksort(Arr, pi + 1, high);           
	 }
}











