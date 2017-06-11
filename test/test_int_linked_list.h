//
// Created by Michal Ziobro on 09/06/2017.
//

#ifndef COLLECTIONS_TEST_INT_LINKED_LIST_H
#define COLLECTIONS_TEST_INT_LINKED_LIST_H

typedef struct {
    void (*run_tests)(void);
} test_int_linked_list_t;

extern test_int_linked_list_t test_int_linked_list;


#endif //COLLECTIONS_TEST_INT_LINKED_LIST_H
