#ifndef __IPC_PING_PONG_H__
#define __IPC_PING_PONG_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define PIPE "pipe"
struct shared_data
{
    sem_t ping;
    sem_t pong;
};

typedef struct shared_data shared_data_t;

shared_data_t *InitSharedData(void);
void InitSemaphores(shared_data_t *);
void PingPongCleanup(shared_data_t *);

void InitPipes(int *, int *);
void ClosePipes(int, int);

#endif /* __IPC_PING_PONG_H__ */
