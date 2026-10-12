#include <stdio.h>
#include "kv.c"

int main() {
    printf("Hello, this is a Key-Value store program\n");

    kv_t *table = kv_init(2048);
    kv_put(table, "name", "Alice");
    kv_put(table, "age", "28");

    printf("name: %s, age: %s\n", kv_get(table, "name"), kv_get(table, "age"));
    printf("table size: %lu\n", table->count);

    printf("Deleting...\n");
    kv_delete(table, "name");

    printf("name: %s, age: %s\n", kv_get(table, "name"), kv_get(table, "age"));
    printf("table size: %lu\n", table->count);
    printf("Updating...\n");

    kv_put(table, "name", "Bob");
    kv_put(table, "age", "56");

    printf("name: %s, age: %s\n", kv_get(table, "name"), kv_get(table, "age"));
    printf("table size: %lu\n", table->count);
    return 0;
}
