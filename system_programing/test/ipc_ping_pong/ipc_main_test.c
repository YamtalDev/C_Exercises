#include "ipc_ping_pong.h"
void PingPong(void);
void PipePong(void);
int NamedPipePong(void);
void MessageQueue(void);
void SharedMem(void);
/*****************************************************************************/
int main(void)
{
    /*PingPong();*/
    /*PipePong();*/
    NamedPipePong();
    /*MessageQueue();*/
    /*SharedMem();*/
    return (0);
}
/*****************************************************************************/
void PingPong(void)
{
    int i = 0;
    shared_data_t *data = InitSharedData();
    if(NULL == data)
    {
        perror("Init failed\n");
        return;
    }

    InitSemaphores(data);
    for(;i < 5; ++i)
    {
        sem_wait(&data->ping);
        puts("Ping");
        sem_post(&data->pong);
    }

    PingPongCleanup(data);
}
/*****************************************************************************/
void PipePong(void)
{
    int i = 0;
    int child_pid = 0;

    char message[20] = {0};
    const char *pong = "Pong";
    const char *ping = "Ping";

    int parent[2] = {0};
    int child[2] = {0};

    InitPipes(parent, child);
    child_pid = fork();
    if(-1 == child_pid)
    {
        perror("Fork failure");
        return;
    }

    if(child_pid == 0)
    {
        for(; i < 5; i++)
        {
            if(0 >= read(parent[0], message, sizeof(message)))
                break;

            puts(message);
            write(child[1], pong, strlen(pong) + 1);
        }
        return;
    }
    else
    {
        for(; i < 5; i++)
        {
            write(parent[1], ping, strlen(ping) + 1);
            if(0 >= read(child[0], message, sizeof(message)))
                break;

            puts(message);
        }

        wait(NULL);
    }

    ClosePipes(parent[1], child[0]);
    ClosePipes(parent[0], child[1]);
}
/*****************************************************************************/
int NamedPipePong(void)
{
    int i = 0;
    int pipe_fd = 0;
    char message[20] = {0};
    const char *ping = "Ping";
    mkfifo(PIPE, 0666);

    for(; i < 20; i++)
    {
        pipe_fd = open(PIPE, O_WRONLY);
        if(-1 == pipe_fd)
            return (-1);

        if(0 >= write(pipe_fd, ping, strlen(ping) + 1))
            return (-1);

        close(pipe_fd);
        pipe_fd = open(PIPE, O_RDONLY);

        if(0 >= read(pipe_fd, message, sizeof(message)))
            return (-1);

        puts(message);
        sleep(1);
        if(-1 == pipe_fd)
            return (-1);

        close(pipe_fd);
    }

    unlink(PIPE);
    return (0);
}
/*****************************************************************************/
void MessageQueue(void)
{
    key_t key = 0;
    int msgid = 0;
    struct message_buffer
    {
        long message_type;
        char message_text[10];
    } message;
 
    key = ftok("MessageQueue", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    msgrcv(msgid, &message, 10, 1, 0);
    printf("Data Received is: %s \n", message.message_text);
}
/*****************************************************************************/
void SharedMem(void)
{
    key_t key = ftok("shared_mem",65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*)shmat(shmid , NULL, 0);
    printf("Data read from memory: %s\n",str);
    shmdt(str);
}
/*****************************************************************************/