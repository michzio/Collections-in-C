//
// Created by Michal Ziobro on 31/08/2016.
//

#ifndef COLLECTIONS_INT_HASH_MAP_H
#define COLLECTIONS_INT_HASH_MAP_H

#include "../common/allocator.h"

// hashable map (based on generic hashable map) storing generic values for integer pointer keys
struct int_hash_map;
typedef struct int_hash_map int_hash_map_t;

// int hash map operations
void int_hash_map_init_default(int_hash_map_t **int_hash_map, allocator_t *value_allocator);
void int_hash_map_init(int_hash_map_t **int_hash_map, allocator_t *value_allocator, size_t size);
void int_hash_map_put(int_hash_map_t *int_hash_map, int key, void *val, size_t val_size);
void *int_hash_map_get(int_hash_map_t *int_hash_map, int key, size_t *val_size);
result_t int_hash_map_remove(int_hash_map_t *int_hash_map, int key);
void int_hash_map_free(int_hash_map_t *int_hash_map);

#endif //COLLECTIONS_INT_HASH_MAP_H
