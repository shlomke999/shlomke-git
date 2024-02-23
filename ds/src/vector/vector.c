#include <stddef.h> /*size_t*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*memcpy*/
#include <assert.h>

#include "../../include/vector.h"

#define GROWTH_FACTOR 1.25



struct vector 
{
	size_t capacity;
	size_t curr_size;
	size_t element_size;
	char *head;
};

/*
	status: APPROVED
	description:   create a vector stack with 4 fields (3 for size and last for void pointer)
	Reviewer:  nimrod zelzer
	Return:   vector_t type of struct.

*/
vector_t *VectorCreate(size_t element_amount, size_t element_size)
{
	vector_t *new_vector = (vector_t *)malloc(sizeof(vector_t));
	
	if(NULL == new_vector)
	{
		return NULL;
	}
	
	new_vector->curr_size = 0;
	new_vector->element_size = element_size;
	new_vector->head = (char *)malloc(element_size * element_amount);
	
	if(NULL == new_vector->head)
	{
		return NULL;
	}
	new_vector->capacity = (element_size*element_amount);
	
	return new_vector;
}
 
/*
	status: APPROVED
	description:   free the vector.
	Reviewer:  nimrod zelzer
	Return: none
*/

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector->head);
	free(vector->head);
	vector->head = NULL;
	assert(NULL != vector);
	free(vector);
	vector = NULL;
}



/*
	status: APPROVED
	description: add data to vector  and increase size by growth factor of 1.25
	Reviewer: nimrod zelzer 
	Return:  int 0 if fail, 1 for success

*/

 
int VectorPushBack(vector_t *vector, const void *data)
{
	char *temp = NULL;
	assert(NULL != vector);
	if(vector->curr_size * GROWTH_FACTOR > vector->capacity)
	{
		temp = realloc(vector->head, (vector->capacity * GROWTH_FACTOR));

		if(!temp)
		{
			return 0;
		}
		else
		{
			vector->head = temp;
			vector->capacity = (vector->capacity * GROWTH_FACTOR);
		}
	}
 
	memcpy(vector->head + (vector->curr_size * vector->element_size) ,data , vector->element_size);
 	vector->curr_size = vector->curr_size + 1;
 	return 1;
}
 
 
/*
	status: APPROVED
	description: return pointer to the index give from the user, if element doesn't exist, return NULL
	Reviewer:  nimrod zelzer
	Return: void pointer

*/ 
void *VectorAccessIndex(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	if(NULL == vector)
	{
		return NULL;
	}
	
	if(index > (vector->curr_size-1))
	{
		return vector;
	}
	
	return (vector->head + (index * vector->element_size));
}
 


/*
	status: APPROVED
	description: remove an element from the vector stack. 
	Reviewer:  nimrod zelzer
	Return:  0 if failed and 1 if not.

*/
int VectorPopBack(vector_t *vector)
{
	char *temp = NULL;
	assert(NULL != vector);
	if((vector->curr_size * GROWTH_FACTOR) <  vector->capacity)
	{
		
		temp = realloc(vector->head, vector->curr_size * GROWTH_FACTOR);

		if(!temp)
		{
			return 0;
		}
		
		vector->head = temp; 
	}
	vector->capacity = vector->curr_size * GROWTH_FACTOR;
	vector->curr_size = vector->curr_size-1;
	
	return 1;
}


/*
	status:  APPROVED
	description:  return the current number of elements
	Reviewer:  nimrod zelzer
	Return:  size_t number represent number of elements

*/
size_t VectorSize(vector_t *vector)
{
	assert(NULL != vector);
	return  vector->curr_size;
}




/*
	status:  APPROVED
	description: reallocating new memory size to the head. 
	Reviewer:  nimrod zelzer
	Return: 1 - fail, 0 - success.

*/
int VectorRealloc(vector_t  *vector, size_t new_size)
{
	void *temp = NULL;
	assert(NULL != vector);
	temp = realloc(vector->head, new_size);
	if (NULL == temp) 
	{
		return 1;
	}
	
	vector->head = temp;
	temp = NULL;
	
	return 0;
}

