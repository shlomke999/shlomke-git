#include <stddef.h> /* size_t */
#include <stdlib.h>
#include <assert.h>/*assert*/

typedef struct node
{
	void *data;
	struct node *next;
}slist_node_t, *slist_iter_t;

typedef struct slist
{
	slist_node_t *head;
	slist_node_t *tail;
}slist_t;

typedef int (*action_t)(void *data ,void *param);
typedef int (*is_match_t)(const void *data, void *param);
int SListForEach(slist_iter_t from, slist_iter_t to, action_t ActionFunc, void *param);
slist_node_t *SListDelete(slist_iter_t to_remove);
slist_node_t *SListNext(slist_iter_t element);

slist_node_t *SListDelete(slist_iter_t to_remove);
slist_node_t *SListInsertBefore(slist_iter_t to_insert, const void *data);
slist_t *SListCreate(void);
void SListDestroy(slist_t *list);
size_t SListSize(const slist_t *list);
slist_node_t *SListNext(slist_iter_t element);
slist_node_t *SListStart(const slist_t *list);
slist_node_t *SListEnd(const slist_t *list);


/*approved by ran*/
slist_iter_t FindIntersectionInSLL(slist_t *list1, slist_t *list2)
{
    slist_iter_t curr1 = list1->head, curr2 = list2->head;
    if (curr1 == curr2)
    {
        return curr2;
    }
    if (NULL == curr1 || NULL == curr2)
    {
        return NULL;
    }
    while (NULL != curr1->next)
    {
        curr2 = list2->head;
        while (NULL != curr2->next)/*traverse all the list for intersections*/
        {
            if  (curr2->next == curr1->next)
            {
                return curr2;
            }
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }
    return NULL;
}

void SeparateIntersection(slist_t *list, slist_node_t *inter)
{
	slist_node_t *node = list->head;
	if (list->head == inter)
	{
		list->head = SListNext(inter);
	}
	else
	{
		while (node->next != inter)
		{
			node = SListNext(node);
		}
		SListInsertBefore(node, node->data);
		list->tail = SListNext(node);
		list->tail->data = &list;
		list->tail->next = NULL;
	}
}


int main()
{
	slist_t *list1 = SListCreate();
	slist_t *list2 = SListCreate();
	slist_node_t *node1 = SListEnd(list1);
	slist_node_t *node2 = SListEnd(list2);
	int n[2] = {1, 2};
	slist_node_t *inter;
	node1 = SListInsertBefore(node1, &n[0]);
	node2 = SListInsertBefore(node2, &n[0]);
	node1 = SListInsertBefore(node1, &n[1]);
	node2 = SListInsertBefore(node2, &n[1]);

	inter = SListEnd(list1);
	inter->next = SListStart(list2);
	list1->tail = SListEnd(list2);

	inter = FindIntersectionInSLL(list1, list2);
	if (NULL != inter)
	{
		SeparateIntersection(list1, inter);
	}
	SListDestroy(list1);
	SListDestroy(list2);
	return 0;
}





























slist_t *SListCreate(void)
{
	slist_t *new_list = (slist_t *)malloc(sizeof(slist_t));
	slist_node_t *dummy = NULL;
	if (NULL == new_list)
	{
		return NULL;
	}
	dummy = (slist_node_t *)malloc(sizeof(slist_node_t));
	if (NULL == dummy)
	{
		free(new_list);
		new_list = NULL;
		return NULL;
	}
	
	dummy->data = (void *)new_list;
	dummy->next = NULL;
	
	new_list->head = dummy;
	new_list->tail = dummy;

	dummy = NULL;
	return new_list;
}


void SListDestroy(slist_t *list)
{
	struct node *this = list->head, *next = NULL;
	assert(list);
	
	while(NULL != this)
	{
		next = this->next;
		this->data = NULL;
		free(this);
		this = next;
	}
	next = NULL;
	free(list);
	list = NULL;
}

slist_node_t *SListInsertBefore(slist_iter_t to_insert, const void *data)
{
	slist_node_t *node = (slist_node_t *)malloc(sizeof(slist_node_t));
	assert(to_insert);
	if (NULL == node)
	{
		return NULL;
	}
	
	/* node recieves to_insert data and pointer
		to insert recieves new data and points to node */
		
	node->data = to_insert->data;
	node->next = to_insert->next;
	
	to_insert->data = (void *)data;
	to_insert->next = node;
	
	if (NULL == node->next)
	{
		/* update new tail iterator to list */
		((slist_t *)node->data)->tail = node;
	}
	
	node = NULL;
	
	return to_insert;
}
slist_node_t *SListDelete(slist_iter_t to_remove)
{
	slist_node_t *keep_address = to_remove->next;
	assert(to_remove);
	if (NULL == to_remove->next)
	{
		return ((slist_t *)to_remove->data)->tail;
	}
	
	
	to_remove->data = to_remove->next->data;
	to_remove->next = to_remove->next->next;
	
	free(keep_address);
	keep_address = NULL;
	return to_remove;
}
int SListForEach(slist_iter_t from, slist_iter_t to, action_t ActionFunc, void *param)
{
	int boolean = 0;
	assert(from);
	assert(to);
	while ((size_t)to != (size_t)from)
	{
		boolean += ActionFunc(from->data, param);
		from = SListNext(from);
	}
	return boolean;
}
slist_node_t *SListStart(const slist_t *list)
{
	assert(list);
	return list->head;
}
slist_node_t *SListEnd(const slist_t *list)
{
	assert(list);
	return list->tail;
}
slist_node_t *SListNext(slist_iter_t element)
{
	if (NULL == element->next)
	{
		return (slist_iter_t)element;
	}
	return element->next;
}



/* helper to SListSize func */
static int Counter(void *data, void *param)
{
	*(int *)param += 1;
	return 0;
}
size_t SListSize(const slist_t *list)
{
	/* NEED TO USE FOREACH */
	size_t count = 0;
	assert(list);
	SListForEach(list->head, list->tail, Counter, (void *)&count);
	return count;
}



