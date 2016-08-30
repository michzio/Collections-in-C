//
// Created by Michal Ziobro on 28/08/2016.
//
#include <stdlib.h>
#include "hash_map.h"
#include "../linked_list/linked_list.h"

#define DEFAULT_HASH_MAP_SIZE 100

struct hash_map {
    linked_list_t **table_of_lists;
    int size;

    // allocators
    allocator_t *key_allocator;
    allocator_t *value_allocator;
};

struct key_value_pair {
    void *key;
    size_t key_size;
    void *value;
    size_t value_size;
};
typedef struct key_value_pair key_value_pair_t;

static int hash_function(void *key) {
    // TODO
}

// hash map operations
void hash_map_init_default(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator) {
    hash_map_init(hash_map, key_allocator, value_allocator, DEFAULT_HASH_MAP_SIZE);
}

void hash_map_init(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator, size_t size) {

    *hash_map = malloc(sizeof(hash_map_t));
    (*hash_map)->size = size;
    (*hash_map)->key_allocator = key_allocator;
    (*hash_map)->value_allocator = value_allocator;

    (*hash_map)->table_of_lists = malloc(size * sizeof(linked_list_t *));
    for(int i=0; i < size; i++) {
        linked_list_init( &((*hash_map)->table_of_lists[i]), NULL);
    }
}

void hash_map_put(hash_map_t *hash_map, void *key, void *val) {

}

void *hash_map_get(hash_map_t *hash_map, void *key) {

}

void *hash_map_remove(hash_map_t *hash_map, void *key) {

}

void hash_map_free(hash_map_t *hash_map) {

    for(int i=0; i < hash_map->size; i++) {

        linked_list_t *list = hash_map->table_of_lists[i];
        for(linked_node_t *node = linked_list_front(list); node != NULL; node = linked_list_next(node)) {

            key_value_pair_t *kvp = linked_node_unwrap_data(node, NULL);

            // deallocate key and value placed inside key_value_pair if needed
            if(hash_map->key_allocator != NULL) {
                deallocate_handler_t key_deallocate = allocator_deallocate(hash_map->key_allocator);
                key_deallocate(&kvp->key);
            }
            if(hash_map->value_allocator != NULL) {
                deallocate_handler_t value_deallocate = allocator_deallocate(hash_map->value_allocator);
                value_deallocate(&kvp->value);
            }

            // deallocate key_value_pair placed inside current node
            free(kvp);
        }
        // deallocate linked lists from table of lists
        linked_list_free(list);
    }

    // deallocate table of lists
    free(hash_map->table_of_lists);
    hash_map->table_of_lists = NULL;
    hash_map->size = 0;

    // deallocate allocators if set
    if(hash_map->key_allocator != NULL) allocator_free(hash_map->key_allocator);
    if(hash_map->value_allocator != NULL) allocator_free(hash_map->value_allocator);

    // deallocate hash map
    free(hash_map);
    hash_map = NULL;
}