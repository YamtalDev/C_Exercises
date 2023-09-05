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

    reviewer: Matias Yoel Kaliroff Kravchik.

    date : 23.04.2023

*******************************************************************************

                                 Description:

    The test file provided tests the various functionalities of a binary search 
    tree (BST) data structure implementation. The test cases cover a wide range 
    of scenarios, including creating and destroying a BST, checking if it is empty, 
    comparing iterators, counting nodes, inserting and retrieving data, removing 
    nodes, and finding nodes. The file also includes tests for iterating over 
    the tree, both forwards and backwards. Each test case verifies that the 
    expected behavior is achieved and that the implementation functions 
    correctly according to the specifications of the BST data structure.

******************************************************************************/
#include <stddef.h>  /* size_t, NULL */
#include <assert.h>  /* assert       */
#include <stdio.h>   /* printf       */

#include "bst.h"
/*****************************************************************************/
void BSTCreateDestroyTest(void);
void BSTIsEmptyTest(void);
void BSTIsIterEqualTest(void);
void BSTCountTest(void);
void BSTInsertAndGetDataTest(void);
void BSTRemoveTest(void);
void BSTFindTest(void);
void BSTBeginEndTest(void);
void BSTPrevTest(void);
void BSTNextTest(void);
void BSTForEachTest(void);
int Add(void *data, void *param);
int Cmp(void *data, void *new_data, void *param);
/*****************************************************************************/
int main(void)
{
	BSTCreateDestroyTest();
	puts("\nBSTCreateDestroyTest() : passed.");
	BSTIsEmptyTest();
	puts("\nBSTIsEmptyTest() : passed.");
	BSTIsIterEqualTest();
	puts("\nBSTIsIterEqualTest() : passed.");
	BSTCountTest();
	puts("\nBSTCountTest() : passed.");
	BSTInsertAndGetDataTest();
	puts("\nBSTInsertAndGetDataTest() : passed.");
	BSTRemoveTest();
	puts("\nBSTRemoveTest() : passed.");
	BSTFindTest();
	puts("\nBSTFindTest() : passed.");
	BSTBeginEndTest();
	puts("\nBSTBeginEndTest() : passed.");
	BSTPrevTest();
	puts("\nBSTPrevTest() : passed.");
	BSTNextTest();
	puts("\nBSTNextTest() : passed.");
	BSTForEachTest();
	puts("\nBSTForEachTest() : passed.");
	return (0);
}
/*****************************************************************************/
void BSTCreateDestroyTest(void)
{
	void *param = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTInsertAndGetDataTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	iter = BSTInsert(bst, (void *)13);
	iter2 = BSTInsert(bst, (void *)3);
	iter3 = BSTInsert(bst, (void *)14);
	iter4 = BSTInsert(bst, (void *)18);
	iter5 = BSTInsert(bst, (void *)1);
	iter6 = BSTInsert(bst, (void *)2);
	iter7 = BSTInsert(bst, (void *)4);
	iter8 = BSTInsert(bst, (void *)12);
	iter9 = BSTInsert(bst, (void *)10);
	iter10 = BSTInsert(bst, (void *)11);
	iter11 = BSTInsert(bst, (void *)5);
	iter12 = BSTInsert(bst, (void *)8);
	iter13 = BSTInsert(bst, (void *)9);
	iter14 = BSTInsert(bst, (void *)7);
	iter15 = BSTInsert(bst, (void *)6);
	assert(13 == (long int)BSTGetData(iter));
	assert(3 == (long int)BSTGetData(iter2));
	assert(14 == (long int)BSTGetData(iter3));
	assert(18 == (long int)BSTGetData(iter4));
	assert(1 == (long int)BSTGetData(iter5));
	assert(2 == (long int)BSTGetData(iter6));
	assert(4 == (long int)BSTGetData(iter7));
	assert(12 == (long int)BSTGetData(iter8));
	assert(10 == (long int)BSTGetData(iter9));
	assert(11 == (long int)BSTGetData(iter10));
	assert(5 == (long int)BSTGetData(iter11));
	assert(8 == (long int)BSTGetData(iter12));
	assert(9 == (long int)BSTGetData(iter13));
	assert(7 == (long int)BSTGetData(iter14));
	assert(6 == (long int)BSTGetData(iter15));
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTIsEmptyTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	assert(BSTIsEmpty(bst));
	iter = BSTInsert(bst, (void *)1);
	assert(!BSTIsEmpty(bst));
	iter2 = BSTInsert(bst, (void *)2);
	assert(!BSTIsEmpty(bst));
	(void)iter;
	(void)iter2;
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTCountTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	assert(0 == BSTCount(bst));
	iter = BSTInsert(bst, (void *)13);
	assert(1 == BSTCount(bst));
	iter2 = BSTInsert(bst, (void *)3);
	assert(2 == BSTCount(bst));
	iter3 = BSTInsert(bst, (void *)14);
	assert(3 == BSTCount(bst));
	iter4 = BSTInsert(bst, (void *)18);
	assert(4 == BSTCount(bst));
	iter5 = BSTInsert(bst, (void *)1);
	assert(5 == BSTCount(bst));
	iter6 = BSTInsert(bst, (void *)2);
	assert(6 == BSTCount(bst));
	iter7 = BSTInsert(bst, (void *)4);
	assert(7 == BSTCount(bst));
	iter8 = BSTInsert(bst, (void *)12);
	assert(8 == BSTCount(bst));
	iter9 = BSTInsert(bst, (void *)10);
	assert(9 == BSTCount(bst));
	iter10 = BSTInsert(bst, (void *)11);
	assert(10 == BSTCount(bst));
	iter11 = BSTInsert(bst, (void *)5);
	assert(11 == BSTCount(bst));
	iter12 = BSTInsert(bst, (void *)8);
	assert(12 == BSTCount(bst));
	iter13 = BSTInsert(bst, (void *)9);
	assert(13 == BSTCount(bst));
	iter14 = BSTInsert(bst, (void *)7);
	assert(14 == BSTCount(bst));
	iter15 = BSTInsert(bst, (void *)6);
	assert(15 == BSTCount(bst));
	(void)iter;
	(void)iter2;
	(void)iter3;
	(void)iter4;
	(void)iter5;
	(void)iter6;
	(void)iter7;
	(void)iter8;
	(void)iter9;
	(void)iter10;
	(void)iter11;
	(void)iter12;
	(void)iter12;
	(void)iter13;
	(void)iter14;
	(void)iter15;
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTIsIterEqualTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	iter = BSTInsert(bst, (void *)1);
	assert(BSTIsIterEqual(iter, iter));
	iter2 = BSTInsert(bst, (void *)2);
	assert(!BSTIsIterEqual(iter, iter2));
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTRemoveTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	iter = BSTInsert(bst, (void *)13);
	iter2 = BSTInsert(bst, (void *)3);
	iter3 = BSTInsert(bst, (void *)14);
	iter4 = BSTInsert(bst, (void *)18);
	iter5 = BSTInsert(bst, (void *)1);
	iter6 = BSTInsert(bst, (void *)2);
	iter7 = BSTInsert(bst, (void *)4);
	iter8 = BSTInsert(bst, (void *)12);
	iter9 = BSTInsert(bst, (void *)10);
	iter10 = BSTInsert(bst, (void *)11);
	iter11 = BSTInsert(bst, (void *)5);
	iter12 = BSTInsert(bst, (void *)8);
	iter13 = BSTInsert(bst, (void *)9);
	iter14 = BSTInsert(bst, (void *)7);
	iter15 = BSTInsert(bst, (void *)6);
	assert(13 == (long int)BSTRemove(iter));
	assert(3 == (long int)BSTRemove(iter2));
	assert(14 == (long int)BSTRemove(iter3));
	assert(18 == (long int)BSTRemove(iter4));
	assert(1 == (long int)BSTRemove(iter5));
	assert(2 == (long int)BSTRemove(iter6));
	assert(4 == (long int)BSTRemove(iter7));
	assert(12 == (long int)BSTRemove(iter8));
	assert(10 == (long int)BSTRemove(iter9));
	assert(11 == (long int)BSTRemove(iter10));
	assert(5 == (long int)BSTRemove(iter11));
	assert(8 == (long int)BSTRemove(iter12));
	assert(9 == (long int)BSTRemove(iter13));
	assert(7 == (long int)BSTRemove(iter14));
	assert(6 == (long int)BSTRemove(iter15));
	assert(BSTIsEmpty(bst));
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTFindTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	iter = BSTInsert(bst, (void *)13);
	iter2 = BSTInsert(bst, (void *)3);
	iter3 = BSTInsert(bst, (void *)14);
	iter4 = BSTInsert(bst, (void *)18);
	iter5 = BSTInsert(bst, (void *)1);
	iter6 = BSTInsert(bst, (void *)2);
	iter7 = BSTInsert(bst, (void *)4);
	iter8 = BSTInsert(bst, (void *)12);
	iter9 = BSTInsert(bst, (void *)10);
	iter10 = BSTInsert(bst, (void *)11);
	iter11 = BSTInsert(bst, (void *)5);
	iter12 = BSTInsert(bst, (void *)8);
	iter13 = BSTInsert(bst, (void *)9);
	iter14 = BSTInsert(bst, (void *)7);
	iter15 = BSTInsert(bst, (void *)6);

	assert(iter == BSTFind(bst, (void *)13));
	assert(iter2 == BSTFind(bst, (void *)3));
	assert(iter3 == BSTFind(bst, (void *)14));
	assert(iter4 == BSTFind(bst, (void *)18));
	assert(iter5 == BSTFind(bst, (void *)1));
	assert(iter6 == BSTFind(bst, (void *)2));
	assert(iter7 == BSTFind(bst, (void *)4));
	assert(iter8 == BSTFind(bst, (void *)12));
	assert(iter9 == BSTFind(bst, (void *)10));
	assert(iter10 == BSTFind(bst, (void *)11));
	assert(iter11 == BSTFind(bst, (void *)5));
	assert(iter12 == BSTFind(bst, (void *)8));
	assert(iter13 == BSTFind(bst, (void *)9));
	assert(iter14 == BSTFind(bst, (void *)7));
	assert(iter15 == BSTFind(bst, (void *)6));
	assert(BSTEnd(bst) == BSTFind(bst, (void *)70));
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTBeginEndTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst1 = BSTCreate(Cmp, param);
	assert(bst1);
	iter = BSTInsert(bst1, (void *)13);
	iter2 = BSTInsert(bst1, (void *)3);
	iter3 = BSTInsert(bst1, (void *)14);
	iter4 = BSTInsert(bst1, (void *)18);
	iter5 = BSTInsert(bst1, (void *)1);
	iter6 = BSTInsert(bst1, (void *)2);
	iter7 = BSTInsert(bst1, (void *)4);
	iter8 = BSTInsert(bst1, (void *)12);
	iter9 = BSTInsert(bst1, (void *)10);
	iter10 = BSTInsert(bst1, (void *)11);
	iter11 = BSTInsert(bst1, (void *)5);
	iter12 = BSTInsert(bst1, (void *)8);
	iter13 = BSTInsert(bst1, (void *)9);
	iter14 = BSTInsert(bst1, (void *)7);
	iter15 = BSTInsert(bst1, (void *)6);
	assert(1 == (long int)BSTGetData(BSTBegin(bst1)));
	assert(NULL == BSTGetData(BSTEnd(bst1)));
	(void)iter;
	(void)iter2;
	(void)iter3;
	(void)iter4;
	(void)iter5;
	(void)iter6;
	(void)iter7;
	(void)iter8;
	(void)iter9;
	(void)iter10;
	(void)iter11;
	(void)iter12;
	(void)iter12;
	(void)iter13;
	(void)iter14;
	(void)iter15;
	BSTDestroy(bst1);
	return;
}
/*****************************************************************************/
void BSTPrevTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	iter = BSTInsert(bst, (void *)13);
	iter2 = BSTInsert(bst, (void *)3);
	iter3 = BSTInsert(bst, (void *)14);
	iter4 = BSTInsert(bst, (void *)18);
	iter5 = BSTInsert(bst, (void *)1);
	iter6 = BSTInsert(bst, (void *)2);
	iter7 = BSTInsert(bst, (void *)4);
	iter8 = BSTInsert(bst, (void *)12);
	iter9 = BSTInsert(bst, (void *)10);
	iter10 = BSTInsert(bst, (void *)11);
	iter11 = BSTInsert(bst, (void *)5);
	iter12 = BSTInsert(bst, (void *)8);
	iter13 = BSTInsert(bst, (void *)9);
	iter14 = BSTInsert(bst, (void *)7);
	iter15 = BSTInsert(bst, (void *)6);
	assert(iter8 == BSTPrev(iter));
	assert(iter6 == BSTPrev(iter2));
	assert(iter == BSTPrev(iter3));
	assert(iter3 == BSTPrev(iter4));
	assert(iter5 == BSTPrev(iter6));
	assert(iter2 == BSTPrev(iter7));
	assert(iter10 == BSTPrev(iter8));
	assert(iter13 == BSTPrev(iter9));
	assert(iter9 == BSTPrev(iter10));
	assert(iter7 == BSTPrev(iter11));
	assert(iter14 == BSTPrev(iter12));
	assert(iter12 == BSTPrev(iter13));
	assert(iter15 == BSTPrev(iter14));
	assert(iter11 == BSTPrev(iter15));
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTNextTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	iter = BSTInsert(bst, (void *)13);
	iter2 = BSTInsert(bst, (void *)3);
	iter3 = BSTInsert(bst, (void *)14);
	iter4 = BSTInsert(bst, (void *)18);
	iter5 = BSTInsert(bst, (void *)1);
	iter6 = BSTInsert(bst, (void *)2);
	iter7 = BSTInsert(bst, (void *)4);
	iter8 = BSTInsert(bst, (void *)12);
	iter9 = BSTInsert(bst, (void *)10);
	iter10 = BSTInsert(bst, (void *)11);
	iter11 = BSTInsert(bst, (void *)5);
	iter12 = BSTInsert(bst, (void *)8);
	iter13 = BSTInsert(bst, (void *)9);
	iter14 = BSTInsert(bst, (void *)7);
	iter15 = BSTInsert(bst, (void *)6);
	assert(iter3 == BSTNext(iter));
	assert(iter7 == BSTNext(iter2));
	assert(iter4 == BSTNext(iter3));
	assert(BSTEnd(bst) == BSTNext(iter4));
	assert(iter6 == BSTNext(iter5));
	assert(iter2 == BSTNext(iter6));
	assert(iter11 == BSTNext(iter7));
	assert(iter == BSTNext(iter8));
	assert(iter10 == BSTNext(iter9));
	assert(iter8 == BSTNext(iter10));
	assert(iter15 == BSTNext(iter11));
	assert(iter13 == BSTNext(iter12));
	assert(iter9 == BSTNext(iter13));
	assert(iter12 == BSTNext(iter14));
	assert(iter14 == BSTNext(iter15));
	BSTDestroy(bst);
	return;
}
/*****************************************************************************/
void BSTForEachTest(void)
{
	void *param = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	bst_iter_t iter12 = NULL;
	bst_iter_t iter13 = NULL;
	bst_iter_t iter14 = NULL;
	bst_iter_t iter15 = NULL;
	bst_t *bst = BSTCreate(Cmp, param);
	assert(bst);
	iter = BSTInsert(bst, (void *)13);
	iter2 = BSTInsert(bst, (void *)3);
	iter3 = BSTInsert(bst, (void *)14);
	iter4 = BSTInsert(bst, (void *)18);
	iter5 = BSTInsert(bst, (void *)1);
	iter6 = BSTInsert(bst, (void *)2);
	iter7 = BSTInsert(bst, (void *)4);
	iter8 = BSTInsert(bst, (void *)12);
	iter9 = BSTInsert(bst, (void *)10);
	iter10 = BSTInsert(bst, (void *)11);
	iter11 = BSTInsert(bst, (void *)5);
	iter12 = BSTInsert(bst, (void *)8);
	iter13 = BSTInsert(bst, (void *)9);
	iter14 = BSTInsert(bst, (void *)7);
	iter15 = BSTInsert(bst, (void *)6);
	assert(0 == BSTForEach(bst, Add, (void *)1));
	assert(14 == (long int)BSTGetData(iter));
	assert(4 == (long int)BSTGetData(iter2));
	assert(15 == (long int)BSTGetData(iter3));
	assert(19 == (long int)BSTGetData(iter4));
	assert(2 == (long int)BSTGetData(iter5));
	assert(3 == (long int)BSTGetData(iter6));
	assert(5 == (long int)BSTGetData(iter7));
	assert(13 == (long int)BSTGetData(iter8));
	assert(11 == (long int)BSTGetData(iter9));
	assert(12 == (long int)BSTGetData(iter10));
	assert(6 == (long int)BSTGetData(iter11));
	assert(9 == (long int)BSTGetData(iter12));
	assert(10 == (long int)BSTGetData(iter13));
	assert(8 == (long int)BSTGetData(iter14));
	assert(7 == (long int)BSTGetData(iter15));
	assert(0 == BSTForEach(bst, Add, (void *)-1));
	assert(13 == (long int)BSTGetData(iter));
	assert(3 == (long int)BSTGetData(iter2));
	assert(14 == (long int)BSTGetData(iter3));
	assert(18 == (long int)BSTGetData(iter4));
	assert(1 == (long int)BSTGetData(iter5));
	assert(2 == (long int)BSTGetData(iter6));
	assert(4 == (long int)BSTGetData(iter7));
	assert(12 == (long int)BSTGetData(iter8));
	assert(10 == (long int)BSTGetData(iter9));
	assert(11 == (long int)BSTGetData(iter10));
	assert(5 == (long int)BSTGetData(iter11));
	assert(8 == (long int)BSTGetData(iter12));
	assert(9 == (long int)BSTGetData(iter13));
	assert(7 == (long int)BSTGetData(iter14));
	assert(6 == (long int)BSTGetData(iter15));
	BSTDestroy(bst);
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
