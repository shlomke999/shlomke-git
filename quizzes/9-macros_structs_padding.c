#include <stdio.h>

#define MAX3(a, b, c) ((a>b && a>c) ? a : ((b>c) ? b : c))
#define TO_LOWER(a) ((a>='A' && a<='Z') ? a+('a'-'A') : a)
#define OFFSET(s, f) ((char *)&f - (char *)&s)


/*
status: approved.
by: michael aponin.
*/
struct quiz
{
	int i;
	char c;
	int *ptr;
	long l;
}q8 = {13, 'a', NULL, 306};

int main(void)
{
	
	printf("Max of 3, 19, 7 is %d\n", MAX3(3, 19, 7));
	printf("Lowercase of %c is %c\n", 'Q', TO_LOWER('Q'));
	printf("Offset of int* from q8 is %d bytes\n", OFFSET(q8, q8.ptr));
	
	return 0;
}

