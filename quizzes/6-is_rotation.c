#include <stdio.h>
#include <string.h>

int IsRotation(char *s1, char *s2)
{
	int i = 0, j = 0, s1_size = strlen(s1);
	int rot_found = 0;
	
	if(s1_size != strlen(s2))
	{
		return 0;
	}
	for(; i < s1_size; ++i)
	{
		rot_found = 1;
		for(j = 0; j < s1_size; ++j)
		{
			if(s1[(i+j) % s1_size] != s2[j])
			{
				rot_found = 0;
			}
		}
		if(1 == rot_found)
		{
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	char *s1 = "12345", *s2 = "45123";
	char *s3 = "121234", *s4 = "123412";
	char *s5 = "123456", *s6 = "234156";
	
	printf("%s is rot of %s? %d\n", s2, s1, IsRotation(s1, s2));
	printf("%s is rot of %s? %d\n", s4, s3, IsRotation(s3, s4));
	printf("%s is rot of %s? %d\n", s6, s5, IsRotation(s5, s6));
	
	return 0;
}

