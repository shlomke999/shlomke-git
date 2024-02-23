#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	void *handle = NULL;
	void (*Foo)(int);
	int x = 5;
	handle = dlopen("/home/shlomi/git/system_programming/libraries/dynamic_lib/explicit/libfoo.so", RTLD_LAZY);
	if (!handle)
	{
		printf("Failed :( \n");
		exit(1);
	} 
	Foo = dlsym(handle, "Foo");
	
	Foo(x);
	
	dlclose(handle);
	return 0;
}

