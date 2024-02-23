#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structs.h"

int main()
{
		
	int a = 6;
	float b = 7.7;
	char *str = "string";
	mystruct arr[3];
	
    arr[2].value = malloc(strlen(str) + 1);
    strcpy(arr[2].value, str);
	arr[0].value = (void *)&a;
	arr[1].value = (void *)&b;
	arr[0].Add = &AddInt;
	arr[1].Add = &AddFloat;
	arr[2].Add = &AddStr;
	arr[0].Print = &PrintInt;
	arr[1].Print = &PrintFloat;
	arr[2].Print = &PrintString;
	arr[2].Clear = &ClearString;	
	
	ActivatePrint(arr);
	ActivateAdd(arr, 10);
	ActivatePrint(arr);
	ActivateCleanUp(arr);
	
	/*test for defines
	long double x = 5;
	printf("%lu\n", SIZEOF_VAR(x));
	printf("%lu\n", SIZEOF_TYPE(float));
	*/


	return 0;
}

