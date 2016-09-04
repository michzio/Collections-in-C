//
// Created by Michal Ziobro on 31/08/2016.
//

#include <stdlib.h>
#include <string.h>
#include "str_hash_map.h"
#include "hash_map.h"

struct str_hash_map {
    hash_map_t *hash_map;
};

// str hash map operations
void str_hash_map_init_default(str_hash_map_t **str_hash_map, allocator_t *value_allocator) {

    // string key allocator
    allocator_t *str_key_allocator;
    allocator_init(&str_key_allocator, string_allocate_handler, string_deallocate_handler);

    // allocate string hash map
    *str_hash_map = malloc(sizeof(str_hash_map_t));
    hash_map_init_default( & (*str_hash_map)->hash_map, str_key_allocator, value_allocator, str_cmp_func, str_hash_func);
}

void str_hash_map_init(str_hash_map_t **str_hash_map, allocator_t *value_allocator, size_t size) {

    // string key allocator
    allocator_t *str_key_allocator;
    allocator_init(&str_key_allocator, string_allocate_handler, string_deallocate_handler);

    // allocate string hash map
    *str_hash_map = malloc(sizeof(str_hash_map_t));
    hash_map_init( & (*str_hash_map)->hash_map, str_key_allocator, value_allocator, str_cmp_func, str_hash_func, size);
}

void str_hash_map_put(str_hash_map_t *str_hash_map, char *str_key, void *val, size_t val_size)  {

    hash_map_put(str_hash_map->hash_map, (void *) str_key, strlen(str_key), val, val_size);
}

void *str_hash_map_get(str_hash_map_t *str_hash_map, char *str_key, size_t *val_size) {

    return hash_map_get(str_hash_map->hash_map, (void *) str_key, val_size);
}

result_t str_hash_map_remove(str_hash_map_t *str_hash_map, char *str_key) {

    return hash_map_remove(str_hash_map->hash_map, (void *) str_key);
}

void str_hash_map_free(str_hash_map_t *str_hash_map) {

    // deallocate inner string hash map
    hash_map_free( str_hash_map->hash_map );

    // deallocate string hash map wrapper
    free(str_hash_map);
}

char *str_hash_map_to_string(str_hash_map_t *str_hash_map, stringify_t value_stringify) {

    return hash_map_to_string(str_hash_map->hash_map, str_stringify, value_stringify);
}