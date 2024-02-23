#include <stddef.h> /*size_t*/
#include <stdio.h> /*print*/
#include <string.h> /* for strings */
#include <stdlib.h> /* Used for malloc and free */
#include <assert.h>

#include "../../include/recursion.h"

struct stack
{
	size_t size;
	size_t used;
	size_t elem_size;
	char *head;
};

#define MAX2(a, b) ((a < b) ? b : a)
#define MIN2(a, b) ((a > b) ? b : a)



stack_t *StackCreate(const size_t size, const size_t elem_size)
{
	stack_t *user_stack = malloc(sizeof(stack_t) + (size * elem_size));
	if (NULL == user_stack)
	{
		return 0;	
	}
	user_stack->head = (char *)(user_stack + (sizeof(stack_t)));
	user_stack->size = size;
	user_stack->used = 0;
	user_stack->elem_size = elem_size;
	return user_stack;
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func frees a dynamicly allocated stack pointer 
return: nothing     
special notes:        
#############################*/

void StackDestroy(stack_t *stack_p)
{
	assert (stack_p);
	free(stack_p);
	stack_p = NULL;
	
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func adds a data value to the stack        
return: nothing     
special notes:          
#############################*/

void StackPush(stack_t *stack_p, const void *data)
{
	assert (stack_p);
	assert (data);
	if (stack_p->used < stack_p->size)
	{
		memcpy((stack_p->head + (stack_p->used * stack_p->elem_size)), 
		(char *)data, stack_p->elem_size);
		stack_p->used += 1;
	}
	else
	{
		printf("stack is full");
	}
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func removes a data value from the stack        
return: nothing     
special notes:          
#############################*/

void StackPop(stack_t *stack_p)
{
	assert (stack_p);
	if (stack_p->used > 0)
	{
		--stack_p->used;
	}
	else
	{
		printf("stack is empty\n");
	}
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func returns a pointer to the most 
recently pushed data value on the stack        
return: pointer to the recent push value, assert if input is NULL    
special notes:          
#############################*/

void *StackPeek(const stack_t *stack_p)
{
	assert (stack_p);
	return (stack_p->head + ((stack_p->used - 1) * stack_p->elem_size));
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func determines if stack is empty      
return: 1 = empty, 0 = not empty   
special notes:          
#############################*/

int StackIsEmpty(stack_t *stack_p)
{
	assert (stack_p);
	return (!(stack_p->used)) ? 1 : 0;
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func returns stack size   
return: 1 = empty, 0 = not empty   
special notes:          
#############################*/

size_t StackSize(stack_t *stack_p)
{
	assert (stack_p);
	return stack_p->used;
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func returns stack capacity   
return: 1 = empty, 0 = not empty   
special notes:          
#############################*/

size_t StackCapacity(stack_t *stack_p)
{
	assert (stack_p);
	return stack_p->size * stack_p->elem_size;
}








/* Status : approved
 * Reviewer : michael aponin.
 * Description : returns the Fibonacci value of a given index
 * Arguments : int index	
 * Return : the value of Fibonacci number at given index 
 */
int Fibonacci(size_t element_index)
{
	size_t i = 2;
	size_t elem_1 = 0, elem_2 = 1, elem_next = 1;	
	
	if (element_index < 2)
	{
		return element_index;
	}
	for (i = 2; i <= element_index; ++i)
	{
		elem_next = elem_1 + elem_2;
		elem_1 = elem_2;
		elem_2 = elem_next;
	}
	return elem_next;
}



/* Status : approved
 * Reviewer : michael aponin.
 * Description : returns the Fibonacci value of a given index
 * Arguments : int index	
 * Return : the value of Fibonacci number at given index 
 */
int FibonacciRecursion(size_t element_index)
{
	if (element_index <= 1)
	{
		return element_index;
	}
	else
	{
		return FibonacciRecursion(element_index - 1) + FibonacciRecursion(element_index - 2);
	}
}



int StackCheckAndSwap(int value, stack_t *stack, int flag)
{
	int pop = *(int *)StackPeek(stack);
	int push = MAX2(value, pop);
	StackPop(stack);
	if (pop < value)
	{
		++flag;
	}
	if (!StackIsEmpty(stack))
	{

		StackCheckAndSwap(push, stack, flag);
		push = MIN2(pop, value);
	}
	else if (StackIsEmpty(stack))
	{
		StackPush(stack, &push);
		push = MIN2(pop, value);
	}
	StackPush(stack, &push);
	return flag;
}
/* Status : approved
 * Reviewer : Adi
 * Description : sorts an unsorted stack, recursively.
 * Arguments :
 * Return :
 */
void SortStack(stack_t *stack)
{
	int flag = 0;
	int pop = *(int *)StackPeek(stack);
	StackPop(stack);
	if (StackCheckAndSwap(pop, stack, flag))
	{
		SortStack(stack);
	}
	return;
}




/* Status : approved
 * Reviewer : michael aponin. 
 * Description : flips the order of nodes in a linked list
 * Arguments : 	head node iterator
 * Return :  new head node iterator
 */
Node *FlipList(Node *node)
{
	Node *rest = NULL;
	if(NULL == node->next)
	{
		return node;
	}
	rest = FlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	return rest;
}


/* Status : approved
 * Reviewer : michael aponin. 
 * Description : count the order of characters in a string.
 * Arguments : pointer to string.
 * Return :  number of characters.
 */
size_t StrLen (char *str) 
{
    if (0 == *str)
    {
        return 0;
    }

    return StrLen(++str) + 1;
}


/* Status : approved
 * Reviewer :  elad.
 * Description : compares the two strings s1 and s2.
 * Arguments : pointer to strings
 * Return :  functions return an integer less than, equal to, or
       greater than zero if s1 (or the first n bytes thereof) is 
       found to be less than, to match, or be greater than s2.
 */
int StrCmp(const char *s1, const char *s2)
{
	if('\0' == *s1 || *s1 != *s2)
	{
		return *s1 - *s2;
	}
	return StrCmp(s1 + 1, s2 + 1);
}


/* Status : approved
 * Reviewer :  elad.
 * Description : copies the string pointed to by src, including the termi‐
       nating null byte ('\0'), to the buffer pointed to by dest. The strings 
       may not overlap,  and  the  destination string dest must be large 
       enough to receive the copy.
 * Arguments : pointer to strings
 * Return :  a pointer to the destination string.
 */
char *StrCpy(char *dest, const char *src)
{
	if ('\0' != *src)
	{
		*dest = *src;
		++src, ++dest;
		StrCpy(dest, src);
	}
	else
	{
		*dest = '\0';
		return dest;
	}
	--dest;
	return dest;
}


/* Status : approved
 * Reviewer :  elad.
 * Description : appends the src string to the dest string, overwriting
       the terminating null byte ('\0') at the end of dest, and then adds 
       a terminating null byte.
 * Arguments : pointer to strings
 * Return :  a pointer to the destination string.
 */

char *StrCat(char *dest, const char *src)
{
	if ('\0' != *dest)
	{
		++dest;
		StrCat(dest, src);
	}
	else if ('\0' != *src)
	{
		StrCpy(dest, src);		
	}
	--dest;
	return dest;
}


/* Status : approved
 * Reviewer : michael aponin 
 * Description : finds the first occurrence of the substring needle in the
       			string haystack. The terminating null bytes ('\0') are not compared.
 * Arguments : pointer to strings
 * Return : pointer to the beginning of the located substring, or NULL if the
			  substring is not found.
 */	
char *StrStrRecursive(const char *haystack, const char *needle)
{
	if(strlen(haystack) < strlen(needle))
	{
		return NULL;
	}
	if(0 == strlen(needle) || 0 == strncmp(haystack, needle, strlen(needle)))
	{
		return (char *)haystack;
	}
	return StrStrRecursive(++haystack, needle);
}


	
















