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

    reviewer: [First name, family]

    date : dd.mm.yyyy

    Description:

******************************************************************************/
#include <stdio.h>   /* printf, puts */
#include <assert.h>  /*   assert     */
#include <stdlib.h>  /* malloc, free */
#include <string.h>  /* strcpy       */

#include "vsa.h"
void VSAInitTest(void);
void VSAAllocTest(void);
void VSAFreeTest(void);
void VSALargestChunkAvailableTest(void);

/*****************************************************************************/
int main(void)
{
	VSAInitTest();
	puts("\nVSAInitTest() : passed.");
	VSAAllocTest();
	VSAFreeTest();
	puts("\nVSAFreeTest() : passed.");
	VSALargestChunkAvailableTest();
	puts("\nVSALargestChunkAvailableTest() : passed.\n\n");
	return (0);
}
/*****************************************************************************/
void VSAInitTest(void)
{
	size_t size = 100;
	vsa_t *vsa = NULL;
	void *pool = malloc(size);
	assert(pool);
	vsa = VSAInit(pool, size);
	assert(vsa);
	free(pool);
	pool = NULL;
}
/*****************************************************************************/
void VSAAllocTest(void)
{
	size_t size = 150;
	vsa_t *vsa = NULL;
	char *str = NULL;
	char *str2 = NULL;
	char *str3 = NULL;
	char *str4 = NULL;
	char *str5 = NULL;
	char *str6 = NULL;
	char *str7 = NULL;
	void *pool = malloc(size);
	assert(pool);
	vsa = VSAInit(pool, size);
	assert(vsa);
	str = (char *)VSAAlloc(vsa, 50);
	assert(str);
	str2 = (char *)VSAAlloc(vsa, 10);
	assert(str2);
	str3 = (char *)VSAAlloc(vsa, 0);
	assert(NULL == str3);
	str4 = (char *)VSAAlloc(vsa, 220);
	assert(NULL == str4);
	str5 = (char *)VSAAlloc(vsa, 10);
	assert(str5);
	str6 = (char *)VSAAlloc(vsa, 80);
	assert(NULL == str6);
	str7 = (char *)VSAAlloc(vsa, 10);
	assert(NULL == str7);
	strcpy(str, "\nVSAAllocTest() : passed, ");
	printf("%s", str);
	strcpy(str2, "yay!\n");
	printf("%s", str2);
	free(pool);
	pool = NULL;
}
/*****************************************************************************/
void VSAFreeTest(void)
{
	size_t size = 150;
	vsa_t *vsa = NULL;
	char *str = NULL;
	char *str2 = NULL;
	char *str3 = NULL;
	char *str4 = NULL;
	char *str5 = NULL;
	char *str6 = NULL;
	char *str7 = NULL;
	char *str8 = NULL;
	void *pool = malloc(size);
	assert(pool);
	vsa = VSAInit(pool, size);
	assert(vsa);
	str = (char *)VSAAlloc(vsa, 50);
	assert(str);
	str2 = (char *)VSAAlloc(vsa, 10);
	assert(str2);
	str3 = (char *)VSAAlloc(vsa, 0);
	assert(NULL == str3);
	str4 = (char *)VSAAlloc(vsa, 220);
	assert(NULL == str4);
	str5 = (char *)VSAAlloc(vsa, 10);
	assert(str5);
	str6 = (char *)VSAAlloc(vsa, 80);
	assert(NULL == str6);
	str7 = (char *)VSAAlloc(vsa, 10);
	assert(NULL == str7);
	strcpy(str, "\nVSAAllocTest() : passed, ");
	strcpy(str2, "yay!\n");
	VSAFree(str);
	VSAFree(str2);
	VSAFree(str3);
	VSAFree(str4);
	VSAFree(str5);
	VSAFree(str6);
	VSAFree(str7);
	str8 = (char *)VSAAlloc(vsa, 150);
	assert(NULL == str8);
	VSAFree(str8);
	str7 = (char *)VSAAlloc(vsa, 100);
	assert(str7);
	free(pool);
	pool = NULL;
}
/*****************************************************************************/
void VSALargestChunkAvailableTest(void)
{
    size_t size = 150;
    vsa_t *vsa = NULL;
    char *str = NULL;
    char *str2 = NULL;
    char *str3 = NULL;
    char *str4 = NULL;
    char *str5 = NULL;
    void *pool = malloc(size);
    assert(pool);
    vsa = VSAInit(pool, size);
    assert(vsa);
    assert(120 == VSALargestChunkAvailable(vsa));
    str = (char *)VSAAlloc(vsa, 50);
    assert(str);
    assert(48 == VSALargestChunkAvailable(vsa));
    str2 = (char *)VSAAlloc(vsa, 10);
    assert(str2);
    assert(16 == VSALargestChunkAvailable(vsa));
    str3 = (char *)VSAAlloc(vsa, 50);
    assert(NULL == str3);
    assert(16 == VSALargestChunkAvailable(vsa));
    str4 = (char *)VSAAlloc(vsa, 0);
    assert(NULL == str4);
    assert(16 == VSALargestChunkAvailable(vsa));
    str5 = (char *)VSAAlloc(vsa, 10);
    assert(str5);
    assert(0 == VSALargestChunkAvailable(vsa));
    VSAFree(str);
    assert(56 == VSALargestChunkAvailable(vsa));
    VSAFree(str5);
    assert(56 == VSALargestChunkAvailable(vsa));
    VSAFree(str3);
    assert(56 == VSALargestChunkAvailable(vsa));
    VSAFree(str4);
    assert(56 == VSALargestChunkAvailable(vsa));
    VSAFree(str2);
    assert(120 == VSALargestChunkAvailable(vsa));
    free(pool);
    pool = NULL;
}
/*****************************************************************************/
