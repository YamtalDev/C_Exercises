#define _POSIX_C_SOURCE 199309L
#include "ipc_ping_pong.h"
/*****************************************************************************/
shared_data_t *InitSharedData(void)
{
    shared_data_t *data =   NULL;
    int shm_fd = shm_open("/ping_pong_shm", O_CREAT | O_RDWR, 0644);
    if(-1 == shm_fd)
    {
        return (NULL);
    }

    if(-1 == ftruncate(shm_fd, sizeof(shared_data_t)))
    {
        shm_unlink("/ping_pong_shm");
        return (NULL);
    }

    data = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(MAP_FAILED == data)
    {
        shm_unlink("/ping_pong_shm");
        return (NULL);
    }

    return (data);
}
/*****************************************************************************/
void PingPongCleanup(shared_data_t *data)
{
    sem_destroy(&data->ping);
    sem_destroy(&data->pong);
    munmap(data, sizeof(shared_data_t));
    shm_unlink("/ping_pong_shm");
}
/*****************************************************************************/
void InitSemaphores(shared_data_t *data)
{
    if(-1 == sem_init(&(data->ping), 1, 1))
    {
        munmap(data, sizeof(shared_data_t));
        shm_unlink("/ping_pong_shm");
        return;
    }

    if(-1 == sem_init(&(data->pong), 1, 0))
    {
        sem_destroy(&(data->ping));
        munmap(data, sizeof(shared_data_t));
        shm_unlink("/ping_pong_shm");
        return;
    }
}
/*****************************************************************************/
void ClosePipes(int pipe1, int pipe2)
{
    close(pipe1);
    close(pipe2);
}
/*****************************************************************************/
void InitPipes(int *pipe1, int *pipe2)
{
    if(-1 == pipe(pipe1))
    {
        perror("Parent pipe failure\n");
        return;
    }

    if(-1 == pipe(pipe2))
    {
        perror("Child pipe failure\n");
        return;
    }
}
/*****************************************************************************/
