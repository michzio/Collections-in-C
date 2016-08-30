//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef COLLECTIONS_HASH_MAP_H
#define COLLECTIONS_HASH_MAP_H

#include "../common/allocator.h"
#include <ntsid.h>

// hashable map (based on hashable table) storing generic values for generic keys
struct hash_map;
typedef struct hash_map hash_map_t;

// hash map operations
void hash_map_init_default(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator);
void hash_map_init(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator, size_t size);
void hash_map_put(hash_map_t *hash_map, void *key, void *val);
void *hash_map_get(hash_map_t *hash_map, void *key);
void *hash_map_remove(hash_map_t *hash_map, void *key);
void hash_map_free(hash_map_t *hash_map);

#endif //COLLECTIONS_HASH_MAP_H
