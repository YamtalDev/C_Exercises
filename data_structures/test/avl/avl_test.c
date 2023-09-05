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

    Writer: Tal Aharon

    Reviewer: Nir Halperin.

    Date: 06.05.2023

*******************************************************************************

                              Description:

    This code is a test suite for an AVL tree implementation. It includes 
    multiple test functions to assess the functionality and correctness of 
    various operations on the AVL tree. The tests cover functions such as 
    AVLCreateDestroy, AVLInsertRemove, AVLHeight, AVLCount, AVLIsEmpty, 
    AVLFind, and AVLForEach. Each test function performs a specific set 
    of operations on the AVL tree and asserts the expected results.

******************************************************************************/
#include <stdio.h>   /* printf, puts */
#include <stddef.h>  /* size_t, NULL */
#include <assert.h>  /* assert       */
#include <stdlib.h>  /*              */

#include "avl.h"     /* Internal API */
/*****************************************************************************/
void AVLFindTest(void);
int Add(void *, void *);
void AVLCountTest(void);
void MultiFindTest(void);
void AVLHeightTest(void);
void AVLIsEmptyTest(void);
void AVLForEachTest(void);
int AddFail(void *, void *);
void RemoveMultipleTest(void);
void AVLInsertRemoveTest(void);
int Cmp(void *, void *, void *);
void AVLCreateDestroyTest(void);
/*****************************************************************************/
int main(void)
{
	AVLCreateDestroyTest();
	puts("\nAVLCreateRemoveTest() : passed.");
	AVLInsertRemoveTest();
	puts("\nAVLInsertRemoveTest() : passed.");
	AVLHeightTest();
	puts("\nAVLHeightTest() : passed.");
	AVLCountTest();
	puts("\nAVLCountTest() : passed.");
	AVLIsEmptyTest();
	puts("\nAVLIsEmptyTest() : passed.");
	AVLFindTest();
	puts("\nAVLFindTest() : passed.");
	AVLForEachTest();
	puts("\nAVLForEachTest() : passed.");
	MultiFindTest();
	puts("\nMultiFindTest() : passed.");
	RemoveMultipleTest();
	puts("\nRemoveMultipleTest() : passed.");
	return (0);
}
/*****************************************************************************/
void AVLCreateDestroyTest(void)
{
	void *param = NULL;
	avl_t *avl = AVLCreate(Cmp, param);
	assert(avl);
	AVLDestroy(avl);
}
/*****************************************************************************/
void AVLInsertRemoveTest(void)
{
	void *param = NULL;
	avl_t *avl = AVLCreate(Cmp, param);
	assert(avl);
	assert(0 == AVLInsert(avl, (void *)13));
	assert(0 == AVLInsert(avl, (void *)3));
	assert(0 == AVLInsert(avl, (void *)14));
	assert(0 == AVLInsert(avl, (void *)18));
	assert(0 == AVLInsert(avl, (void *)1));
	assert(0 == AVLInsert(avl, (void *)2));
	assert(0 == AVLInsert(avl, (void *)4));
	assert(0 == AVLInsert(avl, (void *)12));
	assert(0 == AVLInsert(avl, (void *)10));
	assert(0 == AVLInsert(avl, (void *)11));
	assert(0 == AVLInsert(avl, (void *)5));
	assert(0 == AVLInsert(avl, (void *)8));
	assert(0 == AVLInsert(avl, (void *)9));
	assert(0 == AVLInsert(avl, (void *)7));
	assert(0 == AVLInsert(avl, (void *)6));
	assert(13 == (size_t)AVLRemove(avl, (void *)13));
	assert(3 == (size_t)AVLRemove(avl, (void *)3));
	assert(14 == (size_t)AVLRemove(avl, (void *)14));
	assert(18 == (size_t)AVLRemove(avl, (void *)18));
	assert(1 == (size_t)AVLRemove(avl, (void *)1));
	assert(2 == (size_t)AVLRemove(avl, (void *)2));
	assert(4 == (size_t)AVLRemove(avl, (void *)4));
	assert(12 == (size_t)AVLRemove(avl, (void *)12));
	assert(10 == (size_t)AVLRemove(avl, (void *)10));
	assert(11 == (size_t)AVLRemove(avl, (void *)11));
	assert(5 == (size_t)AVLRemove(avl, (void *)5));
	assert(8 == (size_t)AVLRemove(avl, (void *)8));
	assert(9 == (size_t)AVLRemove(avl, (void *)9));
	assert(7 == (size_t)AVLRemove(avl, (void *)7));
	assert(6 == (size_t)AVLRemove(avl, (void *)6));
	assert(NULL == AVLRemove(avl, (void *)100));
	assert(NULL == AVLRemove(avl, (void *)130));
	assert(NULL == AVLRemove(avl, (void *)450));
	AVLDestroy(avl);
}
/*****************************************************************************/
void AVLHeightTest(void)
{
	void *param = NULL;
	avl_t *avl = AVLCreate(Cmp, param);
	assert(avl);
	assert(0 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)13));
	assert(1 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)3));
	assert(2 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)14));
	assert(2 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)18));
	assert(3 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)1));
	assert(3 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)2));
	assert(3 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)4));
	assert(4 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)12));
	assert(4 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)10));
	assert(4 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)11));
	assert(4 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)5));
	assert(4 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)8));
	assert(4 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)9));
	assert(5 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)7));
	assert(5 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, (void *)6));
	assert(5 == AVLHeight(avl));
	AVLDestroy(avl);
}
/*****************************************************************************/
void AVLCountTest(void)
{
	void *param = NULL;
	avl_t *avl = AVLCreate(Cmp, param);
	assert(avl);
	assert(0 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)13));
	assert(1 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)3));
	assert(2 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)14));
	assert(3 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)18));
	assert(4 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)1));
	assert(5 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)2));
	assert(6 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)4));
	assert(7 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)12));
	assert(8 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)10));
	assert(9 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)11));
	assert(10 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)5));
	assert(11 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)8));
	assert(12 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)9));
	assert(13 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)7));
	assert(14 == AVLCount(avl));
	assert(0 == AVLInsert(avl, (void *)6));
	assert(15 == AVLCount(avl));
	AVLRemove(avl, (void *)13);
	assert(14 == AVLCount(avl));
	AVLRemove(avl, (void *)3);
	assert(13 == AVLCount(avl));
	AVLRemove(avl, (void *)14);
	assert(12 == AVLCount(avl));
	AVLRemove(avl, (void *)18);
	assert(11 == AVLCount(avl));
	AVLRemove(avl, (void *)1);
	assert(10 == AVLCount(avl));
	AVLRemove(avl, (void *)2);
	assert(9 == AVLCount(avl));
	AVLRemove(avl, (void *)4);
	assert(8 == AVLCount(avl));
	AVLRemove(avl, (void *)12);
	assert(7 == AVLCount(avl));
	AVLRemove(avl, (void *)10);
	assert(6 == AVLCount(avl));
	AVLRemove(avl, (void *)11);
	assert(5 == AVLCount(avl));
	AVLRemove(avl, (void *)5);
	assert(4 == AVLCount(avl));
	AVLRemove(avl, (void *)8);
	assert(3 == AVLCount(avl));
	AVLRemove(avl, (void *)9);
	assert(2 == AVLCount(avl));
	AVLRemove(avl, (void *)7);
	assert(1 == AVLCount(avl));
	AVLRemove(avl, (void *)6);
	assert(0 == AVLCount(avl));
	AVLDestroy(avl);
}
/*****************************************************************************/
void AVLIsEmptyTest(void)
{
	void *param = NULL;
	avl_t *avl = AVLCreate(Cmp, param);
	assert(avl);
	assert(AVLIsEmpty(avl));
	assert(0 == AVLInsert(avl, (void *)13));
	assert(!AVLIsEmpty(avl));
	assert(0 == AVLInsert(avl, (void *)3));
	assert(!AVLIsEmpty(avl));
	assert(0 == AVLInsert(avl, (void *)14));
	assert(!AVLIsEmpty(avl));
	AVLRemove(avl, (void *)13);
	AVLRemove(avl, (void *)3);
	AVLRemove(avl, (void *)14);
	assert(AVLIsEmpty(avl));
	AVLDestroy(avl);
}
/*****************************************************************************/
void AVLFindTest(void)
{
	void *param = NULL;
	avl_t *avl = AVLCreate(Cmp, param);
	assert(avl);
	assert(0 == AVLInsert(avl, (void *)13));
	assert(0 == AVLInsert(avl, (void *)3));
	assert(0 == AVLInsert(avl, (void *)14));
	assert(0 == AVLInsert(avl, (void *)18));
	assert(0 == AVLInsert(avl, (void *)1));
	assert(0 == AVLInsert(avl, (void *)2));
	assert(0 == AVLInsert(avl, (void *)4));
	assert(0 == AVLInsert(avl, (void *)12));
	assert(0 == AVLInsert(avl, (void *)10));
	assert(0 == AVLInsert(avl, (void *)11));
	assert(0 == AVLInsert(avl, (void *)5));
	assert(0 == AVLInsert(avl, (void *)8));
	assert(0 == AVLInsert(avl, (void *)9));
	assert(0 == AVLInsert(avl, (void *)7));
	assert(0 == AVLInsert(avl, (void *)6));
	assert(13 == (size_t)AVLFind(avl, (void *)13));
	assert(3 == (size_t)AVLFind(avl, (void *)3));
	assert(14 == (size_t)AVLFind(avl, (void *)14));
	assert(18 == (size_t)AVLFind(avl, (void *)18));
	assert(1 == (size_t)AVLFind(avl, (void *)1));
	assert(2 == (size_t)AVLFind(avl, (void *)2));
	assert(4 == (size_t)AVLFind(avl, (void *)4));
	assert(12 == (size_t)AVLFind(avl, (void *)12));
	assert(10 == (size_t)AVLFind(avl, (void *)10));
	assert(11 == (size_t)AVLFind(avl, (void *)11));
	assert(5 == (size_t)AVLFind(avl, (void *)5));
	assert(8 == (size_t)AVLFind(avl, (void *)8));
	assert(9 == (size_t)AVLFind(avl, (void *)9));
	assert(7 == (size_t)AVLFind(avl, (void *)7));
	assert(6 == (size_t)AVLFind(avl, (void *)6));
	assert(NULL == AVLFind(avl, (void *)100));
	assert(NULL == AVLFind(avl, (void *)130));
	assert(NULL == AVLFind(avl, (void *)450));
	AVLDestroy(avl);
}
/*****************************************************************************/
void AVLForEachTest(void)
{
	void *param = NULL;
	avl_t *avl = AVLCreate(Cmp, param);
	avl_t *avl1 = AVLCreate(Cmp, param);
	avl_t *avl2 = AVLCreate(Cmp, param);
	assert(avl);
	assert(avl1);
	assert(avl2);
	assert(0 == AVLInsert(avl, (void *)13));
	assert(0 == AVLInsert(avl, (void *)3));
	assert(0 == AVLInsert(avl, (void *)14));
	assert(0 == AVLInsert(avl, (void *)18));
	assert(0 == AVLInsert(avl, (void *)1));
	assert(0 == AVLInsert(avl, (void *)2));
	assert(0 == AVLInsert(avl, (void *)4));
	assert(0 == AVLInsert(avl, (void *)12));
	assert(0 == AVLInsert(avl, (void *)10));
	assert(0 == AVLInsert(avl, (void *)11));
	assert(0 == AVLInsert(avl, (void *)5));
	assert(0 == AVLInsert(avl, (void *)8));
	assert(0 == AVLInsert(avl, (void *)9));
	assert(0 == AVLInsert(avl, (void *)7));
	assert(0 == AVLInsert(avl, (void *)6));

	assert(0 == AVLInsert(avl1, (void *)13));
	assert(0 == AVLInsert(avl1, (void *)3));
	assert(0 == AVLInsert(avl1, (void *)14));
	assert(0 == AVLInsert(avl1, (void *)18));
	assert(0 == AVLInsert(avl1, (void *)1));
	assert(0 == AVLInsert(avl1, (void *)2));
	assert(0 == AVLInsert(avl1, (void *)4));
	assert(0 == AVLInsert(avl1, (void *)12));
	assert(0 == AVLInsert(avl1, (void *)10));
	assert(0 == AVLInsert(avl1, (void *)11));
	assert(0 == AVLInsert(avl1, (void *)5));
	assert(0 == AVLInsert(avl1, (void *)8));
	assert(0 == AVLInsert(avl1, (void *)9));
	assert(0 == AVLInsert(avl1, (void *)7));
	assert(0 == AVLInsert(avl1, (void *)6));

	assert(0 == AVLInsert(avl2, (void *)13));
	assert(0 == AVLInsert(avl2, (void *)3));
	assert(0 == AVLInsert(avl2, (void *)14));
	assert(0 == AVLInsert(avl2, (void *)18));
	assert(0 == AVLInsert(avl2, (void *)1));
	assert(0 == AVLInsert(avl2, (void *)2));
	assert(0 == AVLInsert(avl2, (void *)4));
	assert(0 == AVLInsert(avl2, (void *)12));
	assert(0 == AVLInsert(avl2, (void *)10));
	assert(0 == AVLInsert(avl2, (void *)11));
	assert(0 == AVLInsert(avl2, (void *)5));
	assert(0 == AVLInsert(avl2, (void *)8));
	assert(0 == AVLInsert(avl2, (void *)9));
	assert(0 == AVLInsert(avl2, (void *)7));
	assert(0 == AVLInsert(avl2, (void *)6));

	assert(0 == AVLForEach(avl, Add, (void *)1, POST_ORDER));

	assert(13 + 1 == (size_t)AVLFind(avl, (void *)(13 + 1)));
	assert(3 + 1 == (size_t)AVLFind(avl, (void *)(3 + 1)));
	assert(14 + 1 == (size_t)AVLFind(avl, (void *)(14 + 1)));
	assert(18 + 1 == (size_t)AVLFind(avl, (void *)(18 + 1)));
	assert(1 + 1 == (size_t)AVLFind(avl, (void *)(1 + 1)));
	assert(2 + 1 == (size_t)AVLFind(avl, (void *)(2 + 1)));
	assert(4 + 1 == (size_t)AVLFind(avl, (void *)(4 + 1)));
	assert(12 + 1 == (size_t)AVLFind(avl, (void *)(12 + 1)));
	assert(10 + 1 == (size_t)AVLFind(avl, (void *)(10 + 1)));
	assert(11 + 1 == (size_t)AVLFind(avl, (void *)(11 + 1)));
	assert(5 + 1 == (size_t)AVLFind(avl, (void *)(5 + 1)));
	assert(8 + 1 == (size_t)AVLFind(avl, (void *)(8 + 1)));
	assert(9 + 1 == (size_t)AVLFind(avl, (void *)(9 + 1)));
	assert(7 + 1 == (size_t)AVLFind(avl, (void *)(7 + 1)));
	assert(6 + 1 == (size_t)AVLFind(avl, (void *)(6 + 1)));

	assert(0 == AVLForEach(avl1, Add, (void *)1, PRE_ORDER));

	assert(13 + 1 == (size_t)AVLFind(avl1, (void *)(13 + 1)));
	assert(3 + 1 == (size_t)AVLFind(avl1, (void *)(3 + 1)));
	assert(14 + 1 == (size_t)AVLFind(avl1, (void *)(14 + 1)));
	assert(18 + 1 == (size_t)AVLFind(avl1, (void *)(18 + 1)));
	assert(1 + 1 == (size_t)AVLFind(avl1, (void *)(1 + 1)));
	assert(2 + 1 == (size_t)AVLFind(avl1, (void *)(2 + 1)));
	assert(4 + 1 == (size_t)AVLFind(avl1, (void *)(4 + 1)));
	assert(12 + 1 == (size_t)AVLFind(avl1, (void *)(12 + 1)));
	assert(10 + 1 == (size_t)AVLFind(avl1, (void *)(10 + 1)));
	assert(11 + 1 == (size_t)AVLFind(avl1, (void *)(11 + 1)));
	assert(5 + 1 == (size_t)AVLFind(avl1, (void *)(5 + 1)));
	assert(8 + 1 == (size_t)AVLFind(avl1, (void *)(8 + 1)));
	assert(9 + 1 == (size_t)AVLFind(avl1, (void *)(9 + 1)));
	assert(7 + 1 == (size_t)AVLFind(avl1, (void *)(7 + 1)));
	assert(6 + 1 == (size_t)AVLFind(avl1, (void *)(6 + 1)));

	assert(0 == AVLForEach(avl2, Add, (void *)1, IN_ORDER));

	assert(13 + 1 == (size_t)AVLFind(avl2, (void *)(13 + 1)));
	assert(3 + 1 == (size_t)AVLFind(avl2, (void *)(3 + 1)));
	assert(14 + 1 == (size_t)AVLFind(avl2, (void *)(14 + 1)));
	assert(18 + 1 == (size_t)AVLFind(avl2, (void *)(18 + 1)));
	assert(1 + 1 == (size_t)AVLFind(avl2, (void *)(1 + 1)));
	assert(2 + 1 == (size_t)AVLFind(avl2, (void *)(2 + 1)));
	assert(4 + 1 == (size_t)AVLFind(avl2, (void *)(4 + 1)));
	assert(12 + 1 == (size_t)AVLFind(avl2, (void *)(12 + 1)));
	assert(10 + 1 == (size_t)AVLFind(avl2, (void *)(10 + 1)));
	assert(11 + 1 == (size_t)AVLFind(avl2, (void *)(11 + 1)));
	assert(5 + 1 == (size_t)AVLFind(avl2, (void *)(5 + 1)));
	assert(8 + 1 == (size_t)AVLFind(avl2, (void *)(8 + 1)));
	assert(9 + 1 == (size_t)AVLFind(avl2, (void *)(9 + 1)));
	assert(7 + 1 == (size_t)AVLFind(avl2, (void *)(7 + 1)));
	assert(6 + 1 == (size_t)AVLFind(avl2, (void *)(6 + 1)));

	assert(1 == AVLForEach(avl2, AddFail, (void *)1, IN_ORDER));
	assert(3 == (size_t)AVLFind(avl2, (void *)3));
	assert(NULL == AVLFind(avl2, (void *)20));

	AVLDestroy(avl);
	AVLDestroy(avl1);
	AVLDestroy(avl2);
}
/*****************************************************************************/
void MultiFindTest(void)
{
	return;
}
/*****************************************************************************/
void RemoveMultipleTest(void)
{
	return;
}
/*****************************************************************************/
int Cmp(void *data, void *new_data, void *param)
{
	(void)param;
	return ((size_t)data - (size_t)new_data);
}
/*****************************************************************************/
int Add(void *data, void *param)
{
	*(long int *)data += (long int)param;
	return 0;
}
/*****************************************************************************/
int AddFail(void *data, void *param)
{
	*(long int *)data += (long int)param;
	return 1;
}
/*****************************************************************************/
