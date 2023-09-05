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
#include <stdlib.h>    /* malloc, free */
#include <assert.h>    /* assert       */

#include "circular_buffer.h"   /* Internal use */

/*****************************************************************************/
struct cbuff
{
    size_t start;
    size_t size;
    size_t bufsiz;
    char buffer[1];
};
/*****************************************************************************/
cbuff_t *CircularBufferCreate(size_t capacity)
{
	cbuff_t *cbuff = (cbuff_t *)malloc(sizeof(cbuff_t) + capacity);

	if(NULL == cbuff)
	{
		return NULL;
	}

	cbuff -> bufsiz = capacity;
	cbuff -> start = 0;
	cbuff -> size = 0;

	return cbuff;
}
/*****************************************************************************/
void CircularBufferDestroy(cbuff_t *buffer)
{
	assert(buffer && "Buffer isn't valid.");
	free(buffer);
	buffer = NULL;
}
/*****************************************************************************/
ssize_t CircularBufferWrite(cbuff_t *buffer, const void *source, size_t amount)
{
	size_t bytes = 0;
	ssize_t index = 0;
	unsigned char *src = (unsigned char *)source;

	assert(buffer && "Buffer isn't valid.");

	while(amount-- && CircularBufferFreeSpace(buffer))
	{
		index = (buffer -> size) + (buffer -> start) % (buffer -> bufsiz);
		buffer -> buffer[index] = *src++;
		++(buffer -> size);
		++bytes;
	}

	return bytes;
}
/*****************************************************************************/
ssize_t CircularBufferRead(cbuff_t *buffer, void *dest, size_t amount)
{
	ssize_t bytes = 0;
	unsigned char *destination = (unsigned char *)dest;

	assert(buffer && "Buffer isn't valid.");
	assert(buffer && "Destination buffer isn't valid.");

	while(amount-- && !CircularBufferIsEmpty(buffer))
	{
		*destination++ = buffer -> buffer[buffer -> start];
		buffer -> start = (buffer -> start + 1) % (buffer -> bufsiz);
		--(buffer -> size);
		++bytes;
	}

	return bytes;
}
/*****************************************************************************/
int CircularBufferIsEmpty(const cbuff_t *buffer)
{
	assert(buffer && "Buffer isn't valid.");
	return 0 == buffer -> size;
}
/*****************************************************************************/
size_t CircularBufferFreeSpace(const cbuff_t *buffer)
{
	assert(buffer && "Buffer isn't valid.");
	return buffer -> bufsiz - buffer -> size;
}
/*****************************************************************************/
size_t CircularBufferBufsiz(const cbuff_t *buffer)
{
	assert(buffer && "Buffer isn't valid.");
	return buffer -> bufsiz;
}
/*****************************************************************************/
