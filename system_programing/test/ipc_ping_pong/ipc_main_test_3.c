#include "ipc_ping_pong.h"
void SharedMem(void);
void MessageQueue(void);
/*****************************************************************************/
int main(void)
{
    /*MessageQueue();*/
    MessageQueue();
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
  
    msgrcv(msgid, &message, 10, 3, 0);
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
    shmctl(shmid,IPC_RMID,NULL);
}
/*****************************************************************************/
