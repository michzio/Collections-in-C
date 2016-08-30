#include "test/test_linked_list.h"
#include "hash_map/hash_map.h"

static int hash_function(void *key, int key_size) {

    unsigned int h = 0;
    char *key_data = (char *) key;

    for(int i=0; i < key_size; i++) {
        h += key_data[i];
    }

    // using hash table mask = hash table size - 1
    // it is used instead of modulo operation ( % hash table size )
    // as and binary operation is faster than modulo operation
    return (h * 1049) & (30 - 1);
}

int main() {

    test_linked_list.run_tests();
    hash_map_t *hash_map;
    hash_map_put(hash_map, 12, 2, 17, 2);


    return 0;
}