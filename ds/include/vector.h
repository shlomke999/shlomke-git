#ifndef __VECTOR_H_CR4__ 
#define __VECTOR_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */


#define VECTOR_H

#include <stddef.h>

#define GROWTHFACTOR 1.25

#define SHRINKFACTOR (1 / GROWTHFACTOR)

#define EPSILON 0.5

typedef struct vector vector_t;

vector_t *VectorCreate(const size_t elements, const size_t elem_size);

void VectorDestroy(vector_t *vector);

int VectorPushBack(vector_t *vector, const void *data);

int VectorResize(vector_t *vector, size_t new_size);

void *VectorAccessIndex(vector_t *vector, const size_t index);

int VectorPopBack(vector_t *vector);

size_t VectorSize(vector_t *vector);


#endif /* __VECTOR_H_CR4__ */
