#include <stdio.h> /*for print*/
#include <assert.h> /*for assert*/
#include <stdlib.h>	

#include "atoiitoa.h"


/* Status : 
reviewer : 
description : Constructs a string representation of an integer, base 10.
return : Returns the value strisng
special notes : 
*/
char * Itoa(int n, char *buffer, int radix)
{
	int num = n, c = 0; /*digits counter*/
	
	if (n < 0)
	{
		n = n * -1;
		buffer[c] = '-';
		++buffer;	
	}
	
	while (0 != num)
	{
		num = num / radix;
		++c;
	}
		
	while (0 != c)
	{
		buffer[c - 1] = (char)(n % radix + 48);	
		n = n / radix;
		--c; 
	}
	return buffer;			
}


/* Status : 
reviewer : 
description : convert a string to its int representation. base 10.
return : Returns the value int, or 0 on error.
special notes : 
*/
int Atoi(const char *nptr)
{
	
	int result = 0, is_negative = 1;
	assert(NULL != str);
	
	if (*nptr == '-')
	{
		is_negative = -1;
		++nptr;
	}	
	
	while('\0' != *nptr)
	{
		if(*nptr < '0' || *nptr > '9')
		{
			break;
		}
		result = (result*10) + (*nptr - '0');
		++nptr;
	}

		
	return result * is_negative;
}


/* Status : 
reviewer : 
description : convert a string to int for any base till 36.
return : Returns the value int, or 0 on error.
special notes : 
*/


char *Itoa36(int value, char *string, int radix)
{
	int c = 0; /* digits counter */
	int is_neg = 0; /* negativ check */
	int tmp = value;

	if (value < 0)
	{
		is_neg = 1;
		value = value * -1;
		++c;
	}	
	/*counting digits*/
	while (tmp)
	{
		tmp = tmp / radix;
		++c;
	}
	
	*(string + (sizeof(char) * c)) = '\0';
	--c;
	
	for (; c >= 0; --c)
	{
		if (value % radix < 10)
		{ 
			*(string + sizeof(char) * c) = (char)(value % radix + 48);
			value /= radix;
		}
		else
		{
			*(string + sizeof(char) * c) = (char)(value % radix + 55);
			value /= radix;
		}
	}
	if (is_neg)
	{
		*string  = '-';
	}
	return string;
}


/* Status : 
reviewer : 
description : convert a string to its int representation. any base till 36.
return : Returns the value int, or 0 on error.
special notes : 
*/
int Atoi36(const char *nptr, int radix)
{
	
	int result = 0, is_negative = 1;
	char base_bank[] = {"2223456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	
	if (*nptr == '-')
	{
		is_negative = -1;
		++nptr;
	}	
	
	while ('\0' != *nptr && *nptr < base_bank[radix]) 
	{
		
			if (!(*nptr >= 'A' && *nptr <= 'Z') || (*nptr >= '0' && *nptr <= '9'))
			{
				return result;
			}	
			
			if (*nptr > '0' && *nptr <= '9')
			{
				result = (result * radix) + (*nptr - 48);

			}
			else if (*nptr >= 'A' && *nptr <= 'Z')
			{
				result = (result * radix) + (*nptr - 55);
			}
			++nptr;
	}			
	return result * is_negative;
}


int AtoiVsAtoi(char *str)
{
	return (atoi(str) == Atoi(str)) ? 1 : 0;
}


void TestAtoi(char *str)
{	
	int i = 0;
	char *tests[6] = { "o", "-3-3", "==", "+610", "235qvl", "0x567" };
	
	for(; i < 6; ++i)
	{
		assert(AtoiVsAtoi(tests[i]));
	}
}


/* Status : approved
reviewer : amir
description : recive 3 char arrays and print letters that are in the first two 
			  arrays but not the third.
return :void 
special notes : 
*/
void InTwoOutOfThree(char arr1[], char arr2[], char arr3[])
{
	int flag[128] = {0};
	int i = 0;
	
	while ('\0' != *arr1)
	{		
		flag[(int)*arr1] = 1;		
		++arr1;		
	}
	
	while ('\0' != *arr2)
	{
		if (flag[(int)*arr2] == 1)
		{
			flag[(int)*arr2] = 2;	
		}	
		++arr2;			
	}
	
	while ('\0' != *arr3 )
	{
		flag[(int)*arr3] = 0;		
		++arr3;			
	}
	
	for (i = 0; i < 128; ++i)
	{
		if (flag[i] == 2)
		{
			printf("%c ", (char)i);
		}
	}
}


/* Status : 
reviewer : 
description : check weather or not the system is little indian.
return : 1 for little indian, 0 for big.
special notes : 
*/
int IsLittleEndian()
{
	int x = 1;
	if (*(char *)&x == 1)
	{
		return 1;
	}
	return 0;
}





