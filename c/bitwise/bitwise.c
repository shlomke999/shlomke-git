#include <stdio.h> /*for print*/


/*#############################             
status: approved
reviewer:shany             
description: calculate sum of x * (2^y)                
return value: long       
special notes:            
#############################*/
long Pow2(unsigned int x, unsigned int y)
{
	long two_pow_y = x << y;
	return two_pow_y;
}


/* #############################                
# status: approved
# reviewer:shany             
# description:check if n is power of 2                
# return value: int       
# special notes:            
#############################*/
int IsSquaredNoLoop(unsigned int n)
{
	int x = (n - 1);
	
	if(0 == (x & n))
	{
		return 1;
	}
	return 0;
}


/* #############################             
# status: approved
# reviewer:shany             
# description: check if n is power of 2 using a     loop                
# return value: int       
# special notes:            
#############################*/
int IsSquared(unsigned int n)
{
	unsigned int sum = 1;
	
	while(1)
	{
		sum = (sum << 1);
		if(sum == n)
		{
		return 1;
		}
		if(sum > n)
		{
		return 0;
		}
	}
}


/* #############################             
# status: approved
# reviewer:shany             
# description: add 1 to a given number                
# return value: int       
# special notes:            
#############################*/
int AddOne(int x)
{
	int mask = 1;
	
	while(1 == (x & mask))
	{
		x    = mask ^ x;
		mask = mask << 1;
	}
	x = mask ^ x;
	return x;		
}


/* #############################             
# status: approved
# reviewer:shany             
# description:get array of ints and print the numbers that have exactlly 3 bits on.           
# return value: void       
# special notes:            
#############################*/
void ThreeBitsOn(int arr[], int n)
{
	int mask = 1, counter = 1, i = 0;
	int number;
	
	for(; i < n; i++)
	{
		counter = 1;
		number = arr[i];
		while(number > 0)
		{
			if(number & mask)
			{
				number = number >> 1;
			    counter = counter << 1;
			}
			else
			{
				number = number >> 1;
			}
		}
		if(counter == 8)
		{
			printf("%d\n", arr[i]);
		}			
	}		
}


/* #############################             
# status: approved
# reviewer:shany             
# description: reveres bits in a number using a loop           
# return value: unsigned int       
# special notes:            
#############################*/
unsigned int ByteMirror(unsigned int a)
{
	unsigned int rev = 0;
	unsigned int no_of_bits = (sizeof(a) * 8);
	unsigned int i;
	
	for(i = 0; i < no_of_bits; i++)
	{	
		if ((a & (1 << i)))
 		{
       		 rev |= 1 << ((no_of_bits - 1) - i);
       	}      	
	}	
	return rev;	
}


/* #############################             
# status: approved
# reviewer:shany             
# description:reveres bits in a given 1 byte number without a loop          
# return value: unsigned char       
# special notes:            
#############################*/
unsigned char ByteMirrorNoLoop(unsigned char x)
{
	x = ((x & 170) >> 1) | ((x & 85) << 1);
	x = ((x & 204) >> 2) | ((x & 51) << 2);  
	x= ((x & 240) >> 4)  | ((x & 15) << 4);
	return x;
}


/* #############################             
# status: approved
# reviewer:shany             
# description: get a char, return 1 if bits 2 and 6 are on           
# return value: int       
# special notes:            
#############################*/
int IsBothOn(unsigned char x)
{
	return ((34 & x) == 34);
}


/* #############################             
# status: approved
# reviewer:shany             
# description: get a char, return 1 if at least one of bits 2 and 6 are on          
# return value: int       
# special notes:            
#############################*/
int IsOneOn(unsigned char x)
{
		return ((2 & x) == 2 || (32 & x) == 32);
}


/* #############################             
# status: approved
# reviewer:shany             
# description: get a char, swap its 3rd and 5th bits.      
# return value: int       
# special notes:            
#############################*/
int SwapBits(unsigned char x)
{
	unsigned char third = (x >> 2) & 1;
	unsigned char fifth = (x >> 4) & 1;
	unsigned char similarity = third ^ fifth;
	
	similarity = (similarity << 2) | (similarity << 4);
	
	return (x ^ similarity);
}


/* #############################             
# status: approved
# reviewer:shany             
# description: get a number, find nearest lower number that devieded by 16.    
# return value: unsigned int       
# special notes:            
#############################*/
unsigned int Divisible16(unsigned int n)
{
	return ((n >> 4) << 4); 
}


/* #############################             
# status: approved
# reviewer:shany             
# description: swap two variables without using a third one.
# return value: void.       
# special notes:            
#############################*/
void Swap(int *x, int *y)
{
	if(x != y)
	{
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}


/* #############################             
# status: approved
# reviewer:shany             
# description: count set bits of a number.
# return value: int.       
# special notes:            
#############################*/
int CountSetBits(unsigned int x)
{
	int count = 0;
	while(x > 0)
	{
		if(1 == (x&1))
		{
			++count;
		}
		x >>= 1;
	}
	
	return count;
}


/* #############################             
# status: approved
# reviewer:shany             
# description: count set bits of a number, without a loop.
# return value: int.       
# special notes:            
#############################*/
int CountSetBitsNoLoop(int n)
{
	int count = 0, flag = 1;
	if (n)
	{
		n &= (n - 1);
		count = flag + CountSetBitsNoLoop(n);
	}
	
	return count;
}


/* #############################             
# status: approved
# reviewer:shany             
# description: recive float and print its bits.
# return value: void.       
# special notes:            
#############################*/
void FloatAnalysis(float f)
{
	unsigned int *i = (void*)&f;
	printf("%b\n", *i);
}











