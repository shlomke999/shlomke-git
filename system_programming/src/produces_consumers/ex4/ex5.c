#include <stdio.h>/*printf*/
#include <pthread.h>/*pthread funcs*/
#include <semaphore.h>/*semaphore*/
#include <assert.h>    /* assert */
#include <stdlib.h>    /* malloc */
#include <string.h>    /* memcpy */
#include <sys/types.h> /* ssite_t*/
#include <stddef.h>    /*offsetof*/

#include "cbuff_read_write_index.h" /*queue*/

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX_PRODUCERS 3
#define MAX_CONSUMERS 3
#define NBYTES 8
#define TOTAL_BYTES 600

struct c_buff
{
       size_t capacity;     /* Initialized and never changes - can be read from multiple thread asynchronously */
       size_t write_offset; /* Starting position for write operations.          */
       size_t read_offset;  /* Starting position for read operations.          */
       char buffer[1];
};

typedef struct list
{
       pthread_mutex_t prod_mutex;
       pthread_mutex_t con_mutex;
       sem_t read_semaphore;
       sem_t write_semaphore;
       c_buff_t *log_buffer;
       size_t arr[25];
} list_t;

void *producer(void *thread_arg)
{
       int i = 0;
       list_t *arg = thread_arg;

       while (i < 4)
       {
              sem_wait(&arg->write_semaphore); /*decrease write semaphore*/

              pthread_mutex_lock(&arg->prod_mutex);
              if (NBYTES != CBuffWrite(arg->log_buffer, &arg->arr[i], NBYTES))
              {
                     printf("log write failed");
              }
              printf("producer %d: produced %ld\n",i, arg->arr[i]);
              ++i;
              sem_post(&arg->read_semaphore); /*read semaphore*/
              pthread_mutex_unlock(&arg->prod_mutex);
       }

       return NULL;
}

void *consumer(void *thread_arg)
{
       int i = 0;
       size_t k = 0;
       list_t *arg = thread_arg;

       while (i < 4)
       {
              sem_wait(&arg->read_semaphore);

              pthread_mutex_lock(&arg->con_mutex);
              CBuffRead(arg->log_buffer, &k, NBYTES);
              k *= 5;
              printf("consumer %d: multiply by 5 is %ld\n ", i, k);
              ++i;
              sem_post(&arg->write_semaphore); /*producer can write again on the cell we read*/
              pthread_mutex_unlock(&arg->con_mutex);
       }

       return NULL;
}

int main()
{
       pthread_t producers[MAX_PRODUCERS], consumers[MAX_CONSUMERS];
       long i = 0;
       list_t arg;
       arg.log_buffer = CBuffCreate(TOTAL_BYTES);
       for (i = 0; i < 25; ++i)/*initilize struct arr*/
       {
              arg.arr[i] = i;
       }
       i = 0;

       pthread_mutex_init(&arg.prod_mutex, NULL);
       pthread_mutex_init(&arg.con_mutex, NULL);
       sem_init(&arg.read_semaphore, 0, 0);
       sem_init(&arg.write_semaphore, 0, 25); /*to limit producer writes to 3 times*/

       for (i = 0; i < MAX_PRODUCERS; ++i)
       {
              pthread_create(&producers[i], NULL, producer, (void *)&arg);
              pthread_create(&consumers[i], NULL, consumer, (void *)&arg);
       }

       /*join threads */
       for (i = 0; i < MAX_PRODUCERS; ++i)
       {
              pthread_join(producers[i], NULL);
              pthread_join(consumers[i], NULL);
       }

       pthread_mutex_destroy(&arg.prod_mutex);
       pthread_mutex_destroy(&arg.con_mutex);
       sem_destroy(&arg.read_semaphore);
       sem_destroy(&arg.write_semaphore);
       CBuffDestroy(arg.log_buffer);
       return 0;
}

/* In this DS we assume Read and Write sizes are guarded by
   external sempahores using producer / consumer pattern.
   Therefore it uses separate read and write offsets, and maintains no
   size member.*/

void CBuffPrintDebug(const c_buff_t *c_buff);

c_buff_t *CBuffCreate(size_t capacity)
{
       c_buff_t *c_buff = NULL;
       size_t unused_mem = sizeof(c_buff_t) - offsetof(struct c_buff, buffer);
       size_t buffer_size = 0;

       assert(capacity);

       /* Using the padding memory for the buffer size to allocate - flexible array */
       if (capacity > unused_mem)
       {
              buffer_size = capacity - unused_mem;
       }

       c_buff = (c_buff_t *)malloc(sizeof(c_buff_t) + buffer_size);

       if (c_buff)
       {
              c_buff->capacity = capacity;
              c_buff->write_offset = 0;
              c_buff->read_offset = 0;
       }

       return c_buff;
}

void CBuffDestroy(c_buff_t *c_buff)
{
       assert(c_buff);

       free(c_buff);
       c_buff = NULL;
}

ssize_t CBuffRead(c_buff_t *c_buff, void *dest, size_t bytes_num)
{
       size_t bytes_to_read = 0;
       size_t bytes_to_copy = 0;

       assert(c_buff);
       assert(dest);

       bytes_to_read = bytes_num;

       /* Copy from the right side of buffer. */
       bytes_to_copy = MIN(bytes_to_read, c_buff->capacity - c_buff->read_offset);
       memcpy(dest, &c_buff->buffer[c_buff->read_offset], bytes_to_copy);
       dest = (char *)dest + bytes_to_copy;

       /* Copy from the left side of buffer. */
       if (bytes_to_read > bytes_to_copy)
       {
              bytes_to_copy = bytes_to_read - bytes_to_copy;
              memcpy(dest, &c_buff->buffer[0], bytes_to_copy);
       }

       /* Update read offset: */
       c_buff->read_offset = (c_buff->read_offset + bytes_to_read) %
                             c_buff->capacity;

       return bytes_to_read;
}

ssize_t CBuffWrite(c_buff_t *c_buff, const void *src, size_t bytes_num)
{
       size_t bytes_to_write = 0;
       size_t bytes_to_copy = 0;

       assert(c_buff);
       assert(src);

       bytes_to_write = bytes_num;

       /* Copy into the right side of buffer. */
       bytes_to_copy = MIN(bytes_to_write, c_buff->capacity - c_buff->write_offset);
       memcpy(&c_buff->buffer[c_buff->write_offset], src, bytes_to_copy);
       src = (char *)src + bytes_to_copy;

       /* Copy into the left side of buffer. */
       if (bytes_to_write > bytes_to_copy)
       {
              bytes_to_copy = bytes_to_write - bytes_to_copy;
              memcpy(&c_buff->buffer[0], src, bytes_to_copy);
       }

       /* Update write offset: */
       c_buff->write_offset = (c_buff->write_offset + bytes_to_write) %
                              c_buff->capacity;

       return bytes_to_write;
}

int CBuffIsEmpty(const c_buff_t *c_buff)
{
       assert(c_buff);

       /* Also here, we are counting on external semaphores usage upon
          Read / Write calls. If used correctly, The following IsEmpty() is
          now valid (non thread-safe of course):*/
       return (c_buff->read_offset == c_buff->write_offset);
}

size_t CBuffFreeSpace(const c_buff_t *c_buff)
{
       assert(c_buff);

       /* Also here, we are counting on external semaphores usage upon
          Read / Write calls. If used correctly, The following FreeSpace() is
          now valid (non thread-safe of course):*/
       return (c_buff->write_offset > c_buff->read_offset) ? (c_buff->write_offset > c_buff->read_offset) : (c_buff->write_offset - 0) + (c_buff->capacity - c_buff->read_offset);
}

size_t CBuffCapacity(const c_buff_t *c_buff)
{
       return c_buff->capacity;
}
