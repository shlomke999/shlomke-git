#include <stddef.h> /*size_t*/

#define WORD_SIZE (sizeof(size_t))


/*#############################             
status: approved
reviewer:shany             
description: fills the first n bytes of the memory area 
		     pointed to by s with the constant byte c.             
return value: a pointer to the memory area s.       
special notes:            
#############################*/

void *MemSet(void *s, int c, size_t n)
{
    unsigned char word[WORD_SIZE];
    void *start = s;
    size_t i = 0;
        
    for (; i < WORD_SIZE; ++i)
    {
    	word[i] = (unsigned char)c;
    }
        
    while (n != 0)
    {
		if(n >= WORD_SIZE && (((size_t)s) % WORD_SIZE == 0))
        {
            *((size_t *)s) = *((size_t *)word);
            s = (size_t *)s + 1; 
            n = n - 8;
        }
        else
        {
            *((unsigned char *)s) = (unsigned char)c;
            s = (unsigned char *)s + 1; 
            --n;
        }
    }
    return start;
}


/*#############################             
status: approved
reviewer:shany             
description: copies n bytes from memory area src to memory 
             area dest. The memory areas must not overlap.
return value: pointer to dest.       
special notes:            
#############################*/
void *MemCpy(void *dest, const void *src, size_t n)
{
    unsigned char word[WORD_SIZE];
    size_t i = 0;
    const char *temp = src;
    char *dest_p = dest;
    
    while (n != 0)
    {
    	if (n >= WORD_SIZE && ((((size_t)dest) % WORD_SIZE) == 0))
    	{
    		for (i = 0; i < WORD_SIZE; ++i)
    		{
    			word[i] = *temp;
    			++temp;
    		}
    		(*(size_t *)dest_p) = (*(size_t *)word);
    		*dest_p = (*dest_p + 8);
    		n = n - 8;
    		i = 0;
    	}	
    	else
    	{
    		*dest_p = *temp;
    		++dest_p;
    		++temp;
    		--n;
    	}
    }    
    return dest;	    
}


/*#############################             
status: approved
reviewer:shany             
description: copies n bytes from memory area src to memory area dest. The memory areas may overlap
return value: pointer to dest.       
special notes: thank you shany for your great pseudocode!           
#############################*/
void *MemMove(void *dest, const void *src, size_t n)
{
	const char *src_p = src;
	char *dest_p = dest;
	
	src_p = src_p + n;
	dest_p = dest_p + n;
	
	if (src_p < dest_p)
	{
		while (src_p != src)
		{
			*dest_p = *src_p;
			--dest_p;
			--src_p;
		} 
	}
	else
	{
		MemCpy(&dest, &src, n);
	}	
	
	return dest_p;
}











