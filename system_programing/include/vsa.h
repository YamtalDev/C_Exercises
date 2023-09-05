/*=============================================================================

                            Costumer requirements:

===============================================================================

* Usage of "free list" for the VSA.

* Free will receive only the block to free and will preform time complexity of 
  O(1) constant time.

* User will allocate large memory block and provide its address to VSAInit.

* VSA should be aligned to machine word size.

* Meta data for managing the VSA should be at the beginning of the VSA memory 
  it self and blocks in it.

* Each available block should hold the next available block(offset).

* A way to determine if the VSA is full by the return value of VSAAlloc.

===============================================================================

                 VSA(Variable Size Allocator) functionalities:

===============================================================================

1.) Function to initialize the VSA based on the user input(pool, size).

2.) Function to allocate a block of memory from the VSA.

3.) Function to free a block from the VSA.

4.) Function to return the largest chunk available in the VSA.

==============================================================================*/

#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h>

typedef struct vsa vsa_t;

/******************************************************************************

Function: VSAInit - Initialize the VSA.

Usage: vsa_t *vsa = VSAInit(memory_pool, size)

Description: The function will initialize a memory VSA(pool).

Arguments: memory_pool - The base pointer to the managed pool, 
           size - the number of bytes of the memory pool that the user allocated(including bytes for the overhead).

Return value: A pointer to the new VSA created.

Complexity: Time complexity: O(1), Space complexity: O(1) */

vsa_t *VSAInit(void *memory_pool, size_t size);

/*****************************************************************************
Function: VSAAlloc - Allocates a block from the VSA to be used.

Usage: void *block = VSAAlloc(vsa)

Description: VSAAlloc function will allocate an aligned block.

Arguments: vsa - pointer to the VSA it self, block_size - a block size for allocation. 

Return value: Return the address of the block to the caller function, 
              if the VSA is full the function will returns NULL.

Complexity: Time complexity: O(n), Space complexity: O(1) */

void *VSAAlloc(vsa_t *vsa, size_t size_to_allocate);

/*****************************************************************************
Function: VSAFree - Free a block in the vsa.

Usage: VSAFree(block)

Description: The function will free(de allocate) a block from the VSA.

Arguments: Pointer that is used as a key to the block to be freed.

Return value: No return value.

Complexity: Time complexity: O(1), Space complexity: O(1) */

void VSAFree(void *ptr);

/*****************************************************************************
Function: VSALargestChunkAvailable - Does de fragmentation and returns the size of 
          the largest chunk.

Usage: size_t largest = VSALargestChunkAvailable(vsa)

Description: The function will return the largest chunk available.

Arguments: Pointer to the VSA it self.

Return value: size_t - the size of the largest chunk.

Complexity: Time complexity: O(n), Space complexity: O(1) */

size_t VSALargestChunkAvailable(vsa_t *vsa);

/*****************************************************************************/

#endif /* __VSA_H__ */
