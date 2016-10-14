cmake_minimum_required(VERSION 3.5)
project(Collections)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES hash_map/hash_map.h hash_map/hash_map.c common/allocator.h common/allocator.c common/data_handler.h common/data_handler.c linked_list/linked_list.h linked_list/linked_list.c linked_list/doubly_linked_list.h linked_list/doubly_linked_list.c hash_map/str_hash_map.h hash_map/str_hash_map.c hash_map/int_hash_map.h hash_map/int_hash_map.c)
set(TEST_SOURCE_FILES test/test_hash_map.h test/test_hash_map.c test/test_linked_list.h test/test_linked_list.c test/test_int_hash_map.h test/test_int_hash_map.c test/test_str_hash_map.h test/test_str_hash_map.c test/test_doubly_linked_list.h test/test_doubly_linked_list.c)

# libraries paths
set(COMPARERS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/comparers)
set(UNIT_TESTS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/unit_tests)

add_library(Collections_Lib SHARED ${SOURCE_FILES})
set_target_properties(Collections_Lib PROPERTIES OUTPUT_NAME collections_shared)
target_link_libraries(Collections_Lib ${COMPARERS_PATH}/libcomparers.a)

add_library(Collections_Lib_Static ${SOURCE_FILES})
set_target_properties(Collections_Lib_Static PROPERTIES OUTPUT_NAME collections)
target_link_libraries(Collections_Lib_Static ${COMPARERS_PATH}/libcomparers.a)

add_executable(Collections main.c ${TEST_SOURCE_FILES})
target_link_libraries(Collections Collections_Lib_Static)
target_link_libraries(Collections ${UNIT_TESTS_PATH}/libunit_tests.a)