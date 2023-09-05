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

  The given code is a program that tests the performance of a multithreaded 
  counting sort algorithm. It measures the execution time of both the 
  multithreaded and normal counting sort algorithms on different thread numbers. 
  The sorted buffers are checked for correctness, and the most efficient thread 
  number is determined based on the minimum execution time. The program includes 
  header files, defines constants, and contains functions to load data, calculate 
  buffer size, and find the best thread number.

******************************************************************************/
#include <stdio.h>                          /* printf         */
#include <assert.h>                         /* assert         */
#include <stdlib.h>                         /* rand, q_sort   */
#include <time.h>                           /* clock, clock_t */

#include "multithreaded_counting_sort.h"    /* Internal API   */
/*****************************************************************************/
size_t ex_thread_num = 1;
#define MULTIPLIER (2)
#define MAX_THREADS (128)
/*****************************************************************************/
int MultithreadedCountingSortTest(void);
int cmpfunc(const void *, const void *);
/*****************************************************************************/
static unch_t *LoadBuffer(size_t);
static size_t GetBufferSize(void);
static uint_t BestThreadNumber(double *, size_t);
/*****************************************************************************/
int main(void)
{
    assert(MCS_SUCCESS == MultithreadedCountingSortTest());
    puts("\nTest() : passed.");
    return (MCS_SUCCESS);
}
/*****************************************************************************/
int MultithreadedCountingSortTest(void)
{
    size_t i = 0;
    size_t j = 0;
    clock_t t = (clock_t)0;
    clock_t mt = (clock_t)0;
    unch_t *r_buffer = NULL;
    unch_t *m_buffer = NULL;
    double time_taken = 0.0;
    double mtime_taken = 0.0;
    double time_buffer[7] = {0.0};
    size_t size = GetBufferSize();
    for(; ex_thread_num != MAX_THREADS; ex_thread_num *= MULTIPLIER)
    {
        puts("\n\n");
        r_buffer = LoadBuffer(size);
        m_buffer = LoadBuffer(size);
        if(r_buffer == NULL || m_buffer == NULL)
        {
            printf("Failed to load dictionary buffer.\n");
            return (MCS_FAILURE);
        }

        t = clock();
        assert(MCS_SUCCESS == CountingSort(r_buffer, size));
        t = clock() - t;

        mt = clock();
        assert(MCS_SUCCESS == MultithreadedCountingSort(m_buffer, size));
        mt = clock() - mt;

        for(i = 0; i < (size - 1); ++i)
        {
            assert(m_buffer[i] <= m_buffer[i + 1]);
        }

        time_taken = ((double)t) / CLOCKS_PER_SEC;
        mtime_taken = ((double)mt) / CLOCKS_PER_SEC;
        printf("\nrun: %ld.) MultithreadedCountingSort: %.6f\n\nrun: %ld.) CountingSort: %.6f.\n", j + 1, mtime_taken, j + 1, time_taken);
        printf("\nrun: %ld.) MultithreadedCountingSort clocks: %ld.\n\nrun: %ld.) CountingSort clocks: %ld.", j + 1, mt, j + 1, t);

        time_buffer[j++] = mtime_taken;
        time_taken = 0;
        mtime_taken = 0;
        t = (clock_t)0;
        mt = (clock_t)0;
        free(r_buffer);
        free(m_buffer);
    }

    printf("\n\nMost efficient thread number is: %d\n\n", BestThreadNumber(time_buffer, 7));
    return (MCS_SUCCESS);
}
/*****************************************************************************/
static unch_t *LoadBuffer(size_t size)
{
    int i = 0;
    int c = 0;
    int index = 0;
    unch_t *buffer = NULL;
    FILE *file = fopen("/usr/share/dict/words", "r");
    if(NULL == file) 
    {
        return NULL;
    }

    buffer = (unch_t *)malloc(size + 1);
    if(NULL == buffer)
    {
        fclose(file);
        return (NULL);
    }

    for(; i < TIMES; ++i)
    {
        while(EOF != (c = fgetc(file)))
        {
            if('A' <= c && 'z' >= c)
            {
                buffer[index++] = c;
            }
        }

        rewind(file);
    }

    fclose(file);
    return (buffer);
}
/*****************************************************************************/
static size_t GetBufferSize(void)
{
    int c = 0;
    size_t size = 0;
    FILE *file = fopen("/usr/share/dict/words", "r");
    if(NULL == file) 
    {
        return (0);
    }

    while(EOF != (c = fgetc(file)))
    {
        if('A' <= c && 'z' >= c)
        {
            ++size;
        }
    }

    fclose(file);
    return (size * TIMES);
}
/*****************************************************************************/
static uint_t BestThreadNumber(double* time_buffer, size_t size)
{
    size_t i = 1;
    size_t index = 0;
    double min_time = time_buffer[0];

    for(; i < size; ++i)
    {
        if(time_buffer[i] < min_time)
        {
            min_time = time_buffer[i];
            index = i;
        }
    }

    return (1 << index);
}
/*****************************************************************************/