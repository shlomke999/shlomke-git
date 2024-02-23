#include <stdio.h>

int Flip(int n);

int main()
{
	printf("%d\n", Flip(12345));
	return 0;
}



int Flip(int n)
{
	int revers;
	while(n > 0)
	{
	   revers += n % 10;
	revers = revers * 10;
           n = n / 10;
	}

	return revers/10;
}


