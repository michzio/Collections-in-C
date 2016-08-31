//
// Created by Michal Ziobro on 31/08/2016.
//

#include "int_hash_map.h"
#include "hash_map.h"

struct int_hash_map {
    hash_map_t *hash_map;
};

// int hash map operations
void int_hash_map_init_default(int_hash_map_t **int_hash_map, allocator_t *value_allocator) {

}

void int_hash_map_init(int_hash_map_t **int_hash_map, allocator_t *value_allocator, size_t size) {

}

void int_hash_map_put(int_hash_map_t *int_hash_map, int key, void *val, size_t val_size) {

}

void *int_hash_map_get(int_hash_map_t *int_hash_map, int key, size_t *val_size) {

}

result_t int_hash_map_remove(int_hash_map_t *int_hash_map, int key) {

}

void int_hash_map_free(int_hash_map_t *int_hash_map) {

}