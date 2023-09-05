/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Ravit Yehud               ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    📅️ : 15.03.2023                     ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀          🐈️
******************************************************************************/
#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <sys/types.h> /*ssize_t, size_t*/

typedef struct cbuff cbuff_t;

/*TC : O(1) create a buffer, return NULL on fail*/
cbuff_t *CircularBufferCreate(size_t capacity);

/*TC : O(1) delete a buffer*/
void CircularBufferDestroy(cbuff_t *buffer);

/*TC : O(n) write amount bytes from source to buffer*/		
ssize_t CircularBufferWrite(cbuff_t *buffer, const void *source, size_t amount);

/*TC : O(n) read amount bytes from buffer to dest*/
ssize_t CircularBufferRead(cbuff_t *buffer, void *dest, size_t amount);

/*TC : O(1) return non-zero value if buffer is empty*/
int CircularBufferIsEmpty(const cbuff_t *buffer);

/*TC : O(1) return how much unused bytes are in the buffer*/
size_t CircularBufferFreeSpace(const cbuff_t *buffer);

/*TC : O(1) return the capacity of the buffer*/
size_t CircularBufferBufsiz(const cbuff_t *buffer);

#endif /* __CIRCULAR_BUFFER_H__ */
