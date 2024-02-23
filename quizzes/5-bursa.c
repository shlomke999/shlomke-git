#include <stdio.h>

void Bursa(int *prices, size_t size, int result[3])
{
    int max = prices[size-1];
    int min = prices[size-1];
	int i = 0;

	for (i = size - 2; i >= 0; --i)
	{
		if (prices[i] > max)
		{
			max = prices[i];
			min = prices[i];
			continue;
		}
		if (prices[i] < min)
		{
			min = prices[i];
			if(max - min > result[2])
			{
				result[0] = min;
				result[1] = max;
				result[2] = max - min;
			}
		}
		
	}
}

int main(void)
{
	int prices[] = { 9 ,3 ,12, 3, 15, 7, 4, 9, 10, 21, 6, 8, 14, 2, 9 };
	int res[3] = { 0, 0, 0 };
	
	Bursa(prices, sizeof(prices)/sizeof(prices[0]), res);
	printf("if you Buy at : %d  and sell at : %d  you will earn: %d\n", res[0], res[1], res[2]);
	
	return 0;
}

