#ifndef __STRUCTS_H_CR4__
#define __STRUCTS_H_CR4__

#define MAX2(a, b) a > b? a : b

#define MAX3(a, b ,c) (MAX2(a, b) > c? MAX2(a, b) : c)

#define SIZEOF_VAR(var) (size_t)(&var + 1) - (size_t)&var 

#define SIZEOF_TYPE(type) (size_t)(((type *)0) + 1)




struct mystruct
{
	void *value;
	int(*Add)(void **vp, int);
	int(*Clear)(void *vp);
	int(*Print)(void *vp);
};

typedef struct mystruct mystruct;

int PrintInt(void *vp);
int PrintFloat(void *vp);
int PrintString(void *vp);
int AddInt(void **vp, int num);
int AddFloat(void **vp, int num);
int AddStr(void **vp, int num);
int ClearInt(void *value);
int ClearFloat(void *value);
int ClearString(void *value);
void ActivatePrint(mystruct *arr);
void ActivateAdd(mystruct *arr, int x);
void ActivateCleanUp(mystruct *arr);

#endif
