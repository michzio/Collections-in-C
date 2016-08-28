//
// Created by Michal Ziobro on 28/08/2016.
//

#include "linked_list.h"

struct linked_node {
    linked_node_t *next;    // a reference to the next node
    void *data;             // a reference to any data stored in the node (should store only heap allocated data, else free(node->data) fails).
    size_t data_size;       // size of data stored in the node
};

