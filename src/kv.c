#include "../inc/kv.h"

kv_t *kv_init(size_t capacity) {
    kv_t *db = (kv_t*) malloc(sizeof(kv_t));
    if (db == NULL) {
        return NULL;
    }
    kv_entry_t *entries = calloc( capacity, sizeof(kv_entry_t));
    if (entries == NULL) {
        free(db);
        return NULL;
    }
    db->capacity = capacity;
    db->count = 0;

    return db;
}
