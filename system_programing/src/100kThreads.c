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

    Reviewer: First name and family name.

    Date: 03.06.2023

*******************************************************************************

                          Description:

  This C code implements multiple examples of multithreading and array manipulation. 
  It creates and joins threads, performs array operations, and measures execution 
  time. The examples demonstrate different scenarios, including creating threads 
  with and without error handling, detaching threads, and parallelizing array 
  manipulation using OpenMP directives. The code utilizes structures to pass 
  data to threads and includes assertions to verify array correctness. Overall, 
  it showcases concepts of multithreading, parallelization in C.

******************************************************************************/
#include <pthread.h> /* pthread_create, pthread_join, pthread_exit */
#include <omp.h>     /* #pragma omp parallel for                   */
#include <stdio.h>   /* printf                                     */
#include <assert.h>  /* assert                                     */
#include <unistd.h>  /* sleep                                      */
#include <time.h>    /* time                                       */

#include "100kThreads.h"      /* Internal API */
/*****************************************************************************/
#define TIME_OF_SLEEP (15)
size_t number = 1234567890;
size_t global_sum_of_div = 0;
#define NUMBER_OF_THREADS (32)
/*****************************************************************************/
typedef struct Array
{
    int value;
    int padding;
} array_t;
/*****************************************************************************/
typedef struct thread_data
{
    size_t end;
    size_t start;

} thread_data_t;

array_t array[NUMBER_OF_THREADS];
/*****************************************************************************/
static void *Routine(void *);
static void *WorkLoad(void *arg);
static void *DetachRoutine(void *arg);
static void InitiateArrayToZero(void);
/*****************************************************************************/
int ex1(void)
{
    size_t i = 0;
    pthread_t threads[NUMBER_OF_THREADS] = {0};
    time_t start_time = time(NULL);

    InitiateArrayToZero();
    for(; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, Routine, (void *)i);
    }

    printf("\nTotal time: %ld", time(NULL) - start_time);

    sleep(TIME_OF_SLEEP);
    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        assert(array[i].value == (int)i);
    }

    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    return (SUCCESS);
}
/*****************************************************************************/ 
int ex2(void)
{
    size_t i = 0;
    int status = FAILURE;
    pthread_t threads[NUMBER_OF_THREADS] = {0};
    time_t start_time = time(NULL);

    InitiateArrayToZero();
    for(; i < NUMBER_OF_THREADS; ++i)
    {
        while(status != 0)
        {
            status = pthread_create(&threads[i], NULL, Routine, (void *)i);
        }

        status = FAILURE;
    }

    printf("\nTotal time: %ld", time(NULL) - start_time);
    sleep(TIME_OF_SLEEP);   
    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        assert(array[i].value == (int)i);
    }

    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    return (SUCCESS);
}
/*****************************************************************************/ 
int ex3(void)
{
    size_t i = 0;
    int status = FAILURE;
    pthread_t threads[NUMBER_OF_THREADS] = {0};
    time_t start_time = time(NULL);

    InitiateArrayToZero();
    for(; i < NUMBER_OF_THREADS; ++i)
    {
        while(SUCCESS != status)
        {
            status = pthread_create(&threads[i], NULL, DetachRoutine, (void *)i);
        }

        status = FAILURE;
    }

    printf("\nTotal time: %ld", time(NULL) - start_time);
    sleep(TIME_OF_SLEEP);   
    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        assert(array[i].value == (int)i);
    }

    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    return (SUCCESS);
}
/*****************************************************************************/ 
int ex4(void)
{
    size_t i = 0;
    int status = FAILURE;
    size_t chunk = number / NUMBER_OF_THREADS;
    pthread_t threads[NUMBER_OF_THREADS] = {0};
    thread_data_t thread_data[NUMBER_OF_THREADS] = {0};

    time_t start_time = time(NULL);
    for(; i < NUMBER_OF_THREADS; ++i)
    {
        thread_data[i].start = (i * chunk) + 1;
        thread_data[i].end = thread_data[i].start + chunk - 1;

        if(i == NUMBER_OF_THREADS - 1)
        {
            thread_data[i].end = number;
        }

        while(SUCCESS != status)
        {
            status = pthread_create(&threads[i], NULL, WorkLoad, (void *)&thread_data[i]);
        }

        status = FAILURE;
    }

    printf("\nTotal time: %ld\n", time(NULL) - start_time);
    sleep(TIME_OF_SLEEP);   

    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Sum of divisors: %lu\n", global_sum_of_div);
    return (SUCCESS);
}
/*****************************************************************************/ 
int ex5(void)
{
    size_t i = 1;
    size_t sum_of_div = 0;
    for(; i <= number; ++i)
    {
        if(0 == (number % i))
        {
            sum_of_div += i;
        }
    }

    return (SUCCESS);
}
/*****************************************************************************/ 
int ex6(void)
{
    size_t i = 0;
    time_t start_time = time(NULL);

    InitiateArrayToZero();
    #pragma omp parallel for
    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        array[i].value = i;
    }

    printf("\nTotal time: %ld\n", time(NULL) - start_time);
    sleep(TIME_OF_SLEEP);

    for(i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        assert(array[i].value == (int)i);
    }

    return (SUCCESS);
}
/*****************************************************************************/ 
static void *Routine(void *arg)
{
    array[(size_t)arg].value = (size_t)arg;
    return (NULL);
}
/*****************************************************************************/ 
static void InitiateArrayToZero(void)
{
    size_t i = 0;
    for(; i < NUMBER_OF_THREADS; ++i)
    {
        array[i].value = 0;
    }
}
/*****************************************************************************/ 
static void *DetachRoutine(void *arg)
{
    array[(size_t)arg].value = (size_t)arg;
    pthread_exit(NULL);
    return (NULL);
}
/*****************************************************************************/
static void *WorkLoad(void *arg)
{
    size_t i = 0;
    size_t sum_of_div = 0;
    thread_data_t *data = (thread_data_t *)arg;
    for(i = data->start; i <= data->end; ++i)
    {
        if(0 == (number % i))
        {
            sum_of_div += i;
        }
    }

    global_sum_of_div += sum_of_div;
    return (NULL);
}
/*****************************************************************************/