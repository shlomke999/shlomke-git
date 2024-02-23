#ifndef __HASHTABLE_H_CR4__ 
#define __HASHTABLE_H_CR4__ 

#include <stddef.h>    /* Used for size_t type */
#include <stdlib.h> /*malloc*/
#include "slist.h"


typedef struct hash_table hash_table_t;

typedef int (*cmpfunc_t)(const void *data, void *param);
typedef size_t (*hashfunc_t)(const void *data);

/*
 * Description - HashCreate creates a hash table.
 * Arguments - index_capacity - maximum amount of indexes in the table
 *             HashFunc - hash function for the hash table 
 *             and hashcmp - compre function for data.
 * Return - A pointer to a new hash table, return NULL on fail.
 * Time Complexity - O(1)
 * Space Complexity - O(n)
 */
hash_table_t *HashCreate(const size_t index_amount, const hashfunc_t HashFunc, 
                    const cmpfunc_t CmpFunc);


/*
 * Description - HashDestroy destroys a given hash table
 * Arguments - table - pointer to hash table
 * Return - void.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
void HashDestroy(hash_table_t *table);


/*
 * Description - HashRemove removes the element correlated with the given key.
 * Arguments - table - pointer to hash table
 *             Data - to remove (will use as parameter in 
 *              hash function)
 * Return - 0 upon success, 1 upon failiur.
 * Time Complexity - O(1)
 * Space Complexity - O(1)
 */
int HashRemove(hash_table_t *table, const void *data);


/*
 * Description - HashInsert inserts a new value to hash table
 * Arguments - table - pointer to hash table, data - to insert.
 * Return - 0 upon success, 1 upon failier.
 * Time Complexity - O(1)
 * Space Complexity - O(1)
 */
int HashInsert(hash_table_t *table, const void *data);


/*
 * Description - HashSize computes the number of elements in the hash table.
 * Arguments - table - pointer to hash table
 * Return - the number of elements in the table.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
size_t HashSize(const hash_table_t *table);


/*
 * Description - HashIsEmpty checks if hash table is empty
 * Arguments - table - pointer to hash table
 * Return - 1 if empty, 0 if not.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
int HashIsEmpty(const hash_table_t *table);


/*
 * Description - HashFind find the element correlated with the given data.
 * Arguments - table - pointer to hash table
 *             data - key value to find.
 * Return - void pointer to the value correlated with the given key.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
void *HashFind(const hash_table_t *table, const void *data);


/*
 * Description - HForEach applies ActionFunc with param on each element in the table.
 * Arguments - table - pointer to hash table
 *             ActionFunc - pointer to action function
 *             param - pointer to action func parameter
 * Return - 0 upon success, 1 upon failure.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
int HashForEach(hash_table_t *table, int (void *data, void *param), void *param);

#endif /* __HASHTABLE_H_CR4__ */

