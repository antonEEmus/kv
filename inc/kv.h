#ifndef KV_H
#define KV_H

#include <stdlib.h>

// Types

#define TOMBSTONE ((char*)0x1)

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
int kv_put(kv_t *table, const char *key, const char *value);

char *kv_get(kv_t *table, const char *key);
int kv_delete(kv_t *table, const char *key);
void kv_free(kv_t *table);

#endif