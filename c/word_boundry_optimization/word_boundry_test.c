#include <stdio.h> /*print*/
#include <string.h> /*strcmp*/
#include <assert.h> /*assert*/

#include "word_boundry.h"

#define WORD_SIZE (sizeof(size_t))



int main()
{
    
    
    
	int int_arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, i;
	int int_arr2[10] = { 0 };
	char char_arr[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
	char string[] = {"if it works then I can't explain why"};
	char char_arr2[10];
	float flt_arr[10] = {2.3, 4.5, 1.9, 0.1, 4, 5, 17};
	float flt_arr2[10] = { 0 };
	size_t n[3] = {16, 4, 8};
	int c[3] = {1, -1, 10};
	
	/*MemSet(int_arr, c[0], n[0]);*/
	MemSet(char_arr, c[1], n[1]);
	MemSet(flt_arr, c[2], n[2]);
	printf("\nBefore memset: ");
	for( i = 0; i < 10; i++)
	{
		printf(" %d", int_arr[i]);
	}
		
	MemSet(int_arr, '8', 3);
	printf("\nAfter  memset:  \n");
	for( i = 0; i < 10; i++)
	{
		
		printf("%d \n", int_arr[i]);
	}


	
	MemCpy(int_arr2, int_arr, n[0]);
	MemCpy(char_arr2, char_arr, n[1]);
	MemCpy(flt_arr2, flt_arr, n[2]);

	MemMove(string - 3, string, 16);
	
	printf("%s\n", string);


    
    
    
    
    
    /*    test ******************  MEMCPY
    char str[43] = {"bakabgan yin yang foo"};
	char tocopy[] = {"Yesh li yom yom hag yesh li hag yom yom"};
	size_t i;
	int arr[] = {1,2,3,4,5,6,7,8,9};
	float f[] = {34.67,2.4,3.23425,12314,23425.234234,4.3};
	printf("My Word Size: %ld \n", WORD_SIZE);

    
    printf("\n\n ******************  MEMCPY *********************\n\n");
	printf("Before memcpy: %s \n", tocopy);
	MemCpy(tocopy, str, 8);
	printf("\n\nAfter memncpy: %s \n\n", tocopy);
	*/
	
	/*
	MemSet(str , 98 , 16);
    printf("%s\n" , str);
    */
    	
	
    return 0;

}
