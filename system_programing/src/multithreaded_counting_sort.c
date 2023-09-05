/******************************************************************************
                                        ▄▄▀▀▀▀████▓▓░░  ░
                                     ▄█▓░░   ░▓█▓
                                   ▄█▓░░    ░▓█░
                                  █▓░░░░   ░▓█░
                                ▄█▓░░░    ░░▓█░
        ▄▄▄              ▄▄▄▄█▄█▓▓▀▀▀▓███▄▄▓██▓░ ░
       █░  █         ▄▄▓▓▓▓░░░░░░░░░░░░░░░▓████▄▄                      ▄▄▄▄▄▄▓
      █    ▓█    ▄▄▓▓▓▓░▓░░░   ░░░░░░░░░░░░░░░▓▓▓█▄▄     ▄        ▄▄▓▓▓░░░░█▀
       █  ▓█   ▄█▓░▄██▓░░       ░  ░░░░░░ ░░░░░░▓▓▓▓██▄    ▄   ░▄▓▓▓░░  ░▓█▓
        ▀▀▀  ▄█▓░ ▄▄▄▄▄ ░░           ░░░   ░  ▄▄▄ ░░▓▓▓█▄ ▀▓▀ ░█▓▓░░   ░▓█▓
      ▄▄    ██▓░▄▀  ░░▓█▓░░       ░  ░░      █░  █  ░░░▓▓█▄  ▓█▓▓░░   ░▓▓█░
     █ ▓█  ██▓░▓█     ░▓█▓░░   ░   ░░░      █░  ░▓█   ░░▓▓██▓█▓▓░    ░░▓▓█
      ▀▀  ██▓▓░█▓      ░▓░░   ░ ░            █ ░▓█     ░░░▓███▓░ ░  ░░░▓█▓
   ▄▄  ▄ ██▓▓░ █░  ▄▄▄  ░░     ░    ▄▄▄▄▄     ▀▀▀ ▄  ░  ░░░▓█▓░    ░░░▓▓█
  █ ▓█  ███▓▓░▄█▄▄██▄█▄▄▄░░     ▄▓▓▓░░░ ░▀  ░░░          ░░▓█▓    ░ ░░░▓█ ▀
   ▀▀   ███▓▓▓░░░░░░░  ░▓▓░░         ░     ░▓████▓▓░░░ ░  ░░▓▓  ░   ░░▓▓▓▀
     ▄▓▄ ███▓▓▓░░░░  ▄░▀▄░░░░░░░    ░    ░▓███▓░▀▀▀██▄    ░░░     ░░░▓▓▓ ▄░▀▀▄
      ▀   ▀███▓▓▓▄▄▄ ▀▄▓▀░ ▄▄▄ ░░░░░░ ░░░▓███▓░     ▀██░ ░▓░░░ ░░░░░▓▓▓ █░   ▓█
*******************************************************************************

    Writer: Tal Aharon

    Reviewer: Ishai Zilberman.

    Date: 22.06.2023

*******************************************************************************

                          Description:

  This code implements a multithreaded counting sort algorithm. The main function 
  is MultithreadedCountingSort, which takes an array buffer and its size size as 
  input. It divides the sorting process into multiple threads, each responsible 
  for counting the occurrences of characters in a specific chunk of the array. 
  The counting is done using a shared mutex-protected count array. After all the 
  threads have finished counting, the main thread consolidates the counts and 
  reassembles the sorted array. The code also includes the necessary header files 
  and defines a thread object structure and a counting routine function.

******************************************************************************/
#define _POSIX_SOURCE /* pthreads */
#include <stdlib.h>   /* malloc, free */
#include <pthread.h>
/*
    pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_destroy, 
    pthread_mutex_lock, pthread_mutex_unlock,
*/

#include "multithreaded_counting_sort.h"
/*****************************************************************************/
typedef struct thread_object
{
    uint_t *count;
    unch_t *buffer;
    size_t chunk_size;

} thread_object_t;
/*****************************************************************************/
static pthread_mutex_t mutex;
static void *CountingRoutine(void *);
/*****************************************************************************/
int CountingSort(unch_t *buffer, size_t size)
{
    unch_t min = 'A';
    unch_t max = 'z';
    size_t i = 0, j = 0, k = 0;
    unsigned int *count = NULL;
    count = calloc((int)(max - min) + 1, sizeof(unsigned int));
    if(NULL == count)
    {
        return (MCS_FAILURE);
    }

    for(i = 0; i < size; ++i)
    {
        ++count[buffer[i] - min];
    }

    for(i = min; i <= max; ++i)
    {
        for(j = 0; j < count[i - min]; ++j)
        {
            buffer[k++] = (unch_t)i;
        }
    }

    free(count);
    return (MCS_SUCCESS);
}
/*****************************************************************************/ 
int MultithreadedCountingSort(unch_t *buffer, size_t size)
{
    uint_t count[RANGE] = {0};
    pthread_t *threads = NULL;
    size_t i = 0, j = 0, k = 0;
    size_t remainder = size % ex_thread_num;
    size_t chunk_size = size / ex_thread_num;
    thread_object_t *thread_object = malloc(sizeof(thread_object_t) * ex_thread_num);
    if(NULL == thread_object)
    {
        return (MCS_FAILURE);
    }

    threads = (pthread_t *)malloc(ex_thread_num * sizeof(pthread_t));
    if(NULL == threads)
    {
        free(thread_object);
        return (MCS_FAILURE);
    }

    pthread_mutex_init(&mutex, NULL);
    for(i = 0; i < ex_thread_num; ++i)
    {
        thread_object[i].count = count;
        thread_object[i].chunk_size = chunk_size;
        if(i == ex_thread_num - 1)
        {
            thread_object[i].chunk_size += remainder;
        }

        thread_object[i].buffer = buffer + (i * chunk_size);
        if(0 != pthread_create(&threads[i], NULL, CountingRoutine, \
           (void *)&thread_object[i]))
        {
            free(threads);
            free(thread_object);
            return (MCS_FAILURE);
        }
    }

    for(i = 0; i < ex_thread_num; ++i)
    {
        if(0 != pthread_join(threads[i], NULL))
        {
            free(threads);
            free(thread_object);
            return (MCS_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex);
    for(i = 'A'; i <= 'z'; ++i)
    {
        for(j = 0; j < count[i - 'A']; ++j)
        {
            buffer[k++] = (unch_t)i;
        }
    }

    free(threads);
    free(thread_object);
    return (MCS_SUCCESS);
}
/*****************************************************************************/ 
static void *CountingRoutine(void *arg)
{
    size_t i = 0;
    uint_t count[RANGE] = {0};
    thread_object_t *thread_object = (thread_object_t *)arg;

    for(i = 0; i < thread_object->chunk_size; ++i)
    {
        ++count[thread_object->buffer[i] - 'A'];
    }

    pthread_mutex_lock(&mutex);
    for(i = 0; i < RANGE; ++i)
    {
        thread_object->count[i] += count[i];
    }
    pthread_mutex_unlock(&mutex);

    return (NULL);
}
/*****************************************************************************/