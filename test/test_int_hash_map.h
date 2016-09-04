//
// Created by Michal Ziobro on 31/08/2016.
//

#ifndef COLLECTIONS_TEST_INT_HASH_MAP_H
#define COLLECTIONS_TEST_INT_HASH_MAP_H

typedef struct {
    void (*run_tests)(void);
} test_int_hash_map_t;

extern test_int_hash_map_t test_int_hash_map;

#endif //COLLECTIONS_TEST_INT_HASH_MAP_H
