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
  █ ▓█  ███▓▓░▄█▄▄██▄█▄▄▄░░     ▄▓▓▓░░░ ░▀  ░░░          ░░▓█▓    ░ ░░░▓█ ▀
   ▀▀   ███▓▓▓░░░░░░░  ░▓▓░░         ░     ░▓████▓▓░░░ ░  ░░▓▓  ░   ░░▓▓▓▀
     ▄▓▄ ███▓▓▓░░░░  ▄░▀▄░░░░░░░    ░    ░▓███▓░▀▀▀██▄    ░░░     ░░░▓▓▓ ▄░▀▀▄
      ▀   ▀███▓▓▓▄▄▄ ▀▄▓▀░ ▄▄▄ ░░░░░░ ░░░▓███▓░     ▀██░ ░▓░░░ ░░░░░▓▓▓ █░   ▓█
*******************************************************************************

    writer: Tal Aharon

    reviewer: Zehorit Cohen

    date : 16.04.2023

    Description:

	This is a C implementation of a Variable Size Allocator (VSA) using a memory 
	pool. The VSA allows dynamic memory allocation and deallocation of different 
	sizes within a given memory pool. The code consists of four functions:

	VSAInit - initializes the VSA with the given memory pool and its size.

	VSAAlloc - allocates a block of memory of the given size from the VSA.

	VSAFree - frees the previously allocated block of memory.

	VSALargestChunkAvailable - returns the size of the largest free block of 
	memory available in the VSA.

	The implementation uses a metadata structure to keep track of the allocated 
	and free blocks of memory in the memory pool. The metadata structure contains 
	two fields: the size of the block and a magic number (used for debugging).

	The implementation also uses bit manipulation to keep track of the status of 
	the blocks of memory. The least significant bit of the size field in the 
	metadata structure is used to indicate whether the block is allocated or free. 
	If the bit is 1, the block is allocated, and if it is 0, the block is free.

	The code also uses some macros and helper functions for alignment, checking 
	if a block is taken or free, setting the first bit of a block to 1 (taken), 
	and setting the first 1 bit of a number to 0 (free).

******************************************************************************/
#include <assert.h> /*    assert    */
#include "vsa.h"    /*     API      */
/*****************************************************************************/
struct vsa
{
	size_t pool_size;
};
/*****************************************************************************/
typedef struct m_data
{
	size_t size;
	#ifndef NDEBUG
	size_t magic_number;
	#endif

} meta_data;
/*****************************************************************************/
/* word size */
#define WORD (sizeof(size_t))

/* meta-data size */
#define HEADER (sizeof(meta_data))

/* End address of pool */
#define END(X) ((char *)X + X->pool_size)

/* Starting address of pool + overhead */
#define START(X) ((char *)X + sizeof(vsa_t))

/* Dereference for a desired struct field */
#define META_DATA(X,Y) ((*(meta_data *)X).Y)

/* Check first bit of meta data block size */
#define IS_TAKEN(X) (META_DATA(X, size) & 0x1)

/* Align address or number to the system word */
#define ALIGN(X) (X + (WORD - (X % WORD)) * ((X % WORD) != 0))
/*****************************************************************************/
vsa_t *VSAInit(void *memory_pool, size_t size)
{
	vsa_t *vsa = NULL;
	assert(memory_pool && "Memory pool is not valid.");

	if(size < HEADER)
	{
		return (NULL);
	}

	/* Aligning vsa and decreasing size accordingly */
	vsa = (vsa_t *)ALIGN((size_t)memory_pool);
	size -= ((size_t)vsa - (size_t)memory_pool);
	size -= size % WORD;

	vsa->pool_size = size;
	META_DATA(START(vsa), size) = vsa->pool_size - sizeof(vsa_t);

	#ifndef NDEBUG
	META_DATA(START(vsa), magic_number) = (size_t)START(vsa);
	#endif

	return (vsa);
}
/*****************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t size)
{
	char *end = NULL;
	char *block = NULL;
	char *next_block = NULL;
	size_t remaining_size = 0;
	assert(vsa && "VSA is not valid.");

	if(0 == size || vsa->pool_size < (size = ALIGN(size) + HEADER))
	{
		return (NULL);
	}

	end = END(vsa);
	block = START(vsa);
	while((end > block) && ((META_DATA(block, size) < size) || IS_TAKEN(block)))
	{
		next_block = block + (META_DATA(block, size) & ~(0x1));
		if((end > next_block) && !IS_TAKEN(block) && !IS_TAKEN(next_block))
		{
			META_DATA(block, size) += META_DATA(next_block, size);
			continue;
		}

		block += (META_DATA(block, size) & ~(0x1));
	} 

	if(end <= block)
	{
		return (NULL);
	}

	remaining_size = META_DATA(block, size) - size;
	if(HEADER <= remaining_size)
	{
		META_DATA(block, size) = (size | 0x1);
		META_DATA((block + size), size) = (remaining_size & ~(0x1));
	}
	else
	{
		META_DATA(block, size) |= 0x1;
	}

	#ifndef NDEBUG
	META_DATA(block, magic_number) = (size_t)block;
	#endif

	return ((void *)(block + HEADER));
}
/*****************************************************************************/ 
void VSAFree(void *ptr)
{
	char *m_ptr = NULL;
	if(NULL == ptr)
	{
		return;
	}

	m_ptr = (char *)ptr - HEADER;

	#ifndef NDEBUG
	assert(META_DATA(m_ptr, magic_number) == (size_t)m_ptr);
	META_DATA(m_ptr, magic_number) = 0;
	#endif

	META_DATA(m_ptr, size) &= ~(0x1);
}
/*****************************************************************************/ 
size_t VSALargestChunkAvailable(vsa_t *vsa)
{
	char *end = NULL;
	char *block = NULL;
	char *next_block = NULL;
	size_t chunk = 0;
	assert(vsa != NULL && "VSA is not valid.");

	end = END(vsa);
	block = START(vsa);
	next_block = block + (META_DATA(block, size) & ~(0x1));
	while(next_block < end)
	{
		if((next_block < end) && !IS_TAKEN(next_block) && !IS_TAKEN(block))
		{
			META_DATA(block, size) += META_DATA(next_block, size);
			next_block = block + META_DATA(block, size);
			continue;
		}

		if(chunk < META_DATA(block, size) && !IS_TAKEN(block))
		{
			chunk = META_DATA(block, size);
		}

		block = next_block;
		next_block += (META_DATA(next_block, size) & ~(0x1));
	}

	if(chunk < META_DATA(block, size) && !IS_TAKEN(block))
	{
		chunk = META_DATA(block, size);
	}

	return (chunk > 0) * (chunk - HEADER);
}
/*****************************************************************************/ 
