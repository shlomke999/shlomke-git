#include <stdio.h>


static int MaxSubArray(int Array[], size_t size) 
{
   int max_sum = 0, current_sum = 0;
   size_t i = 0;

   for(i = 0; i < size; i++) 
   {
		current_sum += Array[i];
		if (current_sum < 0)
		{
		  current_sum = 0; 
		}
		if(max_sum < current_sum)
		{
		  max_sum = current_sum; 
		}
   }
  return max_sum;
}



int main(void) 
{
  int MyArray[] = {-3, 1, -8, 12, 0, -3, 5, -9, 4};
  int size = sizeof(MyArray) / sizeof(MyArray[0]);
  
  printf("Maximum SubArray is: %d\n", MaxSubArray(MyArray, size));
  return 0;
}


