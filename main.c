#include <stdio.h>
#include "test/test_linked_list.h"
#include "hash_map/hash_map.h"
#include "test/test_hash_map.h"
#include "test/test_str_hash_map.h"
#include "test/test_int_hash_map.h"
#include "test/test_doubly_linked_list.h"
#include "../unit_tests/common/terminal.h"

int main() {

    TITLE_HEADER("test_linked_list");           test_linked_list.run_tests();
    TITLE_HEADER("test_doubly_linked_list");    test_doubly_linked_list.run_tests();
    TITLE_HEADER("test_hash_map");              test_hash_map.run_tests();
    TITLE_HEADER("test_str_hash_map");          test_str_hash_map.run_tests();
    TITLE_HEADER("test_int_hash_map");          test_int_hash_map.run_tests();

    return 0;
}