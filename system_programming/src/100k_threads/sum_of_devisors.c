#include <stdio.h> /* printf */
#include <pthread.h> /* pthread */
#include <omp.h> /* openMP */

#define BIG_NUM 550000000

int main()
{

    size_t sum_of_divisors = 0, i = 0;

    #pragma omp parallel for /*start multy thread here, and devide iterations to different threads*/
    for(i = 1 ; i <= BIG_NUM; ++i)
    {
        if (0 == BIG_NUM % i)
        {
            sum_of_divisors += i;
        }
    }
    
    printf("Sum of divisors of 550000000 is: = %lu\n", sum_of_divisors);
    return 0;
}

