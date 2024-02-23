#ifndef __CBUFF_H__
#define __CBUFF_H__

#include <sys/types.h> /* size_t */

typedef struct c_buff c_buff_t;

/*---------------------------------------------------- CBuffCreate -------------
 |  Function CBuffCreate()
 |
 |  Purpose:     Create a circular buffer.
 |
 |  Returns:     The function returns a pointer to access the circular buffer, or NULL for failure.
 *----------------------------------------------------------------------------*/
c_buff_t *CBuffCreate(size_t capacity);

/*---------------------------------------------------- CBuffDestroy ------------
 |  Function CBuffDestroy() 
 |
 |  Purpose:     Destroys a given circular buffer.   
 |  
 |  Returns:     Void.
 *----------------------------------------------------------------------------*/
void CBuffDestroy(c_buff_t *c_buff);

/*---------------------------------------------------- CBuffRead ---------------
 |  Function CBuffRead()
 |
 |  Purpose:     Copies up to bytes_num bytes from c_buff to 'dest'.    
 |	
 |  Description: CBuffRead reads up to 'bytes_num' bytes from the buffer
 |               pointed to by 'c_buff' and stores them in 'dest'. It returns
 |               the number of bytes actually read.
 |
 |               WARNING: dest size should be at least 'bytes_num' bytes 
 |
 |  Returns:     Returns the number of bytes successfully read.
 *----------------------------------------------------------------------------*/
ssize_t CBuffRead(c_buff_t *c_buff, void *dest, size_t bytes_num);

/*---------------------------------------------------- CBuffWrite --------------
 |  Function CBuffWrite()
 |
 |  Purpose:     Writes data from 'src' to c_buff.
 |	
 |	Description: The function writes at most 'bytes_num' bytes from 'src' memory 
 |               area to a circular buffer pointed to by c_buff. The function
 |               returns the number of bytes successfully written.
 |
 |               WARNING: src size should be at least 'bytes_num' bytes.
 |                
 |  Returns:     Returns the number of bytes successfully written.
 *----------------------------------------------------------------------------*/
ssize_t CBuffWrite(c_buff_t *c_buff, const void *src, size_t bytes_num);

/*---------------------------------------------------- CBuffIsEmpty ------------
 |  Function CBuffIsEmpty()
 |
 |  Purpose:     Checks if the circular buffer is empty.    
 |
 |  Returns:     Non-zero if empty, 0 otherwise.    
 *----------------------------------------------------------------------------*/
int CBuffIsEmpty(const c_buff_t *c_buff);

/*---------------------------------------------------- CBuffFreeSpace ----------
 |  Function CBuffFreeSpace()
 |
 |  Purpose:     Counts the number of free bytes in c_buff for writing.
 |        
 |  Returns:     Returns the number of free bytes for writing.
 *----------------------------------------------------------------------------*/
size_t CBuffFreeSpace(const c_buff_t *c_buff);

/*---------------------------------------------------- CBuffCapacity -----------
 |  Function CBuffCapacity()
 |
 |  Purpose:     Calculates the capacity of the circular buffer, c_buff. 
 |
 |  Complexity: O(1).
 |
 |  Returns:	 Returns the capacity of the circular buffer.     
 *----------------------------------------------------------------------------*/
size_t CBuffCapacity(const c_buff_t *c_buff);

#endif /* __CBUFF_H__ */
