#ifndef __SEM_MANIPULATIONS_H__
#define __SEM_MANIPULATIONS_H__

typedef enum status 
{
    SUCCESS = 0, FAILURE
} status_t;

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

typedef enum init
{
    INITIALIZED = 0,
    NOT_INITIALIZED
} init_status_t;

status_t StartPlayingWithSemaphore(char *command);

#endif /* __SEM_MANIPULATIONS_H__ */
