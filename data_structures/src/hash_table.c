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

    Reviewer: Yotam itzhak Peled.

    Date: 09.05.2023

*******************************************************************************

                                Description:

  The code defines a hash_table_t struct with a capacity, an array of doubly 
  linked lists (dll_t), and function pointers for hash and comparison operations. 
  Functions are provided to create and destroy a hash table, insert and remove 
  elements, find elements, iterate over elements, and retrieve information such 
  as size, load factor, and standard deviation. The hash table uses the provided 
  hash function to determine the index of the array where an element should be 
  stored and the comparison function to handle collisions. The implementation 
  ensures that each array element is a doubly linked list to handle collisions 
  by chaining elements. The code also includes internal helper functions for 
  iterator management and checking the existence of an element in the hash table.

******************************************************************************/
#include <stdlib.h>     /* malloc, free */
#include <math.h>       /* sqrt, pow    */
#include <assert.h>     /* assert       */


#include "dll.h"        /* Internal API */
#include "hash_table.h" /* Internal API */
/*****************************************************************************/
struct table
{
    hash_cmp_func_t cmp;
    hash_func_t hash;
    size_t capacity;
    dll_t **array;
};
/*****************************************************************************/
#define KEY(X,Y) (Y->hash(X) % Y->capacity)
static int HashTableIsIteratorFound(const hash_table_t *, const void *, dll_iter_t *);
/*****************************************************************************/
hash_table_t *HashTableCreate(size_t size, hash_func_t hash, hash_cmp_func_t cmp)
{
    size_t length = sizeof(hash_table_t) + size * sizeof(dll_t *);
    hash_table_t *table = (hash_table_t *)calloc(length, sizeof(void *));
    if(NULL == table)
        return (NULL);

    assert(cmp);
    assert(hash);
    table->cmp = cmp;
    table->hash = hash;
    table->capacity = size;
    table->array = (dll_t **)(table + 1);

    return (table);
}
/*****************************************************************************/
void HashTableDestroy(hash_table_t *table)
{
    size_t i = 0;
    size_t size = 0;
    dll_t *dll = NULL;
    if(NULL == table)
        return;

    size = table->capacity;
    for(; i < size; ++i)
    {
        dll = table->array[i];
        if(NULL != dll)
            DLLDestroy(dll);
    }

    free(table);
    table = NULL;
}
/*****************************************************************************/
void HashTableRemove(hash_table_t *table, const void *value)
{
    dll_iter_t iterator = (dll_iter_t)0;
    assert(table && "Table is not valid.");
    if(FAILURE != HashTableIsIteratorFound(table, value, &iterator))
        DLLRemove(iterator);
}
/*****************************************************************************/
int HashTableInsert(hash_table_t *table, void *value)
{
    size_t key = 0;
    dll_iter_t iterator = (dll_iter_t)0;
    assert(table && "Table is not valid.");

    key = KEY(value, table);
    if(NULL == table->array[key])
        if(NULL == (table->array[key] = DLLCreate()))
            return (FAILURE);

    iterator = DLLPushFront(table->array[key], value);
    return (DLLIterIsEqual(iterator, DLLEnd(table->array[key])));
}
/*****************************************************************************/
size_t HashTableSize(const hash_table_t *table)
{
    size_t i = 0;
    size_t size = 0;
    size_t number_of_elements = 0;
    assert(table && "Table is not valid.");

    size = table->capacity;
    for(; i < size; ++i)
    {
        if(NULL != table->array[i])
            number_of_elements += DLLCount(table->array[i]);
    }

    return (number_of_elements);
}
/*****************************************************************************/
int HashTableIsEmpty(const hash_table_t *table)
{
    assert(table);
    return (0 == HashTableSize(table));
}
/*****************************************************************************/
void *HashTableFind(const hash_table_t *table, const void *value)
{
    int status = SUCCESS;
    dll_iter_t iterator = (dll_iter_t)0;
    assert(table && "Table is not valid.");
    status = HashTableIsIteratorFound(table, value, &iterator);
    return (SUCCESS == status ? DLLGetData(iterator) : NULL);
}
/*****************************************************************************/
int HashTableForEach(hash_table_t *table, hash_action_func_t act, void *param)
{
    size_t i = 0;
    size_t size = 0;
    int status = SUCCESS;
    dll_iter_t end = (dll_iter_t)0;
    dll_iter_t start = (dll_iter_t)0;
    assert(table && "Table is not valid.");

    size = table->capacity;
    do
    {
        if(NULL != table->array[i])
        {
            end = DLLEnd(table->array[i]);
            start = DLLBegin(table->array[i]);
            status = DLLForEach(start, end, act, param);
        }

    } while(SUCCESS != status && ++i < size);

    return (status);
}
/*****************************************************************************/
double HashTableLoadFactor(const hash_table_t *table)
{
    size_t i = 0;
    size_t size = 0;
    double number_of_keys = 0;
    assert(table && "Table is not valid.");

    size = table->capacity;
    for(; i < size; number_of_keys += NULL == table->array[i] ? 0 : 1, ++i);

    return (number_of_keys / (double)size);
}
/*****************************************************************************/
double HashTableSD(const hash_table_t *table)
{
    size_t i = 0;
    size_t size = 0;
    double mean = 0.0;
    double variance = 0.0;
    double bucket_size = 0.0;
    double used_buckets = 0.0;
    double number_of_elements = 0.0;
    assert(table && "Table is not valid.");

    size = table->capacity;
    for(; i < size; ++i)
    {
        if(NULL != table->array[i])
        {
            bucket_size = DLLCount(table->array[i]);
            number_of_elements += bucket_size;
            variance += pow(bucket_size, 2);
            ++used_buckets;
        }
    }

    mean = number_of_elements / used_buckets;
    variance = (variance / used_buckets) - pow(mean, 2);
    return (sqrt(variance));
}
/*****************************************************************************/
static int HashTableIsIteratorFound
(const hash_table_t *table, const void *value, dll_iter_t *iterator)
{
    size_t key = 0;
    int status = SUCCESS;
    dll_iter_t end = NULL;
    dll_iter_t start = NULL;
    assert(table && "Table is not valid.");

    key = KEY(value, table);
    if(NULL != table->array[key])
    {
        end = DLLEnd(table->array[key]);
        start = DLLBegin(table->array[key]);
        *iterator = DLLFind(start, end, table->cmp, (void *)value);
        status = DLLIterIsEqual(end, *iterator);
    }

    return (status);
}
/*****************************************************************************/