#include <stdio.h>
int *Swap(int *x, int *y);

int main()
{
	int a = 5, b = 10;
	 Swap(&a, &b);
}



int *Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;

	printf("%d\n%d\n", *x, *y);

	return 0;
}
