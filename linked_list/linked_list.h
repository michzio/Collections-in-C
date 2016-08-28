//
// Created by Michal Ziobro on 28/08/2016.
//

/**
 * Linked list - collection structure based
 * on nodes linked in one direction using pointers.
 * |n| -> |n| -> |n| -> ... -> |n| ->
 **/

#ifndef COLLECTIONS_LINKED_LIST_H
#define COLLECTIONS_LINKED_LIST_H

#include "../common/allocator.h"
#include "../common/data_handler.h"
#include "../common/comparer.h"

struct linked_node;
typedef struct linked_node linked_node_t;

struct linked_list;
typedef struct linked_list linked_list_t;

// list operations
void list_init(linked_list_t **list, allocator_t *allocator);
allocator_t *list_allocator(linked_list_t *list);
void travers(const linked_list_t *list, data_handler_t data_handler);
linked_node_t *find_first(const linked_list_t *list, const void *data, compare_func_t cmp_func);
void insert_at_pos(linked_list_t *list, linked_node_t *pos, void *data, size_t data_size);
void insert_node_at_pos(linked_list_t *list, linked_node_t *pos, linked_node_t *new_node);
void push_front(linked_list_t *list, void *data, size_t data_size);
void push_node_front(linked_list_t *list, linked_node_t *new_node);
void remove_node(linked_list_t *list, linked_node_t *old_node);
linked_node_t *front(const linked_list_t *list);
void pop_front(linked_list_t *list);
void list_free(linked_list_t *list);

// node operations
void node_init(linked_node_t **node);
void *unwrap_data(linked_node_t *node, size_t *data_size);
void wrap_data(linked_list_t *list, linked_node_t *node, void *data, size_t data_size);
void node_free(linked_list_t *list, linked_node_t *node);

#endif //COLLECTIONS_LINKED_LIST_H
