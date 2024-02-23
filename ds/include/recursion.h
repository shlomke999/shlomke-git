#ifndef __RECURSION_H_CR4__ 
#define __RECURSION_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */



typedef struct stack stack_t;

typedef struct Node_t
{
	int val;
	struct Node_t *next;
} Node;


int Fibonacci(size_t element_index);
int FibonacciRecursion(size_t element_index);
Node *FlipList(Node *node);
size_t StrLen (char *str);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStrRecursive(const char *haystack, const char *needle);
int StackCheckAndSwap(int value, stack_t *stack, int flag);
void SortStack(stack_t *stack);


stack_t *StackCreate(const size_t size, const size_t elem_size);
void StackDestroy(stack_t *stack_p);
void StackPush(stack_t *stack_p, const void *data);
void StackPop(stack_t *stack_p);
void *StackPeek(const stack_t *stack_p);
int StackIsEmpty(stack_t *stack_p);
size_t StackSize(stack_t *stack_p);
size_t StackCapacity(stack_t *stack_p);



#endif /* __RECURSION_H_CR4__ */
