//
// Created by Michal Ziobro on 28/08/2016.
//

#include "linked_list.h"

struct linked_node {
    linked_node_t *next;    // a reference to the next node
    void *data;             // a reference to any data stored in the node (should store only heap allocated data, else free(node->data) fails).
    size_t data_size;       // size of data stored in the node
};

struct linked_list {
    linked_node_t *head;    // points to head (first) node of the list
    allocator_t *allocator; // allocator can be null, or set to allocator_t struct that enables to allocate/deallocate nodes
};

// list operations

/**
 * while initializing a list you can pass optional allocator.
 * @allocator is the struct containing allocate_handler and
 * deallocate_handler.
 * if allocator is null, nodes store only pointers to data
 * owned by clients of the list.
 * while allocator is defined, nodes allocate/deallocate
 * data as owned by the list.
 **/
void list_init(linked_list_t **list, allocator_t *allocator) {

}

allocator_t *list_allocator(linked_list_t *list) {

}

void travers(const linked_list_t *list, data_handler_t data_handler) {

}

linked_node_t *find_first(const linked_list_t *list, const void *data, compare_func_t cmp_func) {

}

void insert_at_pos(linked_list_t *list, linked_node_t *pos, void *data, size_t data_size) {

}

void insert_node_at_pos(linked_list_t *list, linked_node_t *pos, linked_node_t *new_node) {

}

void push_front(linked_list_t *list, void *data, size_t data_size) {

}

void push_node_front(linked_list_t *list, linked_node_t *new_node) {

}

void remove_node(linked_list_t *list, linked_node_t *old_node) {

}

linked_node_t *front(const linked_list_t *list) {

}

void pop_front(linked_list_t *list) {

}

void list_free(linked_list_t *list) {

}

// node operations
void node_init(linked_node_t **node) {

}

void *unwrap_data(linked_node_t *node, size_t *data_size) {

}

void wrap_data(linked_list_t *list, linked_node_t *node, void *data, size_t data_size) {

}

void node_free(linked_list_t *list, linked_node_t *node) {

}