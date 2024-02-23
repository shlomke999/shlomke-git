#ifndef __VSA_H_CR4__ 
#define __VSA_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */

/* Status : 
 * Reviewer : 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 */


typedef struct vsa vsa_t;


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : Recieves memory pool, initiate vsa struct,
 *				 returns pointer to vsa struct. Minimum size is 24 bytes.
 * Arguments : memory_p -  a pointer to allocated memory by user.
 *			   memory_size - the total amount of allocated memory in bytes.
 * Return : pointer to pool.
 * Time Complexity - O(1).
 * Space Complexity - O(1). 
 */
vsa_t *VSAInit(void *memory_p, size_t memory_size);


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : Allocates a block to user the size of block_size.
 * Arguments : vsa_pool - pointer to the pool
 * 			   block_size - size of block to allocate, in bytes.
 * Return : void pointer to block start.
 * 			If no space available - undefined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
void *VSAAlloc(vsa_t *vsa_pool, size_t block_size);


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : Frees one block from user.
 * Arguments : block - void pointer to a block.
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void VSAFree(void *block);


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : provides information about free blocks.
 * Arguments : vas_pool - pool pointer.
 * Return : number of bytes in largest available block.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
size_t VSALargestBlockAvailable(const vsa_t *vsa_pool);


#endif /* __VSA_H_CR4__ */
