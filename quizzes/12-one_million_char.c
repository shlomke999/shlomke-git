#include <stddef.h>/*size_t*/
#include <stdio.h>/*printf*/

size_t OneMillChar(char c)
{
	size_t most_times = 0;
	int i = 0;
	static size_t char_count_arr[127] = {0};
	
	if(0 == c)
	{
		while(i < 127)
		{
			if(most_times < char_count_arr[i])
			{
				most_times = char_count_arr[i];
			}
			++i;
		}
		return most_times;
	}
	
	++char_count_arr[c - 1];
	
	return most_times;
}


size_t CountBits(long n)
{
	size_t count = 0;
	
	while(n)
	{
		n = n & (n - 1);
		++count;
	}
	return count;
}

int main()
{
	int i = 0;
	for(i = 1 ;i<100;++i)
	{
	
		if(0 == i%26)
		{
			OneMillChar('8');
		}
		if(0 == i%26)
		{
			OneMillChar('b');
		}
	}
	
	printf("most times same char appeared is: %ld\n\n", OneMillChar(0));
  
	printf("count set bit of 143 is 5,result is: %ld\n", CountBits(143));
	return 0;
}

