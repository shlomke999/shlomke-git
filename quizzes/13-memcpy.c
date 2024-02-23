#include <stddef.h>
#include <stdio.h>

void *MemCpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	void *s_start = dest;
	
	while(i < n)
	{
		if((n - i) > 8)
		{
			*(size_t *)((char *)dest + i) = *(size_t *)((char *)src + i);
			i += sizeof(size_t);
		}
		else
		{
			*((char *)dest + i) = *((char *)src + i);
			++i;
		}
	}
	
	return s_start;
}



int main(void)
{
	char src[] = "12345678912345 werwerwer werwgqwe";
	char cpy[30];
	MemCpy(cpy, src, 10);
	printf("the string that was copy: %s", cpy);
	
	return 0;
}

