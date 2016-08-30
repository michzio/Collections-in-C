//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef COLLECTIONS_TEST_LINKED_LIST_H
#define COLLECTIONS_TEST_LINKED_LIST_H

typedef struct {
    void (*run_tests)(void);
} test_linked_list_t;

extern test_linked_list_t test_linked_list;

#endif //COLLECTIONS_TEST_LINKED_LIST_H
