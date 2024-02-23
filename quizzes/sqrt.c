#include <stdio.h>


/*approved by elad.*/

double Sqrt(double num)
{
	double sqrt = (num / 2), mid = 0;
	while (mid != sqrt)
	{
		mid = sqrt;
		sqrt = ((num / mid) + mid) / 2;
	}
	return sqrt;
}



int main(void)
{
	double i = 0;
	for (i = 9; i < 15; ++i)
	{
		printf("%f is the sqrt of %f.\n", Sqrt(i), i);
	}
	return 0;
}

