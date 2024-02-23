#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "../../../ds/include/slist.h"

#define MAX_PRODUCERS 3
#define MAX_CONSUMERS 3
#define MAX 4


typedef struct list list_t;
struct list
{
       pthread_mutex_t mutex;
       slist_t *my_list; /*defined in main*/
       slist_iter_t new_node;
};

void *producer(void *thread_arg)
{
       int i = 0;
       list_t *arg = thread_arg;
       while (i < MAX)
       {
              pthread_mutex_lock(&arg->mutex);
              arg->my_list->head = SListStart(arg->my_list);
              arg->new_node = SListInsertBefore(arg->my_list->head, (void *)i);
              printf("Producer %d: produced %d\n", i, (int)i);
              ++i;
              pthread_mutex_unlock(&arg->mutex);
       }

       return NULL;
}

void *consumer(void *thread_arg)
{
       int data = 0, i = 0;
       list_t *arg = thread_arg;
       while (i < MAX)
       {
              pthread_mutex_lock(&arg->mutex);
              if (SlistIsEmpty(arg->my_list) == 0)
              {
                     data = (int)arg->new_node->data;
                     SListDelete(arg->new_node);
                     printf("Consumer %d: consumed %d\n", i, data);
              }
              ++i;
              pthread_mutex_unlock(&arg->mutex);
       }

       return NULL;
}

int main()
{
       pthread_t producers[MAX_PRODUCERS], consumers[MAX_CONSUMERS];
       long i = 0;
       list_t data;

       data.my_list = SListCreate();

       pthread_mutex_init(&data.mutex, NULL);

       for (i = 0; i < MAX_PRODUCERS; ++i)
       {
              pthread_create(&producers[i], NULL, producer, (void *)&data);
              pthread_create(&consumers[i], NULL, consumer, (void *)&data);
       }

       /*join threads */
       for (i = 0; i < MAX_PRODUCERS; ++i)
       {
              pthread_join(producers[i], NULL);
              pthread_join(consumers[i], NULL);
       }

       pthread_mutex_destroy(&data.mutex);
       SListDestroy(data.my_list);
       return 0;
}

slist_t *SListCreate()
{
       slist_t *list = (slist_t *)malloc(sizeof(slist_t));
       if (NULL == list)
       {
              return NULL;
       }
       list->head = (struct node *)malloc(sizeof(struct node));
       if (NULL == list->head)
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
       while (list->head->next)
       {
              SListDelete(list->head);
       }
       free(list->head);
       free(list);
}

slist_iter_t SListInsertBefore(slist_iter_t to_insert, const void *new_data)
{
       struct node *new_node = (struct node *)malloc(sizeof(struct node));
       void *prev_list_item_data = to_insert->data;
       slist_iter_t prev_list_item_next = to_insert->next;

       if (NULL == new_node)
       {
              return NULL;
       }

       if (NULL == to_insert->next)
       {
              ((slist_t *)to_insert->data)->tail = (slist_iter_t)new_node;
       }
       to_insert->data = (void *)new_data;
       to_insert->next = new_node;
       new_node->data = prev_list_item_data;
       new_node->next = prev_list_item_next;

       return to_insert;
}

slist_iter_t SListStart(const slist_t *list)
{
       return list->head;
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

int SlistIsEmpty(const slist_t *list)
{
       return list->head->next ? 0 : 1;
}
