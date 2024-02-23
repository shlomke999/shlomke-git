#include <stdio.h>
#include <stddef.h> /* Used for size_t type */



/*needs fixing*/
int FindInCircularArray(int *circ_arr, size_t size, int element)
{
	size_t i = 0, j = 0;
	for (i = 0; i < size; ++i)
	{
	    if (circ_arr[i] > circ_arr[i + 1])
	    {
	        break;
	    }
	    ++j;
	}
	for (i = 0; i < size; ++i)
	{
	    if (circ_arr[i] == element)
	    printf("element found at index:\n");
	    return i - j;
	}
	return - 1;
}








int main()
{
    int arr[6] = {7, 8, 11, 1, 4, 5};
    return FindInCircularArray(arr, 6, 11);
    return 0;
}
