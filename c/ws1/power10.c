#include <stdio.h>

int main()

{
return 0;
}



double power(int n)

{
	 int  i;
	double result = 1;
	double  base = 10;
	if (n == 0)
	return 1;

	if (n < result)
	{
		n = n * -1;
		base = 1/base;

	}



        for(i = 0; i < n; i++)

	{
		result = result * base;
	}


	return result;

}


