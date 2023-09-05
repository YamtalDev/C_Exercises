#ifndef __MULTITHREADED_COUNTING_SORT_H__
#define __MULTITHREADED_COUNTING_SORT_H__

/*  size_t, NULL  */
#include <stddef.h>
extern size_t ex_thread_num;
typedef unsigned char unch_t;
typedef unsigned int uint_t;

#define TIMES (10)
#define RANGE ('z' - 'A' + 1)

enum msc_status
{
    MCS_SUCCESS = 0, MCS_FAILURE
};

int MultithreadedCountingSort(unch_t *buffer, size_t size);
int CountingSort(unch_t *buffer, size_t size);

#endif /* __MULTITHREADED_COUNTING_SORT_H__ */
