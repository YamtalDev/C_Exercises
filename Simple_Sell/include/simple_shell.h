#ifndef __SIMPLE_SHELL_H__
#define __SIMPLE_SHELL_H__

typedef enum status
{
    SUCCESS =0, FAILURE
} status_t;

status_t ShellFork(void);

status_t ShellSystem(void);

#endif /* __SIMPLE_SHALL_H__ */
