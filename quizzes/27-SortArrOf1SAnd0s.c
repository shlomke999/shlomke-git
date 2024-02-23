#include <stdio.h>

void Swap(int *x,int *y)
{
    int t;
     t   = *x;
    *x   = *y;
    *y   =  t;
}

/*approved by nimrod*/
void SortArr(int arr[], int l_index, int r_index)
{
    size_t i = 0;
    
    for (i = 0; i < r_index - 1; ++i)
    {
        if (arr[i] == 0)
        {
           Swap(&arr[i], &arr[l_index]);
           ++l_index;
        }
        else
        {
            Swap(&arr[i], &arr[r_index]);
            if(arr[i] == 1)
            {
                Swap(&arr[i], &arr[i + 1]);
            }
            --r_index;
        }
    }
    
}


int main()
{
    size_t i = 0;
    int arr[7] = {0, 1, 1, 0, 0, 1, 0};
    SortArr(arr, 0, 7);
    for(i = 0; i < 7; ++i)
    {
         printf("%d\n", arr[i]);
    }

    return 0;
}







