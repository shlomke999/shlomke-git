#include <stddef.h> /* Used for size_t type */
#include <assert.h> /*assert*/

#include "../../include/hash_table.h"



struct hash_table
{
    size_t index_amount;
    hashfunc_t hashFunc;
    cmpfunc_t hashcmp;      /*string compare function*/
    slist_t **bucket_list;
};


/*
 * status: approved.
 * reviewer: elad.
 * Description - HashCreate creates a hash table.
 * Arguments - index_capacity - maximum amount of indexes in the table
 *             HashFunc - hash function for the hash table 
 *             and hashcmp - compre function for data.
 * Return - A pointer to a new hash table
 * Time Complexity - O(1)
 * Space Complexity - O(n)
 */
hash_table_t *HashCreate(const size_t index_amount, const hashfunc_t HashFunc, 
                    const cmpfunc_t hashcmp)
{
	size_t i = 0, j = 0;
	hash_table_t *table = (hash_table_t *)malloc(sizeof(hash_table_t) + index_amount * sizeof(slist_t *));
	if (NULL == table)
	{
		return NULL;
	}
	table->hashFunc = HashFunc;
	table->hashcmp = hashcmp;
	table->index_amount = index_amount;
	table->bucket_list = (slist_t **)((char *)table + sizeof(hash_table_t));
	
	for (i = 0; i < index_amount; ++i)
	{
		table->bucket_list[i] = SListCreate();
		if (NULL == (table->bucket_list[i]))
		{
			j = 0;
			while(j < i)
			{
				SListDestroy(table->bucket_list[j]);
				++j;
			}
			free(table);
			table = NULL;
			return NULL;
		}
	}
	return table;
}


/*
 * status: approved.
 * reviewer: elad.
 * Description - HashDestroy destroys a given hash table
 * Arguments - table - pointer to hash table
 * Return - void.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
void HashDestroy(hash_table_t *table)
{
	size_t i = 0;
	for (i = 0; i < table->index_amount; ++i)
	{
		 SListDestroy(table->bucket_list[i]); 
	}
	free(table);
	table = NULL;
}


/*
 * status: approved.
 * reviewer: elad.
 * Description - ForEach applies ActionFunc with param on each element in the table.
 * Arguments - table - pointer to hash table
 *             ActionFunc - pointer to action function
 *             param - pointer to action func parameter
 * Return - 0 upon success, -1 upon failure.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
int HashForEach(hash_table_t *table, int (*ActionFunc)(void *data, void *param), void *param)
{
	size_t i = 0, result = 0;
	
	for (i = 0; i < table->index_amount; ++i)
	{
		result = SListForEach(SListStart(table->bucket_list[i]), SListEnd(table->bucket_list[i]), ActionFunc, param);
	}
	return result;
}


/*
 * status: approved.
 * reviewer: elad.
 * Description - HashSize computes the number of elements in the hash table.
 * Arguments - table - pointer to hash table
 * Return - the number of elements in the table.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
size_t HashSize(const hash_table_t *table)
{
	size_t i = 0, result = 0;
	
	for (i = 0; i < table->index_amount; ++i)	
	{
		result += SListSize(table->bucket_list[i]);
	}	
	return result;	
}


/*
 * status: approved.
 * reviewer: elad.
 * Description - HashFind find the element correlated with the given data.
 * Arguments - table - pointer to hash table
 *             data - key value to find.
 * Return - void pointer to the value correlated with the given key.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
void *HashFind(const hash_table_t *table, const void *data)
{
	slist_iter_t match = NULL;
	size_t hash_index = table->hashFunc(data) % table->index_amount;   /*adjust the hash to our index amount so that we get a valid key*/
	
	match = SListFind(SListStart(table->bucket_list[hash_index]), SListEnd(table->bucket_list[hash_index]), (is_match_t)table->hashcmp, (void *)data);	
	return 0 != match ? SListGetData(match) : NULL;
}


/*
 * status: approved.
 * reviewer: elad.
 * Description - HashInsert inserts a new value to hash table
 * Arguments - table - pointer to hash table, data - to insert.
 * Return - 0 upon success, 1 upon failier.
 * Time Complexity - O(1)
 * Space Complexity - O(1)
 */
int HashInsert(hash_table_t *table, const void *data)
{
	slist_iter_t result_node = NULL;
	size_t hash_index = table->hashFunc(data) % table->index_amount;
	
	result_node = SListInsertBefore(SListStart(table->bucket_list[hash_index]), data);
	if (NULL == result_node)
	{
		return 1;
	}	
	return 0;
}


/*
 * status: approved.
 * reviewer: elad.
 * Description - HashRemove removes the element correlated with the given key.
 * Arguments - table - pointer to hash table
 *             Data - node to remove (will use as parameter in hash function)
 * Return - 0 upon success, 1 upon failiur.
 * Time Complexity - O(1)
 * Space Complexity - O(1)
 */
int HashRemove(hash_table_t *table, const void *data)
{
	size_t hash_index = table->hashFunc(data) % table->index_amount;
	slist_iter_t match = SListFind(SListStart(table->bucket_list[hash_index]), 
	SListEnd(table->bucket_list[hash_index]), (is_match_t)table->hashcmp, (void *)data);	
		
	SListDelete(match);
	return 0 == match ? 0 : 1;
}


/*
 * status: approved.
 * reviewer: elad.
 * Description - HashIsEmpty checks if hash table is empty
 * Arguments - table - pointer to hash table
 * Return - 1 if empty, 0 if not.
 * Time Complexity - O(n)
 * Space Complexity - O(1)
 */
int HashIsEmpty(const hash_table_t *table)
{
	size_t i = 0, size = 0;
	for (i = 0; i < table->index_amount; ++i)
	{
		size = SListSize(table->bucket_list[i]);
		if (0 != size)
		{
			return 0;
		}
	}
	return 1;
}






















					/*****   linked list functions   *****/
slist_t *SListCreate()
{
  	slist_t *list = (slist_t*)malloc(sizeof(slist_t));
  	if(NULL == list) 
  	{ 	
  		return NULL;
  	}
  	list->head = (struct node*)malloc(sizeof(struct node));
  	if(NULL == list->head)
  	{
    		free(list);
    		return NULL;
  	}
  	list->head->data = list;
  	list->head->next = NULL;
  	list->tail = list->head;
  	return list;
}


void SListDestroy(slist_t *list)
{
  	assert(list);
	while(list->head->next)
  	{
    		SListDelete(list->head);
  	}
  	free(list->head);
  	free(list);
}


slist_iter_t SListInsertBefore(slist_iter_t to_insert, const void *new_data)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    void *prev_list_item_data = to_insert->data;
   	slist_iter_t prev_list_item_next = to_insert->next;
   	
   	if(NULL == new_node)
   	{
   		return NULL;
   	}
   	
   	if(NULL == to_insert->next)
  	{
    	((slist_t *)to_insert->data)->tail = (slist_iter_t)new_node;
  	}
  	to_insert->data = (void*)new_data;
	to_insert->next = new_node;
	new_node->data = prev_list_item_data;
	new_node->next = prev_list_item_next;
    	
   	return to_insert;
}


slist_iter_t SListDelete(slist_iter_t to_remove)
{
	slist_node_t *ptr = to_remove->next;
	to_remove->data = to_remove->next->data;
	if (to_remove->next->next == NULL)		
	{
		((slist_t *)to_remove->data)->tail = to_remove;
	}
	to_remove->next = to_remove->next->next;
	free(ptr);
	return to_remove;
}


slist_iter_t SListStart(const slist_t *list)
{
	return list->head;
}


slist_iter_t SListEnd(const slist_t *list)
{
	return list->tail;
}


void *SListGetData(slist_const_iter_t element)
{
	return (void *)element->data;
}


void SListSetData(slist_iter_t elem, const void *data)
{
	elem->data = (void *)data;
}


slist_iter_t SListNext(slist_const_iter_t element)
{
	return element->next;
}


size_t SListSize(const slist_t *list)
{
	size_t i = 0;
	slist_iter_t start = SListStart(list);
	
	while (NULL != start->next)
	{
		start = SListNext(start);
		++i;
	}
	return i;
}


int SListIterIsEqual(slist_const_iter_t elem1, slist_const_iter_t elem2)
{
	return ((elem1 == elem2) ? 1 : 0); 
}


slist_iter_t SListFind(slist_const_iter_t from, slist_const_iter_t to, is_match_t CompareFunc, void *param)
{
	slist_iter_t from_iter = (slist_iter_t)from;	
	 
	while (from_iter != to)
	{
		if (0 == CompareFunc(SListGetData(from_iter), param))
		{
			return from_iter;
		}
		from_iter = SListNext(from_iter);
	}
	return from_iter;
}


int SListForEach(slist_iter_t from, slist_const_iter_t to, action_t ActionFunc, void *param)
{
	slist_iter_t from_iter = (slist_iter_t)from;	
	int result = 0;
	
	while (from_iter != to && result == 0)
	{
		result = ActionFunc(SListGetData(from_iter), param);
		from_iter = SListNext(from_iter);
	}
	return result;
}

