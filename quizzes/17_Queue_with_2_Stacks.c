#include <stddef.h> /* size_t */
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/


typedef struct _stack stack_t;
struct _stack
{
	size_t capacity;
	size_t element_size;
	size_t curr_size;
	char *start;
};

stack_t *StackCreate(const size_t size, const size_t element_size);
void StackDestroy(stack_t *stack);
void StackPush(stack_t *stack, const void *data);
void StackPop(stack_t *stack);
void *StackPeek(const stack_t *stack);
size_t StackSize(const stack_t *stack);
int StackIsEmpty(const stack_t *stack);
size_t StackCapacity(const stack_t *stack);



/*approved by elad*/

void Enqueue(stack_t *enq, stack_t *deq, void *data)
{
	if(StackIsEmpty(enq))
	{
		while(!StackIsEmpty(deq))
		{
			StackPush(enq, StackPeek(deq));
			StackPop(deq);
		}
	}
	
	StackPush(enq, data);
}



void *Dequeue(stack_t *enq, stack_t *deq)
{
	void *poped_elem = NULL;
	
	while (0 == StackIsEmpty(enq))
	{
		StackPush(deq, StackPeek(enq));
		StackPop(enq);
	}
		
	poped_elem = StackPeek(deq);
	StackPop(deq);	
	
	return poped_elem;	
}


int main(void)
{
	size_t size = 10;
	int a = 5, b = 7, c = 10;
	stack_t *enq = StackCreate(size, sizeof(int));
	stack_t *deq = StackCreate(size, sizeof(int));

	Enqueue(enq, deq, &a);
	Enqueue(enq, deq, &b);
	Enqueue(enq, deq, &c);
	printf("Dequeued %d\n", *(int *)Dequeue(enq, deq));
	printf("Dequeued %d\n", *(int *)Dequeue(enq, deq));
	printf("Dequeued %d\n", *(int *)Dequeue(enq, deq));

	StackDestroy(enq);
	StackDestroy(deq);
	return 0;

}




































stack_t *StackCreate(const size_t size, const size_t element_size)
{
	stack_t *st = NULL;
	st = (stack_t *)malloc(sizeof(stack_t));
	if(NULL == st)
	{
		return (NULL);
	}
	
	st->capacity = size;
	st->element_size = element_size + 1;
	st->curr_size = 0;
	st->start = (char *)malloc(size * (element_size + 1) * sizeof(char));
	if(NULL == st->start)
	{
		free(st);
		return (NULL);
	}
	strcpy(st->start, "\0");
	
	return (st);
}


void StackDestroy(stack_t *stack)
{
	free(stack->start);
	free(stack);
}


void StackPush(stack_t *stack, const void *data)
{
	if(stack->curr_size < stack->capacity)
	{
		memcpy( (stack->start + (stack->curr_size * stack->element_size)), 
				(char *)data, 
				stack->element_size);
		stack->curr_size += 1;
		*(stack->start + (stack->curr_size * stack->element_size) - 1) = '\0';
	}
	else
	{
		printf("Can't push; Stack is full\n");
	}
}


void StackPop(stack_t *stack)
{
	if(stack->curr_size > 0)
	{
		stack->curr_size -= 1;
	}
	else
	{
		printf("Nothing to pop; Stack is empty\n");
	}
}


void *StackPeek(const stack_t *stack)
{
	if(stack->curr_size > 0)
	{
		return (stack->start + ((stack->curr_size - 1) * stack->element_size));
	}
	printf("Nothing to show; Stack is empty\n");
	return NULL;
}

/* Status : Approved
 * Reviewer : Shani Gull
 * Description : 
 		The function returns the current used blocks count to the user. It will
 		reflect the number of used blocks only and not the overall used space
 		in bytes.
 * Arguments : 
		stack - stack_t, stack-managing structure.
 * Return : size_t - number of used blocks.
 */
size_t StackSize(const stack_t *stack)
{
	return (stack->curr_size);
}

/* Status : Approved
 * Reviewer : Shani Gull
 * Description : 
 		The function checks if the stack is empty. Returns 1 if no blocks are 
 		used, and 0 if at least one block is in use.
 * Arguments : 
		stack - stack_t, stack-managing structure.
 * Return : int - boolean result of stack usage.
 */
int StackIsEmpty(const stack_t *stack)
{
	return (0 == stack->curr_size ? 1 : 0);
}

/* Status : Approved
 * Reviewer : Shani Gull
 * Description : 
 		The function returns the overall capacity in blocks (not in total bytes)
 		of the stack.
 * Arguments : 
		stack - stack_t, stack-managing structure.
 * Return : size_t - total blocks that were allocated to the stack.
 */
size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}













