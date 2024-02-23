#include <stdlib.h>	/* Mallod , Free */
#include <stddef.h>	/* size_t */
#include <stdio.h>	/*print*/
#include <string.h> /* memcpy */

#include "../include/vector.h"

int main()
{
/*
		int i = 0;
	int arr[] = {4, 3, 4, 5, 5, 45, 33};
	
	vector_t *vec = VectorCreate(7, 4);
	for (i = 0; i < 7; ++i)
	{
		VectorPushBack(vec, &arr[i]);
		printf ("%d\n", *(int *)VectorAccessIndex(vec, i + 7));
	}
	VectorDestroy(vec);
	return 0;
	*/
	
				int arr[] = {5,33,61,833,1512,12,99,3};
	double double_arr[] = {1.15 ,33.8 ,61.76 ,833 ,1512.87 ,12.2 ,99.77, 3.552};
	int i = 0;
	vector_t *int_vector = VectorCreate(8,4);
	vector_t *double_vector = VectorCreate(8,8);
	for(i = 0; i<8; ++i)
	{
	VectorPushBack(int_vector ,&arr[i]);
 	printf("int element at index %d is: %d\n",i ,*((int *)VectorAccessIndex(int_vector,i)));
 	
 	VectorPushBack(double_vector ,&double_arr[i]);
 	printf("double element at index %d is: %f\n\n",i ,*((double *)VectorAccessIndex(double_vector, i)));
 	
 	printf("number of elements: %ld\n", VectorSize(int_vector));
 	printf("number of elements: %ld\n", VectorSize(double_vector));
	}
	
	for(i=0; i<5; i++)
	{
		printf("int_vector size before pop is: %ld\n", VectorSize(int_vector));
		VectorPopBack(int_vector);

		printf("double_vector size before pop is: %ld\n", VectorSize(double_vector));
		VectorPopBack(double_vector);
	}
	  
	printf("VectorAccess (int) at index 1 should be 33: %d\n", *((int *)VectorAccessIndex(int_vector,1)));
	printf("VectorAccess (double) index 1 should be 33.8 : %f\n", *((double *)VectorAccessIndex(double_vector,1)));
	
	
	VectorDestroy(int_vector);
	VectorDestroy(double_vector);
	return 0;
}






/*
	

	
	

	*/
