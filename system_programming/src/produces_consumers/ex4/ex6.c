#include <stdio.h>     /*printf*/
#include <pthread.h>   /*pthread funcs*/
#include <semaphore.h> /*semaphore*/

#define MAX_CONSUMERS 3
#define ITERATIONS 10

typedef struct list
{
       pthread_mutex_t mutex;
       sem_t semaphore;
       pthread_cond_t consumers_can_read;
       int sum;
} list_t;

void *producerfunc(void *thread_arg)
{
       list_t *arg = thread_arg;
       int i = 0, j = 0;

       while (i < ITERATIONS)
       {

              for (j = 0; j < MAX_CONSUMERS; ++j)
              {

                     sem_wait(&arg->semaphore); /*set semaphore to 0*/
              }
              pthread_mutex_lock(&arg->mutex);
              arg->sum = i + 5; /*produce value*/
              pthread_cond_broadcast(&arg->consumers_can_read);
              pthread_mutex_unlock(&arg->mutex);

              ++i;
       }

       return NULL;
}

void *consumerfunc(void *thread_arg)
{
       list_t *arg = thread_arg;
       int i = 0;
       while (i < ITERATIONS)
       {
              pthread_mutex_lock(&arg->mutex);
              sem_post(&arg->semaphore);
              pthread_cond_wait(&arg->consumers_can_read, &arg->mutex);
              pthread_mutex_unlock(&arg->mutex);

              printf("consumer %d: consumed %d\n", i, arg->sum);
              ++i;
       }

       return NULL;
}

int main()
{
       pthread_t producer, consumers[MAX_CONSUMERS];
       long i = 0;
       list_t arg;

       pthread_mutex_init(&arg.mutex, NULL);
       pthread_cond_init(&arg.consumers_can_read, NULL);
       sem_init(&arg.semaphore, 0, 0);

       for (i = 0; i < MAX_CONSUMERS; ++i)
       {
              pthread_create(&consumers[i], NULL, consumerfunc, (void *)&arg);
       }
       pthread_create(&producer, NULL, producerfunc, (void *)&arg);

       /*join threads */
       for (i = 0; i < MAX_CONSUMERS; ++i)
       {
              pthread_join(consumers[i], NULL);
       }
       pthread_join(producer, NULL);

       pthread_mutex_destroy(&arg.mutex);
       sem_destroy(&arg.semaphore);
       pthread_cond_destroy(&arg.consumers_can_read);
       return 0;
}
