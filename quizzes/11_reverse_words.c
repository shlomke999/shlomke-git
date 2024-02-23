#include <stdio.h>
#include <string.h>

/*approved by adir*/
char *ReverseWords(char *str, char *dest)
{
	int i = strlen(str)-1, j = 0;
	int k = 0;
	
	while(i >= 0)
	{
		if(str[i] == ' ' || 0 == i)
		{
			if(0 == i)
			{
				--i;
			}
			for(j=i+1; str[j]!=' ' && str[j]!='\0'; ++j)
			{
				dest[k] = str[j];
				++k;
			}
			dest[k++] = ' ';
		}
		--i;
	}
	dest[k-1] = '\0';
	
	return dest;
}

int main(void)
{
	char str[] = "my name is shlomi .";
	char str2[50];
	
	ReverseWords(str, str2);
	
	printf("\'%s\' -> \'%s\'\n", str, str2);
	
	return 0;
}
