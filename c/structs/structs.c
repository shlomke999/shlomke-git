#include <stdio.h>/*printf*/
#include <string.h>/*strlen*/
#include <stdlib.h>/*malloc*/

#include "structs.h"

enum Status {SUCCESS = 0, Failed = 1}; 



/*#############################             
status: approved
reviewer:shany             
description: add int to int.                
return value: int       
special notes:            
#############################*/
int AddInt(void **vp, int num)
{
	**((int **)vp) += num;
	return SUCCESS;
}
  
  
/*#############################             
status: approved
reviewer:shany             
description: add int to float.                
return value: int       
special notes:            
#############################*/
int AddFloat(void **vp, int num)
{
	**((float **)vp) += num;
	return SUCCESS;
}


/*#############################             
status: approved
reviewer:shany             
description: appened int to string.                
return value: int       
special notes:            
#############################*/
int AddStr(void **vp, int num)
{
	char append_str[16];
	*vp = realloc(*vp, (long int)(strlen(*vp) + sprintf(append_str, "%d", num) + 1));
	if (NULL == (char *)vp)
	{
		return Failed;
	}
	
	strcat(*vp, append_str);
	return SUCCESS;
}
  
     
int ClearInt(void *vp)
{
	(void)vp;
	return SUCCESS;
}   


int ClearFloat(void *vp)
{
	(void)vp;
	return SUCCESS;
}     


int ClearString(void *vp)
{
	free(vp);
	return SUCCESS;
}



int PrintInt(void *vp)
{
	printf("%d\n", *((int *)vp));
	return SUCCESS;
}


int PrintFloat(void *vp)
{
	printf("%f\n", *((float *)vp));
	return SUCCESS;
}


int PrintString(void *vp)
{
	printf("%s\n", ((char *)vp));
	return SUCCESS;
}





/*for testing*/ 
void ActivatePrint(mystruct *arr)
{
		arr[0].Print(arr[0].value);
		arr[1].Print(arr[1].value);
		arr[2].Print(arr[2].value);
}
void ActivateAdd(mystruct *arr, int x)
{
		arr[0].Add(&arr[0].value,x);
		arr[1].Add(&arr[1].value,x);
		arr[2].Add(&arr[2].value,x);
}
void ActivateCleanUp(mystruct *arr)
{
		arr[2].Clear(arr[2].value);
}

  
  
  
  
  
  
  
  
  


