/*=============================================================================

                            Costumer requirements:

===============================================================================

* Usage of "free list" for the FSA.

* Allocation and de allocation in time complexity of O(1) constant time.

* Allocated blocks should be aligned to machine word size.

* Meta data for managing the FSA should be at the beginning of the FSA memory 
  it self.

* Each available block should hold the next available block(offset).

* A way to determine if the FSA is full by the return value of FSAAlloc.

===============================================================================

         Functional FSA(Fixed Size Allocator) with functionalities:

===============================================================================

1.) Function that will return a suggestion of the amount of memory to initialize
    in the FSA based on the user input(number of blocks and block size).

2.) Function to initialize the FSA based on the user input(pool, size, block_size).

3.) Function to allocate a block of memory from the FSA.

4.) Function to free a block from the FSA.

5.) Function to count the number of free(unallocated) blocks in the FSA.

==============================================================================*/

#ifndef __FSA_H__
#define __FSA_H__

/*     size_t    */

#include <stddef.h>

typedef struct fsa fsa_t;

/*****************************************************************************
Function: FSASuggestSize - Suggests the memory size to initialize the FSA.

Usage: size_t size = FSASuggestSize(number_of_blocks, block_size)

Description: The function will provide the amount of memory to initialize for
             the FSA considering word size alignment and over head.

Arguments: Block_size(the size of every block - has to be fixed), number_of_blocks.

Return value: size_t size(Amount of memory).

Complexity: Time complexity: O(1), Space complexity: O(1) */

size_t FSASuggestSize(size_t number_of_blocks, size_t block_size);

/*****************************************************************************
Function: FSAInit - Initialize the FSA.

Usage: fsa_t *fsa = FSAInit(memory_pool, suggested_size, block_size)

Description: The function will initialize a memory FSA(pool).

Arguments: memory_pool - The base pointer to the managed pool, 
           size - the number of bytes in the memory pool, block size

Return value: A pointer to the new FSA created.

Complexity: Time complexity: O(n), Space complexity: O(1) */

fsa_t *FSAInit(void *memory_pool, size_t size, size_t block_size);

/*****************************************************************************
Function: FSAAlloc - Allocates a block from the FSA to be used.

Usage: void *block = FSAAlloc(fsa)

Description: FSAAlloc function will allocate a block.

Arguments: A pointer to the FSA it self.

Return value: Return the address of the block to the caller function, 
              if the FSA is full the function will returns NULL.

Complexity: Time complexity: O(1), Space complexity: O(1) */

void *FSAAlloc(fsa_t *fsa);

/*****************************************************************************
Function: FSAFree - Free a block in the fsa.

Usage: FSAFree(fsa, block)

Description: The function will free(de allocate) a block from the FSA.

Arguments: Pointer to the FSA it self, pointer to the block to be freed.

Return value: No return value.

Complexity: Time complexity: O(1), Space complexity: O(1) */

void FSAFree(fsa_t *fsa, void *block);

/*****************************************************************************
Function: FSACountFree - Counts the number of free blocks in FSA.

Usage: size_t free_blocks = FSACountFree(fsa)

Description: The function will count the number of unallocated blocks in the FSA,
             without changing the FSA.

Arguments: Pointer to the FSA it self.

Return value: size_t - the number of free blocks remained on the FSA.

Complexity: Time complexity: O(n), Space complexity: O(1) */

size_t FSACountFree(const fsa_t *fsa);

/*****************************************************************************/

#endif /* __FSA_H__ */
