#include <stdlib.h>


int global_var1 = 1;
static static_global = 15;

static void StaticFunction()
{

}

extern void ExternFunction();


int main(int argc, char *argv[], char *envp[])
{
	int local_var1 = 42;
	int local_var2 = 420;
	int local_var3 = 4200;
	
	short* p_heap_var1 = (short*)malloc(85); /* Check allignment */      
    short* p_heap_var2 = (short*)malloc(14); /* Check allignment */      
    static int static_local_var1 = 333;
    int* p_static_local_var1 = &static_local_var1;
	int* plocal_var1 = &local_var1;
	int* plocal_var2 = &local_var2;
	int* plocal_var3 = &local_var3;
	int* p_global_var1 = &global_var1;
	int* p_global_var2 = &static_global;
	char *stlit = "why???!?!?!?!?";
	const char *const_stlit = "why???!?!?!?!?";
	static char local_static_str[] = {"gevvalld!"};
	const char local_const_str[] = {"I love libreries!"};
	char *env = NULL;
	
	
	for(local_var1 = 0; local_var1 < 40; ++local_var1)
	{
		env = envp[local_var1];
	}
	
	foo(local_var3);
}

