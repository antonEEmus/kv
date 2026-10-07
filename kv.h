#ifndef KV_H
#define KV_H

#include <stdlib.h>

// Types

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

#endif