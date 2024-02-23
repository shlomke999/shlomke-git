#include <stdio.h> /*print*/

#include "globalvar.h"

int x;

void PrintGlobalVariableAddress()
{	
	printf("Global %p\n", &x);
}
