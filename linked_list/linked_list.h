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
#include "../../comparers/comparer.h"

struct linked_node;
typedef struct linked_node linked_node_t;

struct linked_list;
typedef struct linked_list linked_list_t;

// list operations
void linked_list_init(linked_list_t **list, allocator_t *allocator);
allocator_t *linked_list_allocator(linked_list_t *list);
void linked_list_travers(const linked_list_t *list, data_handler_t data_handler);
linked_node_t *linked_list_find_first(const linked_list_t *list, const void *data, compare_func_t cmp_func);
void linked_list_insert_after(linked_list_t *list, linked_node_t *pos, void *data, size_t data_size);
void linked_list_insert_node_after(linked_list_t *list, linked_node_t *pos, linked_node_t *new_node);
void linked_list_push_front(linked_list_t *list, void *data, size_t data_size);
void linked_list_push_node_front(linked_list_t *list, linked_node_t *new_node);
result_t linked_list_remove_node(linked_list_t *list, linked_node_t *old_node);
linked_node_t *linked_list_front(const linked_list_t *list);
result_t linked_list_pop_front(linked_list_t *list);
linked_node_t *linked_list_next(linked_node_t *node);
void linked_list_free(linked_list_t *list);

// node operations
void linked_node_init(linked_node_t **node);
void *linked_node_unwrap_data(linked_node_t *node, size_t *data_size);
void linked_node_wrap_data(linked_list_t *list, linked_node_t *node, void *data, size_t data_size);
void linked_node_handle(linked_node_t *node, data_handler_t data_handler);
void linked_node_free(linked_list_t *list, linked_node_t *node);

#endif //COLLECTIONS_LINKED_LIST_H
