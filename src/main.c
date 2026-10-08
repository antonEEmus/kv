#include <stdio.h>
#include "kv.c"

int main() {
    printf("Hello, this is a Key-Value store program\n");
    kv_t *table = kv_init(2048);
    kv_put(table, "abc", "Spamton");
    kv_put(table, "def", "G.");
    kv_put(table, "123", "Spamton");
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key) {
            printf("index: %llu, key: %s, value: %s\n", i, table->entries[i].key, table->entries[i].value);
        }
    }
    printf("table size: %llu", table->count);
    return 0;
}
