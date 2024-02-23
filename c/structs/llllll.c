
#include <stdio.h>/*printf*/
#include <string.h>/*strlen*/
#include <stdlib.h>/*malloc*/

#define ELEM_AMOUNT 5 
#define MAX_DIGITS_FOR_INT 10 

enum Status {Working = 0, Failed = 1}; 

typedef struct elem
{
	int *vp;
	int (*add_p)(void*, int);
	int (*print_p)(void*); 
	int (*free_p)(void*);
}elem;

int InitializeElements();
int PrintElements();
int Add(int num);
int Free();
int PrintInt(void *vp);
int PrintFloat(void *vp);
int PrintString(void *vp);
int AddInt(void *vp, int num);
int AddFloat(void *vp, int num);
int Concatinate(void *vp, int num);
int FreeInt(void *value);
int FreeFloat(void *value);
int FreeString(void *value);

elem elements[ELEM_AMOUNT] = 
{
	{NULL, AddInt, PrintInt, FreeInt},
	{NULL, AddFloat, PrintFloat, FreeFloat},
	{NULL, AddInt, PrintInt, FreeInt},
	{NULL, AddFloat, PrintFloat, FreeFloat},
	{NULL, Concatinate, PrintString, FreeString},
};

int main()
{
	int num = 10;
	
	InitializeElements();
	PrintElements();
	Add(num);
	PrintElements();
	Free();
	PrintElements();

	return Working;
}

int InitializeElements()
{
	*(int *)&elements[0].vp = 14;
	*(float *)&elements[1].vp = 14.14;
	*(int *)&elements[2].vp = 15;
	*(float *)&elements[3].vp = 15.15;
	*(char **)&elements[4].vp = (char *)malloc(sizeof("Good morning my neighbors!"));
	
	if (NULL == *(char **)&elements[4].vp)
	{
		return Failed;
	}
	strcpy(*(char **)&elements[4].vp, "Good morning my neighbors!");
	
	return Working;
}


int PrintElements()
{
	int i = 0;
	for(; i < ELEM_AMOUNT; ++i)
	{
		(*elements[i].print_p)(&elements[i].vp);
	}
	printf("\n");
	return Working;
}

int Add(int num)
{
	int i = 0;
	for(; i < ELEM_AMOUNT; ++i)
	{
		(*elements[i].add_p)(&elements[i].vp, num);
	}
	return Working;
}

int Free()
{
	int i = 0;
	for(; i < ELEM_AMOUNT; ++i)
	{
		(*elements[i].free_p)(&elements[i].vp);
	}
	return Working;
}

int PrintInt(void *vp)
{	
	printf("%d ", *(int *)vp);
	return Working;
}

int PrintFloat(void *vp)
{	
	printf("%f ", *(float *)vp);
	return Working;
}

int PrintString(void *vp)
{
	printf("%s ", *(char **)vp);
	return Working;
}

int AddInt(void *vp, int num)
{
	*(int *)vp += num;
	return Working;
}

int AddFloat(void *vp, int num)
{
	*(float *)vp += num;
	return Working;
}

int Concatinate(void *vp, int num)
{
	char append_str[MAX_DIGITS_FOR_INT];
	int strlen_vp = 0;
	int append_strlen = 0;
	
	sprintf(append_str, "%d", num);
	strlen_vp = strlen(*(char **)vp);
	append_strlen = strlen(append_str);
	
	*vp = realloc(*vp, strlen_vp + append_strlen + 1);
	
	if (NULL == *(char **)vp)
	{
		return Failed;
	}
	
	strcat(*(char **)vp, append_str);
	return Working;
}

int FreeInt(void *vp)
{
	(void)vp;
	return Working;
}

int FreeFloat(void *vp)
{
	(void)vp;
	return Working;
}

int FreeString(void *vp)
{
	free(*(char **)vp);
	return Working;
}


