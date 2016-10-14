#include <printf.h>
#include "test/test_linked_list.h"
#include "hash_map/hash_map.h"
#include "test/test_hash_map.h"
#include "test/test_str_hash_map.h"
#include "test/test_int_hash_map.h"
#include "test/test_doubly_linked_list.h"

#define SEPARATOR printf("=============================================================================\n")

int main() {

    test_linked_list.run_tests();           SEPARATOR;
    test_doubly_linked_list.run_tests();    SEPARATOR;
    test_hash_map.run_tests();              SEPARATOR;
    test_str_hash_map.run_tests();          SEPARATOR;
    test_int_hash_map.run_tests();

    return 0;
}