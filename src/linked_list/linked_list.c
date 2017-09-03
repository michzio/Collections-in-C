//
// Created by Michal Ziobro on 28/08/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include "linked_list/linked_list.h"

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
void linked_list_init(linked_list_t **list, allocator_t *allocator) {
    *list = malloc(sizeof(linked_list_t));
    (*list)->head = NULL;
    (*list)->allocator = allocator;
}

allocator_t *linked_list_allocator(linked_list_t *list) {

    return list->allocator;
}

void linked_list_travers(const linked_list_t *list, data_handler_t handle_data) {

    for(linked_node_t *node = list->head; node != NULL; node = node->next)
        handle_data(node->data, node->data_size);
}

linked_node_t *linked_list_find_first(const linked_list_t *list, const void *data, compare_func_t cmp_func) {

    for(linked_node_t *node = list->head; node != NULL; node = node->next)
        if(cmp_func(data, node->data) == 0)
            return node;

    return NULL;
}

void linked_list_insert_after(linked_list_t *list, linked_node_t *pos, void *data, size_t data_size) {

    // wrap data into node
    linked_node_t *new_node;
    linked_node_init(&new_node);
    linked_node_wrap_data(list, new_node, data, data_size);

    linked_list_insert_node_after(list, pos, new_node);
}

void linked_list_insert_node_after(linked_list_t *list, linked_node_t *pos, linked_node_t *new_node) {

    if(pos == NULL) {
        linked_list_push_node_front(list, new_node);
        return;
    }

    new_node->next = pos->next;
    pos->next = new_node;
}

void linked_list_push_front(linked_list_t *list, void *data, size_t data_size) {

    // wrap data into node
    linked_node_t *new_node;
    linked_node_init(&new_node);
    linked_node_wrap_data(list, new_node, data, data_size);

    linked_list_push_node_front(list, new_node);
}

void linked_list_push_node_front(linked_list_t *list, linked_node_t *new_node) {

    new_node->next = list->head;
    list->head = new_node;
}

result_t linked_list_remove_node(linked_list_t *list, linked_node_t *old_node) {

    // if node to delete unspecified return error
    if(old_node == NULL) {
        fprintf(stderr, "Node to delete is empty!\n");
        return FAILURE;
    }

    // if node to delete is at the head
    if(list->head == old_node) {
        // delete old node at the head
        list->head = list->head->next;
        linked_node_free(list, old_node);
        return SUCCESS;
    }

    // if node to delete isn't at the head, traverse the list to find it
    linked_node_t *prev_node = list->head;
    while( prev_node != NULL ) {
        if(prev_node->next == old_node) {
            // delete old node
            prev_node->next = old_node->next;
            linked_node_free(list, old_node);
            return SUCCESS;
        }
        prev_node = prev_node->next;
    }

    // if node to delete not found in the list
    fprintf(stderr, "Couldn't find old node: %p to delete in the list: %p!\n", old_node, list);
    return FAILURE;
}

linked_node_t *linked_list_front(const linked_list_t *list) {
    return list->head;
}

result_t linked_list_pop_front(linked_list_t *list) {
    return linked_list_remove_node(list, list->head);
}

linked_node_t *linked_list_next(linked_node_t *node) {
    return node->next;
}

void linked_list_free(linked_list_t *list) {

    // deallocate nodes
    linked_node_t *node = list->head;
    while(node) {
        linked_node_t *del_node = node;
        node = node->next;
        linked_node_free(list, del_node);
    }
    list->head = NULL;

    // deallocate allocator if set
    if(list->allocator != NULL) allocator_free(list->allocator);

    // deallocate list
    free(list);
    list = NULL;
}

// node operations
void linked_node_init(linked_node_t **node) {
    *node = malloc(sizeof(linked_node_t));
    (*node)->next = NULL;
    (*node)->data = NULL;
    (*node)->data_size = 0;
}

void *linked_node_unwrap_data(linked_node_t *node, size_t *data_size) {
    if(data_size != NULL) *data_size = node->data_size; // return size of data through pointer argument
    return node->data;
}

/**
 * function wraps data into list node. It takes data and its size.
 * if there is allocator defined and list is the owner of data
 * stored in the node we should properly allocate this data with
 * allocator. on the other hand if client is the owner of data
 * we just store pointer to the data and leaves to the client
 * proper allocation/deallocation of this data.
 * regardless of data ownership store its size in the node.
 */
void linked_node_wrap_data(linked_list_t *list, linked_node_t *node, void *data, size_t data_size) {

    // store data size in the node
    node->data_size = data_size;

    if(list->allocator != NULL) {
        // when list is owning data allocate it with allocator
        allocate_handler_t allocate = allocator_allocate(list->allocator);
        allocate(&node->data, data, data_size);
    } else {
        // when client is owning data only store pointer to it
        node->data = data;
    }
}

void linked_node_handle(linked_node_t *node, data_handler_t handle_data) {
    handle_data(node->data, node->data_size);
}

/**
 * function deallocates given list node. if there is allocator
 * defined and list is the owner of data stored in the node
 * we should properly deallocate this data with allocator struct.
 * on the other hand if client is the owner of data we skip this
 * step, as the client is the only responsible for deallocation
 * of this data. regardless of data ownership we always free node struct.
 */
void linked_node_free(linked_list_t *list, linked_node_t *node) {

    // when list is owning data free it
    if(list->allocator != NULL) {
        deallocate_handler_t deallocate = allocator_deallocate(list->allocator);
        deallocate(&node->data);
    }
    // when client is owning data it is responsible for its deallocation

    // regardless of data ownership free node
    free(node);
    node = NULL;
}