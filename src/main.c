#include <stdio.h>
#include "kv.c"

int main() {
    printf("Hello, this is a Key-Value store program\n");
    kv_t *table = kv_init(2048);
    char *key1 = "abc";
    char *key2 = "def";
    char *key3 = "975934587394875390c";
    kv_put(table, key1, "Spamton");
    kv_put(table, key2, "G.");
    kv_put(table, key3, "1997");
    char *value1 = kv_get(table, key1);
    char *value2 = kv_get(table, key2);
    char *value3 = kv_get(table, key3);
    printf("k1: %s, v1: %s, k2: %s, v2 %s, k3: %s, v3: %s\n",
        key1, value1, key2, value2, key3, value3);
    printf("table size: %lu", table->count);
    return 0;
}
