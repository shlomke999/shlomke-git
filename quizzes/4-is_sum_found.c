#include <stdio.h>
#include <stddef.h>


/* STATUS: APPROVED.
/* by: michael aponin. 
*/
int *Is_Sum_Found(int a[], size_t size, int sum, int ret[])
{
	size_t i = 0;
	size_t j = (size - 1);
	
	while (i != j)
	{
		if ((a[i] + a[j]) == sum)
		{		
			ret[0] = 1;
			ret[1] = i;
			ret[2] = j;
			return ret;
		}
		if (a[i] + a[j] > sum)
		{
			--j;
		}				
		if (a[i] + a[j] < sum)
		{
			++i;
		}				
	}
	ret[0] = 0;
	return ret;
}



int main()
{
	int arr[] = {2,6,7,12,14};
	int ret[3];
	size_t i;
	
	Is_Sum_Found(arr, 5, 8, ret);
	
	for(i = 0 ; i < 3; ++i)
	{
		printf("%d\n", *(ret + i));
	}
	
	return 0;
	
}


