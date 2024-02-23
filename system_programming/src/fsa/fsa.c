#include <stddef.h> /* Used for size_t type */
#include <stdio.h>
#include <assert.h> /* for assert*/

#include "../../include/fsa.h"


#define FSASIZE sizeof(fsa_t)
#define WORDSIZE sizeof(size_t)

#define ALIGNED_BLOCK(b) (((b) % WORDSIZE) ?\
	WORDSIZE - (b) % WORDSIZE + (b) : (b))


struct fsa
{
	size_t next;
};


/* Status : approved.
 * Reviewer : shany.
 * Description : recieve the requested block size and number of blocks requires by user, 
 				 and outputs the number of consecutive memory blocks needed for this module.	
 * Arguments : user requested block size and blocks amount.	
 * Return : size of memory needed for this module in bytes.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
size_t FSASuggestSize(size_t block_size, size_t block_count)
{	
	return ((ALIGNED_BLOCK(block_size) * block_count) + FSASIZE + WORDSIZE);
}


/* Status : approved.
 * Reviewer : michael evanov.
 * Description : recieves memory block, initiates free list and returns pointer to pool.	
 * Arguments : recieves a pointer to allocated memory by user, block size and the total 
 				amount of allocated memory in bytes.	
 * Return : pointer to pool. */
fsa_t *FSAInit(void *memory_p, size_t memory_size, size_t block_size)
{
	fsa_t *new_list = (fsa_t *)ALIGNED_BLOCK((size_t)memory_p);
	size_t offset = 0;
	
	memory_size -= WORDSIZE;
	block_size = ALIGNED_BLOCK(block_size);
	new_list->next = FSASIZE;
	
	/*initiate all blocks with thier next block offset*/ 
	for (offset = new_list->next; offset < (memory_size - block_size); offset += block_size)
	{		
		*(size_t *)((char *)new_list + offset) = offset + block_size;
	}
	
	/*initiate last block to 0, wich is management struct's address*/
	*(size_t *)((char *)new_list + offset) = 0;	
	return new_list;	
}


/* Status : approved.
 * Reviewer : shany.
 * Description : allocates one block to user.	
 * Arguments : fsa_pool pointer.	
 * Return : void pointer to block start. NULL if pool is empty.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
 void *FSAAlloc(fsa_t *fsa)
{
	void *offset = (void *)((char *)fsa + fsa->next);
	
	if (0 == *(size_t *)offset)
	{
		return NULL;
	}
	fsa->next = *(size_t *)offset;
	return offset;
}

 
/* Status : approved.
 * Reviewer : shany.
 * Description : frees one block from user.	
 * Arguments : void pointer to block and pool pointer.	
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void FSAFree(void *block, fsa_t *fsa)
{
    size_t offset = (char *)block - (char *)fsa;
    
    *(size_t *)block = fsa->next;
    fsa->next = offset;    
}


/* Status : approved.
 * Reviewer : shany.
 * Description : provides information about free blocks.	
 * Arguments : pool pointer.	
 * Return : number of free blocks.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
size_t FSACountFree(const fsa_t *fsa)
{
	size_t *ptr = NULL;
	size_t count = 0;
	
	for (ptr = (size_t *)((char *)fsa + fsa->next);  0 != *ptr;  ptr = (size_t *)((char *)fsa + *ptr))
	{
		++count;
	}
	return count;
}



