#ifndef __FSA_H_CR4__ 
#define __FSA_H_CR4__ 

#include <stddef.h> /* Used for size_t type */


typedef struct fsa fsa_t;




/* Status : 
 * Reviewer : 
 * Description : recieve the requested block size and number of blocks requires by user, 
 				 and outputs the number of consecutive memory blocks needed for this module.
	
 * Arguments : user requested block size and blocks amount.
	
 * Return : size of memory needed for this module in bytes.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
size_t FSASuggestSize(size_t block_size, size_t block_count);



/* Status : 
 * Reviewer : 
 * Description : recieves memory block, initiates free list and returns pointer to pool.
	
 * Arguments : recieves a pointer to allocated memory by user, block size and the total 
 				amount of allocated memory in bytes.
	
 * Return : pointer to pool.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */
fsa_t *FSAInit(void *memory_p, size_t memory_size, size_t block_size);



/* Status : 
 * Reviewer : 
 * Description : allocates one block to user.
	
 * Arguments : fsa_pool pointer.
	
 * Return : void pointer to block start. NULL if pool is empty.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void *FSAAlloc(fsa_t *fsa_pool);



/* Status : 
 * Reviewer : 
 * Description : frees one block from user.
	
 * Arguments : void pointer to block and pool pointer.
	
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void FSAFree(void *block, fsa_t *fsa_pool);



/* Status : 
 * Reviewer : 
 * Description : provides information about free blocks.
	
 * Arguments : pool pointer.
	
 * Return : number of free blocks.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
size_t FSACountFree(const fsa_t *fsa_pool);

#endif /* __FSA_H_CR4__ */
