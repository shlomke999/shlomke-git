#include <limits.h>
#include <stdio.h>


int CountCouplesSetBits(char a)
{
	int i = 0, c = 0;
	for (; i < 7; ++i)
	{
		if (((a >> i) & 1) && (( a >> (i + 1)) & 1))
		{
			++c;
		}
	}
	return c;
}

void SwapXOR(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void SwapTmp(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void SwapArithmic(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int CountSetBitsInLong(long n)
{
	int c = 0;
	while (n)
	{
		n = n & (n - 1);
		++c;
	}
	return c;
}

int main()
{
	int i = 0;
	int j = 0;
	int x = 6;
	int w = 8;
	char z = 78;
	long arr[10] = { 1, 3, 7, 4194696, 742391840, 742391841, 
				742400033, 742924321, 742924329, 742924841} ;
	int y[10];
	
	j = CountCouplesSetBits(z);
	printf ("number of  couples of set bits in 78 is %d\n", j);
	SwapXOR(&x, &w);
	SwapTmp(&x, &w);
	SwapArithmic(&x, &w);
	for (; i < 10; ++i)
	{
		y[i] = CountSetBitsInLong(arr[i]);
		printf("number of set bits in %d\n is: %d\n", y[i], CountSetBitsInLong(y[i]));
	}
	return 0;
}

