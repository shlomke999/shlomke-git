#include <stdlib.h> /*malloc*/
#include <stddef.h> /*size_t*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
 
#include "../../include/stack.h"

struct stack
{
	size_t capacity;
	size_t elem_size;
	size_t curr_size;
	char *start;
};


/*
# status: approved
# reviewer:shany             
# description: create a stack.        
# return value: pointer to the stack, and null on failur.      
# special notes: 
*/ 
stack_t *StackCreate(const int size, const int elem_size)
{
	stack_t *stack = malloc(sizeof(stack_t) + size * elem_size); 
	
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack->capacity = size * elem_size;
	stack->elem_size = elem_size;
	stack->curr_size = 0;
	stack->start = (char *)(stack + sizeof(stack_t));
	
	return stack;	 
} 


/*
# status: approved
# reviewer:shany             
# description: free the stack.         
# return value:void.     
# special notes: 
*/ 
void StackDestroy(stack_t *stack_ptr)
{
	assert(stack_ptr);
	
	free(stack_ptr);
	stack_ptr = NULL;
	
}


/*
# status: approved
# reviewer:shany             
# description: push new value to the top of the stack.       
# return value: void.    
# special notes: 
*/ 
void StackPush(stack_t *stack_ptr, const void *data)
{
	assert(stack_ptr);
	assert(data);
	
	memcpy(stack_ptr->start, data, stack_ptr->elem_size); 
	stack_ptr->start +=  stack_ptr->elem_size;
	stack_ptr->curr_size += 1;
	
}


/*
# status: approved
# reviewer:shany             
# description: pop a value from the top of the stack.       
# return value: void.      
# special notes: 
*/ 
void StackPop(stack_t *stack_ptr)
{
	assert(stack_ptr);
	
	--stack_ptr->curr_size;
}


/*
# status: approved
# reviewer:shany             
# description: show the value stored at the top of the stack.       
# return value: void.      
# special notes: 
*/ 
void *StackPeek(const stack_t *stack_p)
{
	assert (stack_p);
	return (stack_p->start + ((stack_p->curr_size - 1) * stack_p->elem_size));
}



/*
# status: approved
# reviewer:shany             
# description: check if stack is empty.          
# return value: 1 if empty 0 if not.      
# special notes: 
*/ 
int StackIsEmpty(const stack_t *stack_ptr)
{
	assert(stack_ptr);

	return (0 == stack_ptr->curr_size? 1 : 0);

}


/*
# status: approved
# reviewer:shany             
# description: check stack size.          
# return value: stack size.     
# special notes: 
*/ 
size_t StackSize(const stack_t *stack_ptr)
{
	assert(stack_ptr);
	
	return stack_ptr->curr_size * stack_ptr->elem_size;
}


/*
# status: approved
# reviewer:shany             
# description: check stack capacity.       
# return value: stack capacity.      
# special notes: 
*/  
size_t StackCapacity(const stack_t *stack_ptr)
{
	assert(stack_ptr);
	
	return stack_ptr->capacity - stack_ptr->curr_size;
}













