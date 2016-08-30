cmake_minimum_required(VERSION 3.5)
project(collections)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.c hash_map/hash_map.h hash_map/hash_map.c common/allocator.h common/allocator.c common/comparer.h common/comparer.c common/data_handler.h common/data_handler.c test/test_hash_map.h test/test_hash_map.c common/types.h linked_list/linked_list.h linked_list/linked_list.c test/test_linked_list.h test/test_linked_list.c)

add_executable(collections ${SOURCE_FILES})

set(UNIT_TESTS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/unit_tests)
target_link_libraries(collections ${UNIT_TESTS_PATH}/libunit_tests.a)