#include "../inc/kv.h"
#include <stdbool.h>
#include <string.h>

static size_t get_hash(const char *s, size_t capacity);

kv_t *kv_init(size_t capacity) {
    kv_t *table = (kv_t*) malloc(sizeof(kv_t));
    if (table == NULL) {
        return NULL;
    }
    kv_entry_t *entries = calloc( capacity, sizeof(kv_entry_t));
    if (entries == NULL) {
        free(table);
        return NULL;
    }
    table->entries = entries;
    table->capacity = capacity;
    table->count = 0;

    return table;
}

int kv_put(kv_t *table, const char *key, const char *value) {
    if (!table || !key || !value) {
        return -1;
    }

    size_t hash = get_hash(key, table->capacity);
    for (size_t probe = 0; probe < table->capacity - 1; probe++) {
        size_t idx = (hash + probe) % table->capacity;
        kv_entry_t *entry = &table->entries[idx];
        if (!entry->key) {
            // Inserting new value
            entry->key = strdup(key);
            entry->value = strdup(value);
            if (!entry->key || !entry->value) {
                free(entry->key);
                free(entry->value);
                entry->key = NULL;
                entry->value = NULL;
                return -1;
            }
            table->count++;
            return 0;
        }
        if (!strcmp(entry->key, key)) {
            // Updating existing value
            char *newValue = strdup(value);
            if (!newValue) {
                return -1;
            }
            free(entry->value);
            entry->value = newValue;
            return 0;
        }
    }

    return -2; // Capacity exceeded, didn't find an available slot
}

static size_t get_hash(const char *s, size_t capacity) {
    size_t hash = 0x1234567890abcdef;
    while (*s) {
        hash ^= *s;
        hash <<= 8;
        hash += *s;
        s++;
    }
    return hash % capacity;
}
