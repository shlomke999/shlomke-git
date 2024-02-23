#ifndef __VECTOR_H_CR4__
#define __VECTOR_H_CR4__
#include <stddef.h>

typedef struct vector_s vector_t;

vector_t *VectorCreate(size_t init_n, size_t elem_size);
void VectorDestroy(vector_t *vector);
int VectorResize(vector_t *vector, size_t new_size);
void VectorPushBack(vector_t *vector,const void *data);
void *VectorAccessIndex(const vector_t *vector, size_t index);
void VectorPopBack(vector_t *vector);
size_t VectorSize(vector_t *vector);


#endif		/* __VECTOR_H_CR4__	*/

