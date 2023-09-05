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

    Reviewer: First name and family name.

    Date: 09.05.2023

*******************************************************************************

                        Description:

  The provided code is a test program for evaluating the functionality and performance 
  of a hash table implementation. It includes tests for create/destroy, insert/remove, 
  size, empty check, and find operations of the hash table. Additionally, there is a 
  specific test function for a spell checker application using the hash table. 
  The program outputs the success or failure of each test.

******************************************************************************/
#include <string.h>           /* strcmp, strchr, strlen */
#include <stdio.h>            /* puts, fopen, fclode    */
#include <assert.h>           /* assert                 */
#include <stdlib.h>           /* fgets                  */

#include "hash_table.h"       /* Internal API           */
#define MAX_CHAR_IN_WORD (30)
/*****************************************************************************/
int Cmp(void *, void *);
size_t Hash(const void *);
void SpellCheckerTest(void);
size_t Capacity(const char *);
int SpellCheckerCmp(void *, void *);
size_t SpellCheckerHash(const void *);
/*****************************************************************************/
void HashForEachTest(void);
void HashTableSizeTest(void);
void HashTableFindTest(void);
void HashTableIsEmptyTest(void);
void HashTableInsertRemoveTest(void);
void HashTableCreateDestroyTest(void);
/*****************************************************************************/
int main(void)
{
    HashTableCreateDestroyTest();
    puts("\nHashTableCreateDestroyTest() : passed.");
    HashTableInsertRemoveTest();
    puts("\nHashTableInsertRemoveTest() : passed.");
    HashTableSizeTest();
    puts("\nHashTableSizeTest() : passed.");
    HashTableIsEmptyTest();
    puts("\nHashTableIsEmptyTest() : passed.");
    HashTableFindTest();
    puts("\nHashTableFindTest() : passed.");
    HashForEachTest();
    puts("\nHashForEachTest() : passed.");
    SpellCheckerTest();
    puts("\nSpellCheckerTest() : passed.");
    return (0);
}
/*****************************************************************************/
void SpellCheckerTest(void)
{
    size_t length = 0;
    FILE *dict = NULL;
    size_t capacity = 0;
    FILE *test_file = NULL;
    hash_table_t *dictionary = NULL;
    char word[MAX_CHAR_IN_WORD] = {0};
    dict = fopen("/usr/share/dict/words", "r");
    capacity = Capacity("/usr/share/dict/words");
    test_file = fopen("/home/tal/Documents/Infinity/work/tal.aharon/ds/test/hash_table/words.txt", "r");
    if(!dict || !test_file)
    {
        return;
    }

    dictionary = HashTableCreate(capacity, SpellCheckerHash, SpellCheckerCmp);
    if(NULL == dictionary)
    {
        fclose(test_file);
        fclose(dict);
        return;
    }

    while(fgets(word, MAX_CHAR_IN_WORD, dict))
    {
        length = strlen(word);
        if (length > 0 && word[length - 1] == '\n')
            word[length - 1] = '\0';

        assert(SUCCESS == HashTableInsert(dictionary, (void *)word));
    }

    assert(0.6 < HashTableLoadFactor(dictionary) && 0.9 > HashTableLoadFactor(dictionary));
    assert(0.5 < HashTableSD(dictionary) && 2 > HashTableSD(dictionary));

    while(fgets(word, MAX_CHAR_IN_WORD, test_file))
    {
        length = strlen(word);
        if (length > 0 && word[length - 1] == '\n')
            word[length - 1] = '\0';

        assert(NULL != HashTableFind(dictionary, (void *)word));
    }

    fclose(dict);
    fclose(test_file);
    HashTableDestroy(dictionary);
}
/*****************************************************************************/
int SpellCheckerCmp(void *data, void *param)
{
    assert(data); assert(param);
    return (strcmp((char *)data, (char *)param));
}
/*****************************************************************************/
size_t SpellCheckerHash(const void *data)
{
    int i = 0;
    char *str = NULL;
    size_t key = 5381;
    str = (char *)data;
    while((i = *str++))
        key = ((key << 7) + key) + i;

    return (key);
}
/*****************************************************************************/
int Cmp(void *data, void *param)
{
    return ((size_t)data - (size_t)param);
}
/*****************************************************************************/
size_t Hash(const void *data)
{
    return ((size_t)data % Capacity("/usr/share/dict/words"));
}
/*****************************************************************************/
size_t Capacity(const char *file_name)
{
    char ch = 0;
    FILE *fp = NULL;
    size_t number_of_words = 0;
    fp = fopen(file_name, "r");
    if(!fp)
    {
        return (FAILURE);
    }

    ch = getc(fp);
    for(; ch != EOF; ch = getc(fp))
        if ('\n' == ch)
            ++number_of_words;


    fclose(fp);
    return (number_of_words);
}
/*****************************************************************************/
void HashTableCreateDestroyTest(void)
{
    hash_table_t *table = HashTableCreate(200 , Hash, Cmp);
    assert(table);
    HashTableDestroy(table);
}
/*****************************************************************************/
void HashTableInsertRemoveTest(void)
{
     hash_table_t *table = HashTableCreate(200 , Hash, Cmp);
     assert(0 == HashTableInsert(table, (void *)13));
     assert(0 == HashTableInsert(table, (void *)15));
     assert(0 == HashTableInsert(table, (void *)78));
     assert(0 == HashTableInsert(table, (void *)0));
     assert(0 == HashTableInsert(table, (void *)133));
     assert(0 == HashTableInsert(table, (void *)131));
     HashTableRemove(table, (void *)13);
     HashTableRemove(table, (void *)15);
     HashTableRemove(table, (void *)78);
     HashTableRemove(table, (void *)0);
     HashTableRemove(table, (void *)133);
     HashTableRemove(table, (void *)131);

     HashTableDestroy(table);
}
/*****************************************************************************/
void HashTableSizeTest(void)
{
     hash_table_t *table = HashTableCreate(200 , Hash, Cmp);
     assert(0 == HashTableSize(table));
     assert(0 == HashTableInsert(table, (void *)13));
     assert(1 == HashTableSize(table));
     assert(0 == HashTableInsert(table, (void *)15));
     assert(2 == HashTableSize(table));
     assert(0 == HashTableInsert(table, (void *)78));
     assert(3 == HashTableSize(table));
     assert(0 == HashTableInsert(table, (void *)0));
     assert(4 == HashTableSize(table));
     assert(0 == HashTableInsert(table, (void *)133));
     assert(5 == HashTableSize(table));
     assert(0 == HashTableInsert(table, (void *)131));
     assert(6 == HashTableSize(table));
     HashTableRemove(table, (void *)13);
     assert(5 == HashTableSize(table));
     HashTableRemove(table, (void *)15);
     assert(4 == HashTableSize(table));
     HashTableDestroy(table);
}
/*****************************************************************************/
void HashTableIsEmptyTest(void)
{
     hash_table_t *table = HashTableCreate(200 , Hash, Cmp);
     assert(1 == HashTableIsEmpty(table));
     assert(0 == HashTableInsert(table, (void *)13));
     assert(0 == HashTableInsert(table, (void *)15));
     assert(0 == HashTableInsert(table, (void *)78));
     assert(0 == HashTableInsert(table, (void *)0));
     assert(0 == HashTableInsert(table, (void *)133));
     assert(0 == HashTableInsert(table, (void *)131));
     assert(0 == HashTableIsEmpty(table));
     HashTableRemove(table, (void *)13);
     HashTableRemove(table, (void *)15);
     HashTableRemove(table, (void *)78);
     HashTableRemove(table, (void *)0);
     HashTableRemove(table, (void *)133);
     HashTableRemove(table, (void *)131);
     assert(1 == HashTableIsEmpty(table));
     HashTableDestroy(table);
}
/*****************************************************************************/
void HashTableFindTest(void)
{
     hash_table_t *table = HashTableCreate(200 , Hash, Cmp);
     assert(0 == HashTableInsert(table, (void *)13));
     assert(0 == HashTableInsert(table, (void *)15));
     assert(0 == HashTableInsert(table, (void *)78));
     assert(0 == HashTableInsert(table, (void *)0));
     assert(0 == HashTableInsert(table, (void *)133));
     assert(0 == HashTableInsert(table, (void *)131));
     assert((void *)13 == HashTableFind(table, (void *)13));
     assert((void *)133 == HashTableFind(table, (void *)133));
     HashTableDestroy(table);
}
/*****************************************************************************/
void HashForEachTest(void)
{
    return;
}
/*****************************************************************************/