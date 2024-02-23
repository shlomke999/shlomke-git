#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> /* to lower*/

/* STATUS: APPROVED.
   by: michael aponin. 
*/
void TF(int num)
{
	int i = 1;
	
	for(; i<=num; ++i)
	{
		if(0 == i % 15)
		{
			printf("TF\n");
		}
		
		else if( 0 == (i % 3))
		{
			printf("T\n");
		}
		
		else if( 0 == (i % 5))
		{
			printf("F\n");
		}
		else
		{			
			printf("%d\n", i);
		}
	}	
	 
}


char ToLower(char c)
{
	return (c > 'A' && c < 'Z'? c+32: c);
}


char *StrReverse(char *s)
{
	char *start = s, *end = (s + strlen(s) - 1);
	char temp;
	
	while(end - start > 0)
	{
		*end = tolower(*end);
		*start = tolower(*start);
		temp = *start;
		*start = *end;
		*end = temp;
		
		--end;
		++start;
	}	
	return s;
}


int main(void)
{

	char str[] = "SHLOMKEP";
	StrReverse(str);	
	printf ("%s\n", StrReverse(str));
	
	
	return 0;
}

