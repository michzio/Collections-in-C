//
// Created by Michal Ziobro on 31/08/2016.
//

#ifndef COLLECTIONS_STR_HASH_MAP_H
#define COLLECTIONS_STR_HASH_MAP_H

#include <stdint.h>
#include "common/allocator.h"
#include "hash_map.h"

#define HASH_MAP_INT_NOT_FOUND INT32_MIN
#define HASH_MAP_UINT16_NOT_FOUND UINT16_MAX
#define HASH_MAP_UINT64_NOT_FOUND UINT64_MAX

// hashable map (based on generic hashable map) storing generic values for string keys
struct str_hash_map;
typedef struct str_hash_map str_hash_map_t;

// str hash map operations
void str_hash_map_init_default(str_hash_map_t **str_hash_map, allocator_t *value_allocator);
void str_hash_map_init(str_hash_map_t **str_hash_map, allocator_t *value_allocator, size_t size);
void str_hash_map_put(str_hash_map_t *str_hash_map, char *str_key, void *val, size_t val_size);
void str_hash_map_put_int(str_hash_map_t *str_hash_map, char *str_key, int int_val);
void str_hash_map_put_uint16(str_hash_map_t *str_hash_map, char *str_key, uint16_t uint16_val);
void str_hash_map_put_uint64(str_hash_map_t *str_hash_map, char *str_key, uint64_t uint64_val);
void *str_hash_map_get(str_hash_map_t *str_hash_map, char *str_key, size_t *val_size);
int str_hash_map_get_int(str_hash_map_t *str_hash_map, char *str_key);
uint16_t str_hash_map_get_uint16(str_hash_map_t *str_hash_map, char *str_key);
uint64_t str_hash_map_get_uint64(str_hash_map_t *str_hash_map, char *str_key);
result_t str_hash_map_remove(str_hash_map_t *str_hash_map, char *str_key);
void str_hash_map_free(str_hash_map_t *str_hash_map);

char *str_hash_map_to_string(str_hash_map_t *str_hash_map, stringify_t value_stringify);

#endif //COLLECTIONS_STR_HASH_MAP_H
