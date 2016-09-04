//
// Created by Michal Ziobro on 28/08/2016.
//
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "hash_map.h"
#include "../linked_list/linked_list.h"

#define DEFAULT_HASH_MAP_SIZE 101

struct hash_map {
    linked_list_t **table_of_lists;
    int size;

    // allocators
    allocator_t *key_allocator;
    allocator_t *value_allocator;

    // key comparer
    compare_func_t key_cmp_func;

    // hash function implementation
    hash_func_t hash_function;
};

struct key_value_pair {
    void *key;
    size_t key_size;
    void *value;
    size_t value_size;
};
typedef struct key_value_pair key_value_pair_t;

// hash functions - calculate hash for given key of given type
int str_hash_func(hash_map_t *hash_map, void *key) {

    unsigned int h = 0;
    char *str_key = (char *) key;
    size_t str_key_len = strlen(str_key);

    for(int i=0; i < str_key_len; i++) {
        h += str_key[i];
    }

    // using hash table mask = hash table size - 1
    // it is used instead of modulo operation ( % hash table size )
    // as AND binary operation is faster than modulo operation
    return (h * 1049) % (hash_map->size);
}

int int_ptr_hash_func(hash_map_t *hash_map, void *key) {

    unsigned int h = 0;
    int int_key = *((int *) key);

    h = abs(int_key);

    // using hash table mask = hash table size - 1
    // it is used instead of modulo operation ( % hash table size )
    // as AND binary operation is faster than modulo operation
    return (h * 1049) % (hash_map->size);

}

// helper function
static linked_node_t *find_node_with_key(const linked_list_t *list, const void *key, compare_func_t key_cmp_func) {

    // go through the linked list to find the node containing key value pair with given key
    for(linked_node_t *node = linked_list_front(list); node != NULL; node = linked_list_next(node)) {
        key_value_pair_t *kvp = linked_node_unwrap_data(node, NULL);
        if(key_cmp_func(kvp->key, key) == 0)
            return node;
    }
    return NULL;
}

// hash map operations
void hash_map_init_default(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator, compare_func_t key_cmp_func, hash_func_t hash_func) {
    hash_map_init(hash_map, key_allocator, value_allocator, key_cmp_func, hash_func, DEFAULT_HASH_MAP_SIZE);
}

void hash_map_init(hash_map_t **hash_map, allocator_t *key_allocator, allocator_t *value_allocator, compare_func_t key_cmp_func, hash_func_t hash_func, size_t size) {

    *hash_map = malloc(sizeof(hash_map_t));
    (*hash_map)->size = size;
    (*hash_map)->key_allocator = key_allocator;
    (*hash_map)->value_allocator = value_allocator;
    (*hash_map)->key_cmp_func = key_cmp_func;
    (*hash_map)->hash_function = hash_func;

    (*hash_map)->table_of_lists = malloc(size * sizeof(linked_list_t *));
    for(int i=0; i < size; i++) {
        linked_list_init( &((*hash_map)->table_of_lists[i]), NULL);
    }
}

/**
 * function inserts new value for given key into hash map.
 * It wraps key and value into key_value_pair struct.
 * It uses hash_function() to find array index for given key
 * i.e. the place where to put new key value pair.
 * If there are some key value pairs at the calculated position,
 * we check whether there is the pair with given key and if so
 * we modify its value, else we insert new key value
 * pair at the front of the linked list at the given position
 * of the lists array.
 */
void hash_map_put(hash_map_t *hash_map, void *key, size_t key_size, void *val, size_t val_size) {

    // calculate hash table index
    int idx = hash_map->hash_function(hash_map, key);
    // get list for given index
    linked_list_t *list = hash_map->table_of_lists[idx];
    // find the node containing key value pair with given key
    linked_node_t *found_node = find_node_with_key(list, key, hash_map->key_cmp_func);

    if (found_node != NULL) {
        // 1. modify value for given key value pair
        key_value_pair_t *kvp = linked_node_unwrap_data(found_node, NULL);
        assert(hash_map->key_cmp_func(kvp->key, key) == 0); // additional check for bugs
        if (hash_map->value_allocator != NULL) {
            // when hash map is owning value:
            // deallocate old value from KVP
            deallocate_handler_t value_deallocate = allocator_deallocate(hash_map->value_allocator);
            value_deallocate(&kvp->value);
            // and allocate new value in KVP
            allocate_handler_t value_allocate = allocator_allocate(hash_map->value_allocator);
            value_allocate(&kvp->value, val, val_size);
            // update value size
            kvp->value_size = val_size;
        } else {
            // when client is owning value, only overwrite old value with new one and update its size
            kvp->value = val;
            kvp->value_size = val_size;
        }
    } else {
        // there isn't key value pair for given key in the linked list
        // 2. insert new key value pair
        key_value_pair_t *kvp = malloc(sizeof(key_value_pair_t));
        if (hash_map->key_allocator != NULL) {
            // when hash map is owning key, allocate it with key allocator
            allocate_handler_t key_allocate = allocator_allocate(hash_map->key_allocator);
            key_allocate(&kvp->key, key, key_size);
            kvp->key_size = key_size;
        } else {
            // when client is owning key, only store pointer to it
            kvp->key = key;
            kvp->key_size = key_size;
        }
        if (hash_map->value_allocator != NULL) {
            // when hash map is owning value, allocate it with value allocator
            allocate_handler_t value_allocate = allocator_allocate(hash_map->value_allocator);
            value_allocate(&kvp->value, val, val_size);
            kvp->value_size = val_size;
        } else {
            // when client is owning value, only store pointer to it
            kvp->value = val;
            kvp->value_size = val_size;
        }
        linked_list_push_front(list, kvp, sizeof(kvp));
    }
}

void *hash_map_get(hash_map_t *hash_map, void *key, size_t *val_size) {

    // calculate hash table index
    int idx = hash_map->hash_function(hash_map, key);
    // get list for given index
    linked_list_t *list = hash_map->table_of_lists[idx];
    // find the node containing key value pair with given key
    linked_node_t *found_node = find_node_with_key(list, key, hash_map->key_cmp_func);

    if(found_node != NULL) {
        // value found for given key
        key_value_pair_t *kvp = linked_node_unwrap_data(found_node, NULL);
        if(val_size != NULL)  *val_size = kvp->value_size;
        return kvp->value;
    }

    // else nothing found for given key
    if(val_size != NULL) *val_size = 0;
    return NULL;
}

result_t hash_map_remove(hash_map_t *hash_map, void *key) {

    // calculate hash table index
    int idx = hash_map->hash_function(hash_map, key);
    // get list for given index
    linked_list_t *list = hash_map->table_of_lists[idx];
    // find the node containing key value pair with given key
    linked_node_t *found_node = find_node_with_key(list, key, hash_map->key_cmp_func);

    if(found_node != NULL) {
        // remove key value pair from hash map
        key_value_pair_t *kvp = linked_node_unwrap_data(found_node, NULL);

        // deallocate key and value placed inside key_value_pair if needed
        if(hash_map->key_allocator != NULL) {
            deallocate_handler_t key_deallocate = allocator_deallocate(hash_map->key_allocator);
            key_deallocate(&kvp->key);
        }
        if(hash_map->value_allocator != NULL) {
            deallocate_handler_t value_deallocate = allocator_deallocate(hash_map->value_allocator);
            value_deallocate(&kvp->value);
        }

        // deallocate key_value_pair placed inside found node
        free(kvp);

        // remove node found for given key from the list
        linked_list_remove_node(list, found_node);

        return SUCCESS;
    }

    // else nothing found for given key
    return FAILURE;
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

static void str_append(char **str, size_t *str_len, const char *appendix, const size_t appendix_len) {

    *str = realloc(*str, sizeof(char)*(*str_len + appendix_len));
    strncpy(*str + *str_len, appendix, appendix_len);
    *str_len += appendix_len;
}

char *hash_map_to_string(hash_map_t *hash_map, stringify_t key_stringify, stringify_t value_stringify) {

    char *str, *a;
    size_t str_len = 0, a_len = 0;

    str = malloc(sizeof(char)*str_len);

    // go through table of lists
    for(int i=0; i<hash_map->size; i++) {

        // append hash table index
        a = int_stringify(&i, sizeof(i));
        a_len = strlen(a);
        str_append(&str, &str_len, a, a_len);
        free(a);
        // append separator
        str_append(&str, &str_len, ";", 1);

        // go through ith list nodes
        for(linked_node_t *node = linked_list_front(hash_map->table_of_lists[i]); node != NULL; node = linked_list_next(node)) {

            key_value_pair_t *kvp = linked_node_unwrap_data(node, NULL);

            // append key
            a = key_stringify(kvp->key, kvp->key_size);
            a_len = strlen(a);
            str_append(&str, &str_len, a, a_len);
            free(a);
            // append separator
            str_append(&str, &str_len, "=", 1);

            // append value
            a = value_stringify(kvp->value, kvp->value_size);
            a_len = strlen(a);
            str_append(&str, &str_len, a, a_len);
            free(a);
            // append separator
            str_append(&str, &str_len, ",", 1);
        }

        str_append(&str, &str_len, "\n", 1);
    }
    str_append(&str, &str_len, "\0", 1);

    return str;
}

// stringify functions:
char *str_stringify(const void *data, size_t data_size) {
    char *str = malloc(data_size);
    sprintf(str, "%s", (const char *) data);
    return str;
}

char *int_stringify(const void *data, size_t data_size) {

    const int *i = (const int *) data;
    int str_len = snprintf(NULL, 0, "%d", *i);
    char *str = malloc(str_len*sizeof(char));
    sprintf(str, "%d", *i);
    return str;
}
