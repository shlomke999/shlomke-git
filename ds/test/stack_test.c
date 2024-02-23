#include "../include/stack.h"

#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdio.h> /*print*/


#define SHOW_D(x) printf(#x" = %d\n", x)
#define SHOW_L(x) printf(#x" = %lu\n", x)
/*
stack_t *StackCreate(const size_t size, const size_t elem_size); 	X
void StackDestroy(stack_t *stack);					
void StackPush(stack_t *stack, const void *data);			X
void *StackPeek(const stack_t *stack);					X
void StackPop(stack_t *stack);						X
int StackIsEmpty(const stack_t *stack);					
size_t StackSize(const stack_t *stack);
size_t StackCapacity(const stack_t *stack);
*/
int main(void)
{
	size_t i = 0;
	int arr_i[] = { 1, 2, 3, 4, };
	stack_t *my_stack = NULL;
	my_stack = StackCreate(5, 4);
	assert(my_stack);
	
	for (i = 0; sizeof(arr_i) / sizeof(arr_i[0]) > i; ++i)
	{
		StackPush(my_stack, arr_i + i);
	}
/*	StackPop(my_stack);i*/
	SHOW_D(*(int*)(StackPeek(my_stack)));
	SHOW_L(StackSize(my_stack));
	SHOW_D(StackIsEmpty(my_stack));
	
	SHOW_L(StackCapacity(my_stack));
	StackPop(my_stack);
	SHOW_D(*(int*)StackPeek(my_stack));
	SHOW_L(StackSize(my_stack));
	StackPop(my_stack);
	SHOW_D(*(int*)StackPeek(my_stack));
	SHOW_L(StackSize(my_stack));
	StackPop(my_stack);
	SHOW_L(StackCapacity(my_stack));
	SHOW_D(*(int*)StackPeek(my_stack));
	SHOW_L(StackSize(my_stack));
	StackPop(my_stack);
	SHOW_D(StackIsEmpty(my_stack));
	SHOW_L(StackSize(my_stack));
	SHOW_L(StackCapacity(my_stack));

	StackDestroy(my_stack);
	

	return 0;
}

