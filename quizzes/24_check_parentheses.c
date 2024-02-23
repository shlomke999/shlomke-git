#include <stddef.h> /* size_t */
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/

#define COMPARE(x, y) ((x) == (y) ? 1 : 0)

typedef struct stack
{
	size_t size;
	size_t used;
	size_t elem_size;
	char *head;
}stack_t;


stack_t *StackCreate(const size_t size, const size_t element_size);
void StackDestroy(stack_t *stack);
void StackPush(stack_t *stack_p, int data);
void StackPop(stack_t *stack);
void *StackPeek(const stack_t *stack);
size_t StackSize(stack_t *stack_p);
int StackIsEmpty(stack_t *stack_p);
size_t StackCapacity(stack_t *stack_p);




typedef enum{
	BALANCED,
	NOT_BALANCED,
	OPEN_SQUARE,
	OPEN_ROUND,
	OPEN_CURLY
} myenum;


/*approved by shany*/
myenum Parentheses(char *str, size_t len)
{
	size_t i = 0;
	stack_t *q = StackCreate(len, sizeof(int));
	for (i = 0; i < (len - 1); ++i)
	{
		switch (str[i])
		{
		case '(':
			StackPush(q, OPEN_ROUND);
			break;
		case '[':
			StackPush(q, OPEN_SQUARE);
			break;
		case '{':
			StackPush(q, OPEN_CURLY);
			break;
		case ')':
			if (!COMPARE(*(int *)StackPeek(q), OPEN_ROUND))
			{
				StackDestroy(q);
				return NOT_BALANCED;
			}
			StackPop(q);
			break;
		case ']':
			if (!COMPARE(*(int *)StackPeek(q), OPEN_SQUARE))
			{
				StackDestroy(q);
				return NOT_BALANCED;
			}
			StackPop(q);
			break;
		case '}':
			if (!COMPARE(*(int *)StackPeek(q), OPEN_CURLY))
			{
				StackDestroy(q);
				return NOT_BALANCED;
			}
			StackPop(q);
			break;
		default:
			return NOT_BALANCED;
			break;
		}
	}
	return BALANCED;
}


int main()
{
	char str[] = {"{()[)}()[{}]"};
	char str2[] = {"{()[]}()[{}]"};
	printf("return 0 if string has balanced parentheses: \n\n");
	printf("%d\n", Parentheses(str, 13));
	printf("return 0 if string has balanced parentheses: \n\n");
	printf("%d\n", Parentheses(str2, 13));
	return 0;
}




























stack_t *StackCreate(const size_t size, const size_t elem_size)
{
	stack_t *user_stack = malloc(sizeof(stack_t) + (size * elem_size));
	if (NULL == user_stack)
	{
		return 0;	
	}
	assert(size && elem_size);
	user_stack->head = (char *)(user_stack + (sizeof(stack_t)));
	user_stack->size = size;
	user_stack->used = 0;
	user_stack->elem_size = elem_size;
	return user_stack;
}
void StackDestroy(stack_t *stack_p)
{
	assert (stack_p);
	free(stack_p);
	stack_p = NULL;
	
}
void StackPush(stack_t *stack_p, int data)
{
	int *d = &data;
	if (stack_p->used < stack_p->size)
	{
		memcpy((stack_p->head + (stack_p->used * stack_p->elem_size)), 
		d, stack_p->elem_size);
		stack_p->used += 1;
	}
	else
	{
		printf("stack is full");
	}
}
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
void *StackPeek(const stack_t *stack_p)
{
	assert (stack_p);
	return (stack_p->head + ((stack_p->used - 1) * stack_p->elem_size));
}
int StackIsEmpty(stack_t *stack_p)
{
	assert (stack_p);
	return (!(stack_p->used)) ? 1 : 0;
}
size_t StackSize(stack_t *stack_p)
{
	assert (stack_p);
	return stack_p->used;
}
size_t StackCapacity(stack_t *stack_p)
{
	assert (stack_p);
	return stack_p->size * stack_p->elem_size;
}









































































