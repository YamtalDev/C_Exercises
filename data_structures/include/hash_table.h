/*=============================================================================

                           Customer requirements:

===============================================================================

*The hash table should support insertion of key-value pairs.

*The hash table should allow removal of key-value pairs.

*The hash table should be able to find a value based on a given key.

*The hash table should provide the number of elements it contains.

*The hash table should be able to check if it is empty or not.

*The hash table should allow iterating over all elements and performing a 
 user-defined action on each element.

*The hash table should provide functions to create and destroy the table.

===============================================================================

                           HASH_TABLE functionalities:

===============================================================================

1.) HashTableCreate: Creates a hash table and returns a pointer to it.

2.) HashTableDestroy: Destroys the hash table and cleans up all its key-value pairs.

3.) HashTableRemove: Removes an element from the hash table and returns the removed value.

4.) HashTableInsert: Inserts a new key-value pair into the hash table.

5.) HashTableCount: Returns the number of elements in the hash table.

6.) HashTableIsEmpty: Checks if the hash table is empty.

7.) HashTableFind: Finds an element with a specific key in the hash table and 
    returns the value found.

8.) HashTableForEach: Performs a user-defined action on each element in the hash table.

9.) HashTableLoadFactor: Calculates the load factor of the hash table, which represents 
    the ratio of the number of elements to the total number of slots/buckets in the table.

10.) HashTableSD: Calculates the standard deviation of bucket sizes in the hash table, 
     providing a measure of how spread out the sizes of the buckets are.

==============================================================================*/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h>    /* size_t*/
typedef struct table hash_table_t;

enum status
{
    SUCCESS = 0, FAILURE
};

/*****************************************************************************/

/* Return value specification for table_action_func_t: 0 for success, non 
zero for failure. */

typedef size_t (*hash_func_t)(const void *key);
typedef int (*hash_cmp_func_t)(void *value, void *param);
typedef int (*hash_action_func_t)(void *value, void *param);
/******************************************************************************

Function: HashTableCreate - Create a hash table.

Usage: hash_table_t *table = HashTableCreate(size, hash, is_mach)

Description: Creating hash table and returning a pointer to it.

Arguments: size - The size of the table, hash - a hash function, is_match - 
           a user define function

Return value: pointer to table, returns NULL in failure.

Time complexity: Worst : O(n).
Space complexity Worst: O(n).

******************************************************************************/

hash_table_t *HashTableCreate(size_t size, hash_func_t hash, hash_cmp_func_t is_match);

/******************************************************************************

Function: HashTableDestroy - Destroy the hash table

Usage: HashTableDestroy(table)

Description: Clean-up the table and all its key value pairs and delete the table 
             it self at the end.

Arguments: table - pointer to the table it self.

Return value: No return value.

Time complexity Worst: O(n).
Space complexity Worst: O(1).

******************************************************************************/

void HashTableDestroy(hash_table_t *table);

/******************************************************************************

Function: HashTableRemove - removes an element from the table.

Usage: void *removed_value = HashTableRemove(table, value)

Description: removes an element from the table.

Arguments: table - pointer to the table it self, value to be removed.

Return value: The value that was removed.

Time complexity Average: O(1), worst: O(n)

Space complexity Worst: O(1).

******************************************************************************/

void HashTableRemove(hash_table_t *table, const void *value);

/******************************************************************************

Function: HashTableInsert - Insert new value into the table.

Usage: int status = HashTableInsert(table, value)

Description: Insertion to the hash table.

Arguments: table - pointer to the table it self, value - the value to insert.

Return value: int - 0 on success, none zero on failure.

Time complexity amortized : O(1).
Space complexity Worst: O(1).

******************************************************************************/

int HashTableInsert(hash_table_t *table, void *value);

/******************************************************************************

Function: HashTableSize - Number of elements in the table.

Usage: size_t size = HashTableSize(table)

Description: Counts the number of elements in the table.

Arguments: table - pointer to the table it self.

Return value: size_t - number of elements.

Time complexity Worst: O(n).
Space complexity Worst: O(1).

******************************************************************************/

size_t HashTableSize(const hash_table_t *table);

/******************************************************************************

Function: HashTableIsEmpty - Checks if the table is empty. 

Usage: int status = HashTableIsEmpty(table)

Description: Checking whether the table is empty.

Arguments: table - pointer to the table it self.

Return value: non-zero if is empty, zero if not.

Time complexity Worst: O(n).
Space complexity Worst: O(1).

******************************************************************************/

int HashTableIsEmpty(const hash_table_t *table);

/******************************************************************************

Function: HashTableFind - Find an element inside the table.

Usage: void *value_found = HashTableFind(table, value)

Description: Find an element with a specific value in the table.

Arguments: table - pointer to the table it self, value - value to find.

Return value: The value found in the table, if fails return pointer to NULL.

Time complexity Worst: O(n).
Space complexity Worst: O(1).

******************************************************************************/

void *HashTableFind(const hash_table_t *table, const void *value);

/******************************************************************************

Function: HashTableForEach - For each element in the hash table.

Usage: int status = HashTableForEach(table, act, arg)

Description: For each element in the hash table the function act will be preformed.

Arguments: table - pointer to the table it self, act - pointer to user defined function,
           param - the value to be inserted to the user function.

Return value: On success returns 0, if fails returns the value of the user defined function.

Time complexity Worst: O(n).
Space complexity Worst: O(1).

******************************************************************************/

int HashTableForEach(hash_table_t *table, hash_action_func_t act, void *param);

/******************************************************************************

Function: HashTableLoadFactor - Calculates the load factor of the hash table.

Usage: double load_factor = HashTableLoadFactor(table)

Description: Calculates and returns the load factor of the hash table.
The load factor represents the ratio of the number of elements in the table to the total number of slots/buckets in the table.

Arguments: table - Pointer to the hash table.

Return value: The load factor of the hash table as a double value.

Time complexity: Worst: O(TBA) (To be determined by the implementation).
Space complexity: O(1).

******************************************************************************/

double HashTableLoadFactor(const hash_table_t *table);

/******************************************************************************

Function: HashTableSD - Calculates the standard deviation of bucket sizes in the hash table.

Usage: double standard_deviation = HashTableSD(table)

Description: Calculates and returns the standard deviation of the sizes of buckets in the hash table.
The standard deviation provides a measure of how spread out the sizes of the buckets are.

Arguments: table - Pointer to the hash table.

Return value: The standard deviation of bucket sizes as a double value.

Time complexity: Worst: O(TBA) (To be determined by the implementation).
Space complexity: O(1).

******************************************************************************/

double HashTableSD(const hash_table_t *table);

/*****************************************************************************/

#endif /* __HASH_TABLE_H__ */
