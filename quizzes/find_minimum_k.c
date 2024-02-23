#include <stdio.h>
#include <limits.h>
#define MIN2(a, b) ((a) < (b) ? (a) : (b))
#define MAX2(a, b) ((a) > (b) ? (a) : (b))

int FindKthSmallest(int *arr, int size, int k)
{
	int kth_i = 0, min = arr[0], max = arr[0], curr_smallest_diff = 0, i = 0, j = 0;
	for ( j = 0; j < size; ++j)
	{
		min = MIN2(arr[j], min);
		max = MAX2(arr[j], max);
	}
	
	for (i = 0; i < (k - 1); ++i)
	{
		curr_smallest_diff = max;
		for ( j = 0; j < size; ++j)
		{
			if (min < arr[j] && arr[j] - min < curr_smallest_diff)
			{
				curr_smallest_diff = arr[j] - min;
				kth_i = arr[j];
			}
		}
		min = kth_i;
	}
	return kth_i;
}

int main()
{
	int arr[] = {1, 9, 13, 2, 4, 7, 18, 21, 0};
	int k = FindKthSmallest(arr, 9, 5);
	printf("%d\n", k);
	return 0;
}

