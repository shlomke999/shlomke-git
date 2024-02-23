#include <stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<assert.h>
int Swap(int *x, int *y);
void Cp_Arr();
void Print_Values();
void SwapSizet(size_t *x, size_t *y);
void SwapSizetptr(size_t *c, size_t *d);

/* swap two int values */

int Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;


	return 0;
}

/* copy one arr to another */

void Cp_Arr(int org_arr[], int n, int new_arr[])
{
        int i;
        for (i = 0; i < n; i++)
        {
          new_arr[i] = org_arr[i];
        }

}

/* - Accept 2 sadresses of size_t swap their values */

void SwapSizet(size_t *a , size_t *b)
{

	size_t temp = *a;
	 *a = *b;
	 *b = temp;
}

int main()
{
	size_t a = 5, b = 10; 
	size_t *pa = &a, *pb = &b;
	size_t **ppa,  **ppb ; 
	ppa = &pa, ppb = &pb; 
	
	
	
	

	printf("%p \n %p \n", *pa, *pb);
	SwapSizet(&*pa, &*pb);
	printf("%p \n %p \n", *pa, *pb);


	return 0;
}

