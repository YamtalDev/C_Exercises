#ifndef __SIGNAL_PING_PONG_H__
#define __SIGNAL_PING_PONG_H__

typedef enum status
{
    SUCCESS = 0, FAILURE 
} status_t;

void SignalHandler(int sig);
status_t ProcPingPong(void);
status_t ProcPingPongTwo(void);
void InitProgramSettings(void);
status_t ProcPingPongUnrelated(void);

#endif /* __SIGNAL_PING_PONG_H__ */
