#include <stdio.h>/*printf*/
#include <stddef.h> /*size_t*/
 
 
 /* status: approved.
 by: elad shem tov.
 */
 
int FindNum(int *arr, int num, size_t arr_size)
{
	while(num != *arr && arr_size > 0)
	{
		++arr;
		--arr_size;
	}
	if(*arr == num)
	{
		return 1;
	}
	return 0;
}



int main()
{
 	int i = 0;
	int arr[10] = {8,4,-3,2,6,77,-21,111,75,0};
	int arr_test[10] = {111,-21,0,1211,20,23};
	for(i=0;i<3;++i)
	{
		printf("should be 1: %d\n",FindNum(arr,arr_test[i],10));
	}
	for(;i<6;++i)
	{
		printf("should be 0: %d\n",FindNum(arr,arr_test[i], 10));
	}
   
	return 0;
}

