#include <stddef.h> /* size_t */
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/

#include "../ds/include/slist.h"

typedef struct node slist_node_t;


/*approved by shany*/
slist_iter_t IsLoop(slist_t *list)
{
	slist_iter_t next_node = SListStart(list);
	slist_iter_t curr_node = SListStart(list);
	while (NULL != next_node)
	{
		while (curr_node != SListNext(next_node) && curr_node != next_node)
		{
			curr_node = SListNext(curr_node);
		}
		if (curr_node == SListNext(next_node))
		{
			return next_node;
		}
		next_node = SListNext(next_node);
		curr_node = SListStart(list);
	}
	return NULL;
}


int OpenLoop(slist_t *list, slist_iter_t node)
{
	node->next = NULL;
	list->tail = node;
	return 0;
}



int main()
{
	int i = 0;
	int arr[10] = {1, 3, 15, 90, -14, 56, 13, 0, 76, 7};
	slist_t *list = SListCreate();
	slist_iter_t trouble, tail = SListEnd(list);/*making a loop in the list*/
	for (i = 0; i < 10; ++i)
	{
		SListInsertBefore(tail, &arr[i]);
		tail = SListEnd(list);   
	}
	((slist_node_t *)SListEnd(list))->next = (slist_node_t *)SListStart(list);
	
	trouble = IsLoop(list);
	printf("check if slist contain a loop: \n\n\n");
	if (NULL != trouble)
	{
		printf("found a loop! \n\n\n");
		i = OpenLoop(list, trouble);
	}
	
	if (NULL == IsLoop(list))
	{
		printf("loopnessed fixed!\n");
	}
	
	SListDestroy(list);
	return i;
}












































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


/* 
   approved - nimrod.
 * Description - Terminates the list gracefully.
 * Arguments - list - the list to be freed.
 * Return - Nothing.
 * Notes - If list not valid - undefined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
*/
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


/* 
   approved - nimrod.
 * Description - Inserts new data before the given iterator.
   SPECIAL NOTE: iterator invalidation is a side effect of this function execution.
 * Arguments - to_insert - iterator to insert before ,data - the data to be inserted.
 * Return - the inserted slist_iter_t.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
*/
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


/* 
   approved - nimrod.
 * Description - Deletes the node in place of the given iterator ,if the given iterator points to tail
   undefined behavior.
   SPECIAL NOTE: iterator invalidation is a side effect of this function execution.
 * Arguments - to_remove - iterator to remove
 * Return - the new iterator in the place of the given iterator. if you delete the last node it will return
   iterator to tail.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
*/
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


/*
   approved - nimrod.
 * Description - The function returns the first element of the list. 
 * 		 if the list is empty we return an iterator to tail
 * Arguments - list - list
 * Return - the first element of the list.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
*/
slist_iter_t SListStart(const slist_t *list)
{
	return list->head;
}


/*
   approved - nimrod.
 * Description - The function returns the last element of the list - an invalid iterator.
 * Arguments - list - list
 * Return - the last element of the list.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
*/
slist_iter_t SListEnd(const slist_t *list)
{
	return list->tail;
}


/* 
   approved - nimrod.
 * Description - The function returns data in the given iterator.
 * Arguments - element - the iterator to the requested data.
 * Return - the data in the given iterator.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
*/
void *SListGetData(slist_const_iter_t element)
{
	return (void *)element->data;
}


/* 
   approved - nimrod.
 * Description - The function writes over the data in the given iterator with the given data.
 * Arguments - element - the iterator to the data write operation , data - to be written.
 * Return - nothing.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void SListSetData(slist_iter_t elem, const void *data)
{
	elem->data = (void *)data;
}


/* 
   approved - nimrod.
 * Description - The function return the iterator for next element to the given iterator.
    if user gives last iterator will return tail;
 * Arguments - element - the iterator before the requested iterator.
 * Return - slist_iter_t - the next iterator.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
slist_iter_t SListNext(slist_const_iter_t element)
{
	return element->next;
}


/* 
   approved - nimrod.
 * Description - counts the number of elements currently in the list.
 * Arguments - slist_t - the list pointer.
 * Return - size_t - the size of the list.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
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


/* 
   approved - nimrod.
 * Description - compares the given iterators.
 * Arguments - elem1 - iterator to be compared ,elem2 - iterator to be compared.
 * Return - returns 1 if equal,0 otherwise.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
*/
int SListIterIsEqual(slist_const_iter_t elem1, slist_const_iter_t elem2)
{
	return ((elem1 == elem2) ? 1 : 0); 
}


/* 
   approved - nimrod.
 * Description - activates the CompareFunc pointer on each node in the iterator range with the given param.
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range CompareFunc the function to compare
   with ,param - a param to send as argument to the CompareFunc .
   NOTE: from inclusive to exclusive
 * Return - iterator to the matching node or "to iterator" if not found.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
*/
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


/* 
   approved - nimrod.
 * Description - activates the ActionFunc pointer on each node in the iterator range with the given param or
   ActionFunc fails which ever comes first.
   NOTE: from inclusive to exclusive
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range ActionFunc the function to activate
   ,param - a param to send as argument to the ActionFunc .
 * Return - 0 for success or non-zero for corresponding failure from ActionFunc.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
*/
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
