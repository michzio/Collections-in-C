//
// Created by Michal Ziobro on 31/08/2016.
//

#ifndef COLLECTIONS_STR_HASH_MAP_H
#define COLLECTIONS_STR_HASH_MAP_H

#include "../common/allocator.h"

// hashable map (based on generic hashable map) storing generic values for string keys
struct str_hash_map;
typedef struct str_hash_map str_hash_map_t;

// str hash map operations
void str_hash_map_init_default(str_hash_map_t **str_hash_map, allocator_t *value_allocator);
void str_hash_map_init(str_hash_map_t **str_hash_map, allocator_t *value_allocator, size_t size);
void str_hash_map_put(str_hash_map_t *str_hash_map, char *str_key, void *val, size_t val_size);
void *str_hash_map_get(str_hash_map_t *str_hash_map, char *str_key, size_t *val_size);
result_t str_hash_map_remove(str_hash_map_t *str_hash_map, char *str_key);
void str_hash_map_free(str_hash_map_t *str_hash_map);

#endif //COLLECTIONS_STR_HASH_MAP_H
