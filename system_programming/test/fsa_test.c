#include <stddef.h> /* Used for size_t type */
#include <stdlib.h> /* malloc free */
#include <stdio.h> /* printf */

#include "../include/fsa.h"

int main(void)
{
	
	size_t block_count = 5;
	size_t block_size = 1024;
	size_t fsa_size = FSASuggestSize(block_size, block_count);
	void *memory = malloc(fsa_size);
	void *block1 = NULL, *block2 = NULL, *block3 = NULL, *block4 = NULL, *block5 = NULL, *block6 = NULL;
	fsa_t *fsa = NULL;
	
	if (NULL == memory)
	{
		return 1;
	}
	/***********init************/
	fsa = FSAInit(memory, fsa_size, block_size);
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa));
	printf(" %p \n", (char *)fsa);
	printf(" %p \n", (char *)memory);
	
	/***********alloc************/
	block1 = FSAAlloc(fsa);
	block2 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);
	block4 = FSAAlloc(fsa);
	block5 = FSAAlloc(fsa);
	block6 = FSAAlloc(fsa); /* this should return NULL */
	if (NULL == block6)
	{
		printf("worked\n");
	}
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa));
	/***********free************/
	FSAFree(block1, fsa);
	FSAFree(block2, fsa);
	FSAFree(block3, fsa);
	FSAFree(block4, fsa);
	FSAFree(block5, fsa);
	
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa)); 
	
	free(memory);
	memory = NULL;	
	return (0);
}

