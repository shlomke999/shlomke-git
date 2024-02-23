#include <dlfcn.h>

#include "globalvar.h"

int main()
{
	void *foolib1;
	void *foolib2;
	void (*Fooa)();
	void (*Foob)();
	
	PrintGlobalVariableAddress();
	
	foolib1 = dlopen("./libfoo1.so", RTLD_LAZY);
	*(void **)(&Fooa) = dlsym(foolib1, "foo1");
	Fooa();
	dlclose(foolib1);
	
	foolib2 = dlopen("./libfoo2.so", RTLD_LAZY);	
	*(void **)(&Foob) = dlsym(foolib2, "foo2");
	
	Foob();
	
	dlclose(foolib2);
	
	return 0;
}
