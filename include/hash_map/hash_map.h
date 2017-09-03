//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef COLLECTIONS_HASH_MAP_H
#define COLLECTIONS_HASH_MAP_H

#include "common/allocator.h"
#include "comparer.h"
#include <stdio.h>

// hashable map (based on hashable table) storing generic values for generic keys
struct hash_map;
typedef struct hash_map hash_map_t;

typedef int (*hash_func_t) (hash_map_t *, void *key);
typedef char *(*stringify_t) (const void *data, size_t data_size);

// hash map operations
void hash_map_init_default(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator, compare_func_t key_cmp_func, hash_func_t hash_func);
void hash_map_init(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator, compare_func_t key_cmp_func, hash_func_t hash_func, size_t size);
void hash_map_put(hash_map_t *hash_map, void *key, size_t key_size, void *val, size_t val_size);
void *hash_map_get(hash_map_t *hash_map, void *key, size_t *val_size);
result_t hash_map_remove(hash_map_t *hash_map, void *key);
void hash_map_free(hash_map_t *hash_map);

char *hash_map_to_string(hash_map_t *hash_map, stringify_t key_stringify, stringify_t value_stringify);

// hash functions:
int str_hash_func(hash_map_t *hash_map, void *key); // for string keys
int int_ptr_hash_func(hash_map_t *hash_map, void *key); // for integer pointer keys

// stringify functions:
char *str_stringify(const void *data, size_t data_size);
char *int_stringify(const void *data, size_t data_size);

#endif //COLLECTIONS_HASH_MAP_H
