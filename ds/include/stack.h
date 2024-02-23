#ifndef __STACK_H_CR4__
#define __STACK_H_CR4__

#include <stddef.h>



typedef struct stack stack_t;



stack_t *StackCreate(const int size, const int elements);

void StackDestroy(stack_t *stack_ptr);

void StackPush(stack_t *stack_ptr, const void *data);

void StackPop(stack_t *stack_ptr);

void *StackPeek(const stack_t *stack_ptr);

int StackIsEmpty(const stack_t *stack_ptr);

size_t StackSize(const stack_t *stack_ptr);

size_t StackCapacity(const stack_t *stack_ptr);



#endif
