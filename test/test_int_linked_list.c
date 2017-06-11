//
// Created by Michal Ziobro on 09/06/2017.
//

#include <stdlib.h>
#include "test_int_linked_list.h"
#include "../common/data_handler.h"
#include "../linked_list/linked_list.h"
#include "../../unit_tests/test/assertion.h"

static linked_list_t *list;

static void test_create(void) {

    allocator_t *allocator;
    allocator_init(&allocator, int_allocate_handler, int_deallocate_handler);

    linked_list_init(&list, allocator);

    for(int i=0; i<20; i++) {
        linked_list_push_front(list, &i, sizeof(int));
    }
}

static void test_clean(void) {

    linked_list_free(list);
}

static void test_travers(void) {
    test_create();
    printf("%s: ", __func__); linked_list_travers(list, print_int_data_handler); printf("\n");
    test_clean();
}

static void test_find_first(void) {
    test_create();
    int value = 15;
    linked_node_t *found_node = linked_list_find_first(list, &value, int_ptr_cmp_func);
    assert_not_null(found_node, __func__);
    test_clean();
}


static void run_tests(void) {
    test_travers();
    test_find_first();
}

test_int_linked_list_t test_int_linked_list = { .run_tests = run_tests };