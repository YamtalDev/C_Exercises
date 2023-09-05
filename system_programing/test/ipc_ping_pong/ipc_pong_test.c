#include "ipc_ping_pong.h"
/*****************************************************************************/
void PingPong(void);
void SharedMem(void);
int NamedPipePong(void);
void MessageQueue(void);
/*****************************************************************************/
int main(void)
{
    /*PingPong();*/
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
        perror("PingPongInit failed\n");
        return;
    }

    for(;i < 5; ++i)
    {
        sem_wait(&data->pong);
        puts("Pong");
        sem_post(&data->ping);
    }

    PingPongCleanup(data);
}
/*****************************************************************************/
int NamedPipePong(void)
{
    int i = 0;
    int pipe_fd = 0;
    char message[20] = {0};
    const char *pong = "Pong";
    mkfifo(PIPE, 0666);

    for(; i < 20; i++)
    {
        pipe_fd = open(PIPE, O_RDONLY);
        if(-1 == pipe_fd)
        {
            return (-1);
        }

        if(0 >= read(pipe_fd, message, sizeof(message)))
        {
            perror("Parent: Read failure");
            return (-1);
        }

        puts(message);
        sleep(1);
        close(pipe_fd);
        pipe_fd = open(PIPE, O_WRONLY);
        if(-1 == pipe_fd)
        {
            return (-1);
        }

        if(0 >= write(pipe_fd, pong, strlen(pong) + 1))
        {
            return (-1);
        }

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
    message.message_type = 1;
    strcpy(message.message_text, "Hi");
    msgsnd(msgid, &message, 10, 0);

    message.message_type = 2;
    strcpy(message.message_text, "Tal");
    msgsnd(msgid, &message, 10, 0);

    message.message_type = 3;
    strcpy(message.message_text, "Aharon");
    msgsnd(msgid, &message, 10, 0);
}
/*****************************************************************************/
void SharedMem(void)
{
    key_t key = ftok("shared_mem",65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, NULL, 0);
    strcpy(str, "Tal Aharon");
    shmdt(str);
}
/*****************************************************************************/