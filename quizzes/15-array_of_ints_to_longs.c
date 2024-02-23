#include <stdio.h> /* printf */


/* 
status: approved.
by : elad shem tov.
*/ 
long *SumIntPairsToLongs(int ints[], size_t numOfElements)
{
	 size_t i = 0;
	 while (i < numOfElements)
	 {
	 	*((long *)(ints + i)) = (long)(*(ints + i)) + (long)(*(ints + i + 1));
	 	i += 2;
	 }
	 
	 return (long *)ints;
}



int main()
{
	int i = 0;
	int arr[] = { 3, 1, 4, 6, 4, 5, 6, 7, 8, 9 };
	long *longs_arr = NULL;
	
	longs_arr = SumIntPairsToLongs(arr, 10);	
	
	for (i = 0; i < (10 / 2); ++i)
	{
		printf("%ld\n", *longs_arr);
		++longs_arr;
	}
	
	
	return 0;
}

