#include <pthread.h>/*threads*/
#include <stdio.h>  /*printf*/
#include <time.h>   /*time*/
#include <unistd.h> /*sleep*/
#include <ulimit.h> /*ulimit*/

#include "../../include/100k_threads.h"

#define SIZE (4)/*optimal number of threads*/
#define RANGE (1000)
#define BIG_NUM 4000

int arr[SIZE];
int i_g = SIZE - 1;

/*thread_function for ex 1 - 3*/
void *thread_function1(void *thread_arg)
{
       arr[(int)thread_arg] = (int)thread_arg;
       return NULL;
}

/*thread_function for ex 4*/
void *thread_function2(void *thread_arg)
{
       int sum_of_divisors = 0;
       int range = (int)thread_arg;
       int j = (range - RANGE) + 1;
       for (; j <= range; ++j)
       {
              if (0 == BIG_NUM % j)
              {
                     sum_of_divisors += j;
              }
       }
       return (void *)sum_of_divisors;
}

void CheckArr()
{
       int i = SIZE - 1;
       while (i)
       {
              if (arr[i] != i)
              {
                     printf("index not correct\n");
              }
              --i;
       }
}
/* Status :approved.
 * Reviewer :nevo.
 * Description : ex 1 -3
 * Return :void
 */
void Threads100K()
{
       int j = SIZE - 1;
       void *retval;
       pthread_t thread;
       while (j)
       {
              /*pthread_attr_t attr;
              pthread_attr_init (&attr);
              pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
              pthread_attr_destroy (&attr);
              */
              while (pthread_create(&thread, NULL, &thread_function1, (void *)j) != 0)
                     ; /*keep running till sucess*/
              /*pthread_detach(thread);*/
              --j;
       }
       pthread_join(thread, &retval);
       sleep(5);
       CheckArr();
}

/* Status :approved.
 * Reviewer :nevo.
 * Description : devide payload to threads, every thread calculates sum of devisors for range of numbers.
 * Return :void
 */
void ex4()
{
       int j = 1, total_sum = 0;
       void *retval;
       pthread_t thread[SIZE];
       while (j <= SIZE)
       {
              if(pthread_create(&thread[j], NULL, &thread_function2, (void *)(j * RANGE)))
              {
                     printf("pthread_create error");
              }
              ++j;
       }
       --j;
       while (j > 0)
       {
              pthread_join(thread[j], &retval);/*collect the return value of each thread's function*/
              total_sum += (int)retval;
              --j;
       }
       printf("%d\n", total_sum);
}






