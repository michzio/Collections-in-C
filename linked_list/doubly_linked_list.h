//
// Created by Michal Ziobro on 28/07/2016.
//

/**
 * Doubly linked list - collection structure based
 * on nodes linked in both directions using pointers.
 * This linked list is circular i.e. last node points
 * to first and first to last.
 *   <- |n| <-> |n| <-> |n| ->....<-|n|->
 */

#ifndef REMOTECONTROLLERAPI_SERVER_DOUBLY_LINKED_LIST_H
#define REMOTECONTROLLERAPI_SERVER_DOUBLY_LINKED_LIST_H

#include "../../comparers/comparer.h"
#include "../../common/types.h"
#include "../common/allocator.h"
#include "../common/data_handler.h"

struct doubly_linked_node;
typedef struct doubly_linked_node doubly_linked_node_t;

struct doubly_linked_list;
typedef struct doubly_linked_list doubly_linked_list_t;

// list operations
void dl_list_init(doubly_linked_list_t **list, allocator_t *allocator);
allocator_t *dl_list_allocator(doubly_linked_list_t *list);
void dl_list_travers_forward(const doubly_linked_list_t *list, data_handler_t data_handler);
void dl_list_travers_backward(const doubly_linked_list_t *list, data_handler_t data_handler);
doubly_linked_node_t *dl_list_find_first(const doubly_linked_list_t *list, const void *data, compare_func_t cmp_func);
void dl_list_insert_at_pos(doubly_linked_list_t *list, doubly_linked_node_t *pos, void *data, size_t data_size);
void dl_list_insert_node_at_pos(doubly_linked_list_t *list, doubly_linked_node_t *pos, doubly_linked_node_t *new_node);
void dl_list_push_front(doubly_linked_list_t *list, void *data, size_t data_size);
void dl_list_push_node_front(doubly_linked_list_t *list, doubly_linked_node_t *new_node);
void dl_list_push_back(doubly_linked_list_t *list, void *data, size_t data_size);
void dl_list_push_node_back(doubly_linked_list_t *list, doubly_linked_node_t *new_node);
result_t dl_list_remove_node(doubly_linked_list_t *list, doubly_linked_node_t *old_node);
doubly_linked_node_t *dl_list_front(const doubly_linked_list_t *list);
doubly_linked_node_t *dl_list_back(const doubly_linked_list_t *list);
void dl_list_pop_front(doubly_linked_list_t *list);
void dl_list_pop_back(doubly_linked_list_t *list);
doubly_linked_node_t *dl_list_next(doubly_linked_node_t *node);
doubly_linked_node_t *dl_list_previous(doubly_linked_node_t *node);
void dl_list_free(doubly_linked_list_t *list);

// node operations
void dl_node_init(doubly_linked_node_t **node);
void *dl_unwrap_data(doubly_linked_node_t *node, size_t *data_size);
void dl_wrap_data(doubly_linked_list_t *list, doubly_linked_node_t *node, void *data, size_t data_size);
void dl_node_free(doubly_linked_list_t *list, doubly_linked_node_t *node);

#endif //REMOTECONTROLLERAPI_SERVER_DOUBLY_LINKED_LIST_H
