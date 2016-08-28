//
// Created by Michal Ziobro on 28/08/2016.
//
#include "hash_map.h"

#define DEFAULT_HASH_MAP_SIZE 100

struct hash_map {
    linked_list_t *table_of_lists;
    int size;
};

static int hash_function(void *key) {
    // TODO
}

// hash map operations
void hash_map_init_default(hash_map_t **hash_map, allocator_t *allocator) {

}

void hash_map_init(hash_map_t **hash_map, allocator_t *allocator, size_t size) {

}

void hash_map_put(hash_map_t *hash_map, void *key, void *val) {

}

void *hash_map_get(hash_map_t *hash_map, void *key) {

}

void hash_map_free(hash_map_t *hash_map) {

}