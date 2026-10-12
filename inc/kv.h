#ifndef KV_H
#define KV_H

#include <stdlib.h>
#include <string.h>

// Types

#define TOMBSTONE ((void*)0x1)

typedef struct kv_entry_t {
    char *key;
    char *value;
} kv_entry_t;

typedef struct kv_t {
    size_t capacity;
    size_t count;
    kv_entry_t *entries;
} kv_t;

// Functions

/**
 * Initializes a kv_t instance, allocating the initial array of entries for the key-value table
 * @param capacity the initial capacity of the key-value table
 * @return a pointer to a kv_t instance
 */
kv_t *kv_init(size_t capacity);

/**
 * Updates a provided value in the key-value table by a given key,
 * inserts the value as new and increments the size otherwise
 * @param table a pointer to the key-value table
 * @param key a pointer to the key
 * @param value a pointer to the value to put
 * @return 0 if the put operation was successful,
 * returns -1 if invalid arguments were passed or any allocations failed,
 * returns -2 if the table's capacity was exceeded.
 */
int kv_put(kv_t *table, char *key, char *value);

/**
 * Returns a value from the table by a given key.
 * @param table a pointer to the table to get the value from
 * @param key the key to the desired value
 * @return a char* to the string value if found, NULL otherwise
 */
char *kv_get(kv_t *table, char *key);

/**
 * Deletes a value from a table by a given key.
 * @param table a pointer to the table to delete the value from
 * @param key a key to delete the value by
 * @return 0 if successful, -1 otherwise
 */
int kv_delete(kv_t *table, char *key);

/**
 * De-allocates a key-value table instance and all its associated members.
 * @param table a pointer to the key-value table to deallocate
 */
void kv_free(kv_t *table);

#endif