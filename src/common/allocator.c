//
// Created by Michal Ziobro on 04/08/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/allocator.h"

struct allocator {
    allocate_handler_t allocate;        // function allocating given data store with data (memcpy data to data store)
    deallocate_handler_t deallocate;    // function deallocating given data store (free data store)
};

// allocator operations
result_t allocator_init(allocator_t **allocator, allocate_handler_t allocate_handler, deallocate_handler_t deallocate_handler) {

    if(allocate_handler == NULL) {
        fprintf(stderr, "allocate handler is empty, could not initialize allocator.\n");
        allocator = NULL;
        return FAILURE;
    }
    if(deallocate_handler == NULL) {
        fprintf(stderr, "deallocate handler is empty, could not initialize allocator.\n");
        allocator = NULL;
        return FAILURE;
    }

    // allocating memory for nodes allocator struct
    *allocator = malloc(sizeof(allocator_t));

    (*allocator)->allocate = allocate_handler;
    (*allocator)->deallocate = deallocate_handler;

    return SUCCESS;
}

allocate_handler_t allocator_allocate(allocator_t *allocator) {

    if(allocator == NULL) {
        fprintf(stderr, "allocator param is empty!\n");
        return  NULL;
    }

    if(allocator->allocate == NULL) {
        fprintf(stderr, "allocate handler not available in given allocator.\n");
        return NULL;
    }
    return allocator->allocate;
}

deallocate_handler_t allocator_deallocate(allocator_t *allocator) {

    if(allocator == NULL) {
        fprintf(stderr, "allocator param is empty!\n");
        return  NULL;
    }

    if(allocator->deallocate == NULL) {
        fprintf(stderr, "deallocate handler not available in given allocator.\n");
        return NULL;
    }
    return allocator->deallocate;
}

void allocator_free(allocator_t *allocator) {

    free(allocator);
    allocator = NULL;
}

// allocator handlers
void string_allocate_handler(void **data_store, void *data, size_t data_size) {

    // data_size + 1 added to include '\0' string end character
    *data_store = (char *) malloc(data_size+1);
    memcpy(*data_store, (char *) data, data_size+1);
}

void string_deallocate_handler(void **data_store) {

    free((char *)*data_store);
}

void int_allocate_handler(void **data_store, void *data, size_t data_size) {

    *data_store = (int *) malloc(data_size);
    memcpy(*data_store, (int *) data, data_size); // **data_store = *((int *) data)
}

void int_deallocate_handler(void **data_store) {

    free((int *)*data_store);
}

void uint16_allocate_handler(void **data_store, void *data, size_t data_size) {

    *data_store = (uint16_t *) malloc(data_size);
    memcpy(*data_store, (uint16_t *) data, data_size); // **data_store = *((uint16_t *) data)
}

void uint16_deallocate_handler(void **data_store) {

    free((uint16_t *)*data_store);
}

void uint64_allocate_handler(void **data_store, void *data, size_t data_size) {

    *data_store = (uint64_t *) malloc(data_size);
    memcpy(*data_store, (uint64_t *) data, data_size); // **data_store = *((uint64_t *) data)
}

void uint64_deallocate_handler(void **data_store) {

    free((uint64_t *)*data_store);
}