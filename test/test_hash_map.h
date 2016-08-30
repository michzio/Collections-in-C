//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef COLLECTIONS_TEST_HASH_MAP_H
#define COLLECTIONS_TEST_HASH_MAP_H

typedef struct {
    void (*run_tests)(void);
} test_hash_map_t;

extern test_hash_map_t test_hash_map;

#endif //COLLECTIONS_TEST_HASH_MAP_H
