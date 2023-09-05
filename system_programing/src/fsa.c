/******************************************************************************
                                        ▄▄▀▀▀▀████▓▓░░  ░
                                     ▄█▓░░   ░▓█▓
                                   ▄█▓░░    ░▓█░
                                  █▓░░░░   ░▓█░
                                ▄█▓░░░    ░░▓█░
        ▄▄▄              ▄▄▄▄█▄█▓▓▀▀▀▓███▄▄▓██▓░ ░
       █░  █         ▄▄▓▓▓▓░░░░░░░░░░░░░░░▓████▄▄                      ▄▄▄▄▄▄▓
      █    ▓█    ▄▄▓▓▓▓░▓░░░   ░░░░░░░░░░░░░░░▓▓▓█▄▄     ▄        ▄▄▓▓▓░░░░█▀
       █  ▓█   ▄█▓░▄██▓░░       ░  ░░░░░░ ░░░░░░▓▓▓▓██▄    ▄   ░▄▓▓▓░░  ░▓█▓
        ▀▀▀  ▄█▓░ ▄▄▄▄▄ ░░           ░░░   ░  ▄▄▄ ░░▓▓▓█▄ ▀▓▀ ░█▓▓░░   ░▓█▓
      ▄▄    ██▓░▄▀  ░░▓█▓░░       ░  ░░      █░  █  ░░░▓▓█▄  ▓█▓▓░░   ░▓▓█░
     █ ▓█  ██▓░▓█     ░▓█▓░░   ░   ░░░      █░  ░▓█   ░░▓▓██▓█▓▓░    ░░▓▓█
      ▀▀  ██▓▓░█▓      ░▓░░   ░ ░            █ ░▓█     ░░░▓███▓░ ░  ░░░▓█▓
   ▄▄  ▄ ██▓▓░ █░  ▄▄▄  ░░     ░    ▄▄▄▄▄     ▀▀▀ ▄  ░  ░░░▓█▓░    ░░░▓▓█
  █ ▓█   ██▓▓░▄█▄▄██▄█▄▄▄░░     ▄▓▓▓░░░ ░▀  ░░░          ░░▓█▓    ░ ░░░▓█ ▀
   ▀▀   ███▓▓▓░░░░░░░  ░▓▓░░         ░     ░▓████▓▓░░░ ░  ░░▓▓  ░   ░░▓▓▓▀
     ▄▓▄ ███▓▓▓░░░░  ▄░▀▄░░░░░░░    ░    ░▓███▓░▀▀▀██▄    ░░░     ░░░▓▓▓ ▄░▀▀▄
      ▀   ▀███▓▓▓▄▄▄ ▀▄▓▀░ ▄▄▄ ░░░░░░ ░░░▓███▓░     ▀██░ ░▓░░░ ░░░░░▓▓▓ █░   ▓█
*******************************************************************************

    writer: Tal Aharon

    reviewer: Yonatan Longini

    date : 10.04.2023

******************************************************************************/
#include <assert.h>    /* assert       */
#include "fsa.h"       /* Internal use */

/* Align a value to machine word size */
#define WORD (sizeof(size_t))
#define ALIGN(X) (X + (WORD - (X % WORD)) * ((X % WORD) != 0))
/*****************************************************************************/
struct fsa
{
	size_t offset;
};
/*****************************************************************************/
size_t FSASuggestSize(size_t number_of_blocks, size_t block_size)
{
	/* Calculating the size with extra padding for safty */
	return (sizeof(fsa_t) + (WORD - 1) + number_of_blocks * ALIGN(block_size));
}
/*****************************************************************************/ 
fsa_t *FSAInit(void *memory_pool, size_t size, size_t block_size)
{
	fsa_t *fsa = NULL;
	char *block = NULL;
	assert(memory_pool && "Memory pool is not valid.");

	fsa = (fsa_t *)ALIGN((size_t)memory_pool);
	fsa->offset = sizeof(fsa_t);

	block = (char *)((size_t)fsa + sizeof(fsa_t));
	block_size = ALIGN(block_size);

	/* Decrementing the size to ensure one block size is left at the end */
	size -= (block_size + sizeof(fsa_t));

	for(; fsa->offset < size; fsa->offset += block_size, block += block_size)
	{
		*(size_t *)block = fsa->offset + block_size;
	}

	*(size_t *)block = 0;
	fsa->offset = sizeof(fsa_t);
	return (fsa);
}
/*****************************************************************************/ 
void *FSAAlloc(fsa_t *fsa)
{
	void *allocted_block = NULL;
	assert(fsa && "FSA is not valid.");

	if(!fsa->offset)
	{
		return (NULL);
	}

	allocted_block = (void *)((char *)fsa + fsa->offset);
	fsa->offset = *(size_t *)allocted_block;

	return (allocted_block);
}
/*****************************************************************************/ 
void FSAFree(fsa_t *fsa, void *block)
{
	assert(fsa && "FSA is not valid.");
	if(NULL == block)
	{
		return;
	}

	*(size_t *)block = fsa->offset;
	fsa->offset = (size_t)((char *)block - (char *)fsa);
}
/*****************************************************************************/ 
size_t FSACountFree(const fsa_t *fsa)
{
	size_t counter = 0;
	size_t *runner = NULL;
	assert(fsa && "FSA is not valid.");

	runner = (size_t *)((char *)fsa + fsa->offset);
	for(;*runner; ++counter)
	{
		runner = (size_t *)((char *)fsa + *runner);
	}

	/* Check if we got to the end */
	return ((0 != fsa->offset) * (1 + counter));
}
/*****************************************************************************/ 
