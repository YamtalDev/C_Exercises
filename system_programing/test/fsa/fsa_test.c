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
#include <stdio.h>   /* printf, puts */
#include <stddef.h>  /* size_t, NULL */
#include <stdlib.h>  /* malloc, free */
#include <assert.h>  /*   assert     */
#include <string.h>  /*   strcpy     */

#include "fsa.h"

void FSASuggestSizeTest(void);
void FSAInitTest(void);
void FSAAllocTest(void);
void FSAFreeTest(void);
void FSACountFreeTest(void);

/*****************************************************************************/
int main(void)
{
	FSASuggestSizeTest();
	puts("\nFSASuggestSizeTest() : passed.");
	FSAInitTest();
	puts("\nFSAInitTest() : passed.");
	FSAAllocTest();
	FSAFreeTest();
	puts("\nFSAFreeTest() : passed.");
	FSACountFreeTest();
	puts("\nFSACountFreeTest() : passed.");
	return (0);
}
/*****************************************************************************/
void FSASuggestSizeTest(void)
{
	assert(95 == FSASuggestSize(10, 8));
	assert(175 == FSASuggestSize(20, 3));
	assert(1615 == FSASuggestSize(100, 11));
}
/*****************************************************************************/
void FSAInitTest(void)
{
	fsa_t *fsa = NULL;
	size_t size = FSASuggestSize(20, 3);
	void *pool = malloc(size);
	assert(pool && "Malloc faild");
	assert((fsa = FSAInit(pool, size, 3)));
	free(pool);
}
/*****************************************************************************/
void FSAAllocTest(void)
{
	fsa_t *fsa = NULL;
	size_t block_size = 48;
	size_t size = FSASuggestSize(3, block_size);
	void *pool = malloc(size);
	char *allocted_block = NULL;
	char *allocted_block2 = NULL;
	char *allocted_block3 = NULL;
	char *allocted_block4 = NULL;
	assert(159 == size);
	assert(pool && "Malloc faild");
	assert((fsa = FSAInit(pool, size, block_size)));
	assert((allocted_block = (char *)FSAAlloc(fsa)));
	while(block_size--)
	{
		*allocted_block = '!';
		allocted_block++;
	}
	assert((allocted_block2 = (char *)FSAAlloc(fsa)));
	assert((strcpy(allocted_block2, "\nFSAAllocTest() : passed.\n")));
	printf("%s", allocted_block2);
	assert((allocted_block3 = (char *)FSAAlloc(fsa)));
	printf("%s", allocted_block3);
	assert(NULL == (allocted_block4 = FSAAlloc(fsa)));
	free(pool);
}
/*****************************************************************************/
void FSAFreeTest(void)
{
	fsa_t *fsa = NULL;
	size_t block_size = 48;
	size_t size = FSASuggestSize(3, block_size);
	void *pool = malloc(size);
	char *allocted_block = NULL;
	char *allocted_block2 = NULL;
	char *allocted_block3 = NULL;
	char *allocted_block4 = NULL;
	assert(159 == size);
	assert(pool && "Malloc faild");
	assert((fsa = FSAInit(pool, size, block_size)));
	assert(3 == FSACountFree(fsa));
	assert((allocted_block = (char *)FSAAlloc(fsa)));
	assert(2 == FSACountFree(fsa));
	assert((allocted_block2 = (char *)FSAAlloc(fsa)));
	assert((strcpy(allocted_block2, "\nFSAAllocTest() : passed.\n")));
	assert(1 == FSACountFree(fsa));
	assert((allocted_block3 = (char *)FSAAlloc(fsa)));
	printf("%s", allocted_block3);
	assert(0 == FSACountFree(fsa));
	assert(NULL == (allocted_block4 = FSAAlloc(fsa)));
	FSAFree(fsa, allocted_block3);
	assert(1 == FSACountFree(fsa));
	FSAFree(fsa, allocted_block2);
	assert(2 == FSACountFree(fsa));
	FSAFree(fsa, allocted_block);
	assert(3 == FSACountFree(fsa));
	free(pool);
}
/*****************************************************************************/
void FSACountFreeTest(void)
{
	fsa_t *fsa = NULL;
	size_t block_size = 48;
	size_t size = FSASuggestSize(3, block_size);
	void *pool = malloc(size);
	char *allocted_block = NULL;
	char *allocted_block2 = NULL;
	char *allocted_block3 = NULL;
	char *allocted_block4 = NULL;
	assert(159 == size);
	assert(pool && "Malloc faild");
	assert((fsa = FSAInit(pool, size, block_size)));
	assert(3 == FSACountFree(fsa));
	assert((allocted_block = (char *)FSAAlloc(fsa)));
	assert(2 == FSACountFree(fsa));
	assert((allocted_block2 = (char *)FSAAlloc(fsa)));
	assert((strcpy(allocted_block2, "\nFSAAllocTest() : passed.\n")));
	printf("%s", allocted_block2);
	assert(1 == FSACountFree(fsa));
	assert((allocted_block3 = (char *)FSAAlloc(fsa)));
	printf("%s", allocted_block3);
	assert(0 == FSACountFree(fsa));
	assert(NULL == (allocted_block4 = FSAAlloc(fsa)));
	free(pool);
}
/*****************************************************************************/
