#include <assert.h>  /*pointers used*/
#include <stddef.h>   /*NULL */
#include <string.h>  /*string*/ 
#include <stdio.h>  /*print */ 

/*approved by ran*/
int CircArraySearch(int array[], int low, int high , int num)
{
	int middle = 0; 
	
	if (low > high)
	{
		return -1;
	}	
	middle = (low + high) / 2;	
	if (array[middle] == num)
	{
		return middle;
	}	
	if (array[low] <= array[middle])  
	{
		if (num >= array[low] && num <= array[middle])
		{
			return CircArraySearch(array, low , middle -1, num);  
		}
		
		else 
		{
			return CircArraySearch(array, middle + 1 , high , num);  
		}
	}
	if (num >= array[middle] && num <= array[high]) 
	{
		return CircArraySearch(array, middle + 1, high, num);
	}
	
	return CircArraySearch(array, low, middle - 1, num);	
}



int main()
{
	int array[] = {1,5,6,7,12,22,27,29,39};
	
	printf("%d \n", CircArraySearch(array,0,8,  39 ));
						
	printf("%d \n", CircArraySearch(array,0,8,  15 ));
	
	return 0; 	
}

