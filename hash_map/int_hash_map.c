//
// Created by Michal Ziobro on 31/08/2016.
//

#include <stdlib.h>
#include "int_hash_map.h"
#include "hash_map.h"

struct int_hash_map {
    hash_map_t *hash_map;
};

// int hash map operations
void int_hash_map_init_default(int_hash_map_t **int_hash_map, allocator_t *value_allocator) {

    // int key allocator
    allocator_t *int_key_allocator;
    allocator_init(&int_key_allocator, int_allocate_handler, int_deallocate_handler);

    // allocate int hash map
    *int_hash_map = malloc(sizeof(int_hash_map_t));
    hash_map_init_default( & (*int_hash_map)->hash_map, int_key_allocator, value_allocator, int_ptr_cmp_func, int_ptr_hash_func );
}

void int_hash_map_init(int_hash_map_t **int_hash_map, allocator_t *value_allocator, size_t size) {

    // int key allocator
    allocator_t *int_key_allocator;
    allocator_init(&int_key_allocator, int_allocate_handler, int_deallocate_handler);

    // allocate int hash map
    *int_hash_map = malloc(sizeof(int_hash_map_t));
    hash_map_init( & (*int_hash_map)->hash_map, int_key_allocator, value_allocator, int_ptr_cmp_func, int_ptr_hash_func, size );
}

void int_hash_map_put(int_hash_map_t *int_hash_map, int key, void *val, size_t val_size) {

    hash_map_put(int_hash_map->hash_map, (void *) &key, sizeof(key), val, val_size);
}

void *int_hash_map_get(int_hash_map_t *int_hash_map, int key, size_t *val_size) {

    return hash_map_get(int_hash_map->hash_map, (void *) &key, val_size);
}

result_t int_hash_map_remove(int_hash_map_t *int_hash_map, int key) {

    return hash_map_remove(int_hash_map->hash_map, (void *) &key );
}

void int_hash_map_free(int_hash_map_t *int_hash_map) {

    // deallocate inner int hash map
    hash_map_free( int_hash_map->hash_map );

    // deallocate int hash map wrapper
    free(int_hash_map);
}