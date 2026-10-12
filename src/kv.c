#include "../inc/kv.h"

static size_t get_hash(const char *s, size_t capacity);
static int insert_value(kv_t *table, kv_entry_t *entry, const char *key, const char *value);

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

int kv_put(kv_t *table, char *key, char *value) {
    if (!table || !key || !value) {
        return -1;
    }

    size_t hash = get_hash(key, table->capacity);
    kv_entry_t *tombstoneEntry = NULL;
    for (size_t probe = 0; probe < table->capacity - 1; probe++) {
        size_t idx = (hash + probe) % table->capacity;
        kv_entry_t *entry = &table->entries[idx];
        if (entry->key == NULL) {
            // If found an empty slot, insert a new value
            return insert_value(table, entry, key, value);
        }
        if (entry->key == TOMBSTONE) {
            tombstoneEntry = entry;
            continue;
        }
        if (entry->key && !strcmp(entry->key, key)) {
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
    if (tombstoneEntry != NULL) {
        // If the probing loop reached its end and an available tombstone entry exists, insert a new value there
        return insert_value(table, tombstoneEntry, key, value);
    }

    return -2; // Capacity exceeded, didn't find an available slot
}

char *kv_get(kv_t *table, char *key) {
    if (!table || !key) {
        return NULL;
    }
    size_t hash = get_hash(key, table->capacity);
    for (size_t i = 0; i < table->capacity; i++) {
        size_t idx = (hash + i) % table->capacity;
        kv_entry_t *entry = &table->entries[idx];
        if (entry->key == NULL) {
            return NULL;
        }
        if (entry->key &&
            entry->key != TOMBSTONE &&
            !strcmp(key, entry->key)) {
            return entry->value;
        }
    }
    return NULL;
}

int kv_delete(kv_t *table, char *key) {
    if (!table || !key) {
        return -1;
    }
    size_t hash = get_hash(key, table->capacity);
    for (size_t i = 0; i < table->capacity; i++) {
        size_t idx = (hash + i) % table->capacity;
        kv_entry_t *entry = &table->entries[idx];
        if (entry->key == NULL) {
            return -1;
        }
        if (entry->key &&
            entry->key != TOMBSTONE &&
            !strcmp(key, entry->key)) {
            free(entry->key);
            free(entry->value);
            entry->key = TOMBSTONE;
            entry->value = NULL;
            table->count--;
            return 0;
        }
    }
    return -1;
}

inline int insert_value(kv_t *table, kv_entry_t *entry, const char *key, const char *value) {
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
