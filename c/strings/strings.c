#include<assert.h>
#include<stddef.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include"strings.h"


int StrCmp(const char *s1, const char *s2)
{
	assert (NULL != s1 && NULL != s2);
	while ((*s1 == *s2) && (*s1 != '\0')) 
	{
		++s1;
		++s2;
	}
	return (*s1  - *s2);
}


size_t StrLen (const char *s)
{
	const char *start_char = s;
	assert (NULL != s);
	while ('\0' != *s) 
	{
		++s;
	}
	return s - start_char;
}


char *StrCpy(char *dest, const char *src)
{
	char *dest_start = dest;
	assert(NULL != dest && NULL != src);
	while (*src != '\0')
	{
		*dest = *src;
		++src;
		++dest;
	}
	
	*dest = *src;
	return dest_start;
}


char *StrnCpy(char *dest, const char *src, size_t n)
{
        size_t i;
        for (i = 0; i < n && src[i] !='\0'; i++)
        {
        	dest[i] = src[i];
        }
        for (; i < n; i++)
        {
      		dest[i] = '\0';
        }
        return dest;	
}


int StrnCmp(char const *str1_ptr, char const *str2_ptr, size_t n)
{
	assert(str1_ptr && str2_ptr);

	while (*str1_ptr == *str2_ptr && '\0' != *str1_ptr)
	{
		++str1_ptr, ++str2_ptr;
		--n;
	}

	return !n ? 0 : *str1_ptr - *str2_ptr;
}




int StrCaseCmp(const char *s1, const char *s2)
{
	assert (NULL != s1 && NULL != s2);
	while (MyToLower(*s1) == MyToLower(*s2) && '\0' != *s1)
	{
		s1++, s2++;
	}
	return MyToLower(*s1) - MyToLower(*s2);
}


char *StrChr(const char *s, int c)
{
	assert (NULL != s);
	while (*s++ != '\0' && *s != c)
	{	
	}
	if (*s == c)
	{
		return (char*) s;
	} 
	return NULL;	
}


char *StrDup(const char *s)
{	
	char *new_string = malloc(StrLen(s + 1));
	return StrCpy(new_string , s);
}


char *StrCat(char *dest, const char *src)
{
	assert (NULL != dest && NULL != src);	
	while (*dest != '\0')
	{
		++dest;
	}	
	while (*src != '\0')
	{
		*dest = *src;
		++src;
		++dest;
	}	
	*dest = '\0';
	return dest;
}


char *StrnCat(char *dest, const char *src, size_t n)
{
	size_t i = 0;
	assert (NULL != dest && NULL != src);	
	while (*dest != '\0')
	{
		++dest;
	}	
	for (; i < n; i++)
	{	
		if (*src != '\0')
		*dest = *src;
		++src;
		++dest;
	}	
	*++dest = '\0';
	return dest;
}


char *StrStr(const char *haystack, const char *needle)
{
	int needle_size =StrLen(needle);
	if ((*haystack == '\0' && *needle == '\0') || *needle == '\0')
	{
		return (char*)haystack;
	}
	while ('\0' != *haystack)
	{
		if (StrnCmp(haystack, needle, needle_size) == 0)
		{
			return (char*)haystack;
		}
		++haystack;		
	}
	return NULL;	
}


size_t StrSpn(const char *s, const char *accept)
{
	const char *start = s;
	assert (s && accept);
	while ((*s == *accept) && '\0' != *s)
	{
		++s;
		++accept;
	}
	return s - start;
}


int IsPalindrome(char *s)
{
	int length = StrLen(s);
	char *ptr1 = s, *ptr2 = (s + length - 1);
	if (1 >= length)
	{
		return 1;
	}
	
	while (*ptr1 == *ptr2 && (s != ptr2))
	{
		++ptr1;
		--ptr2;
	}
	if (*ptr1 == *ptr2)
	{
		return 1;
	}
	
	return 0;			
}


char MyToLower(char c)
{
	if ('A' <= c && 'Z' >= c)
	{
		return c + 32;
	}
	return c;
}



