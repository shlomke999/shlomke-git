#define _POSIX_C_SOURCE 200112L
#include <pthread.h>/*threads*/
#include <stdio.h>  /*printf*/
#include <time.h>   /*time*/
#include <ulimit.h> /*ulimit*/

int status = 0;

typedef struct data data_t;
struct data
{
       pthread_spinlock_t LOCK;
       int buffer[11];
};

void *Producerfunc(void *thread_arg)
{
       int a = 1, b = 10;
       data_t *curr_data = thread_arg;

       while (a <= b)
       {
              pthread_spin_lock(&curr_data->LOCK);
              if (0 == status)
              {
                     curr_data->buffer[a] = a;
                     status = 1;
                     ++a;
              }
              pthread_spin_unlock(&curr_data->LOCK);
       }
       return thread_arg;
}

void *Consumerfunc(void *thread_arg)
{
       int a = 1, b = 10;
       data_t *curr_data = thread_arg;

       while (a <= b)
       {
              pthread_spin_lock(&curr_data->LOCK);
              if (1 == status) /*producer has produced and updated status to 1*/
              {
                     printf("%d\n", curr_data->buffer[a]);
                     status = 0;
                     ++a;
              }
              pthread_spin_unlock(&curr_data->LOCK);
       }
       return thread_arg;
}

int main()
{
       pthread_t producer = 0, consumer = 0;
       void *retval;
       data_t data;

       if (pthread_spin_init(&data.LOCK, PTHREAD_PROCESS_PRIVATE) != 0)
       {
              perror("spin init failed");
       }

       pthread_create(&producer, NULL, Producerfunc, (void *)&data);
       pthread_create(&consumer, NULL, Consumerfunc, (void *)&data);

       pthread_join(producer, &retval);
       pthread_join(consumer, &retval);

       pthread_spin_destroy(&data.LOCK);
       return 0;
}
