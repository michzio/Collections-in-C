cmake_minimum_required(VERSION 3.6)
project(Collections)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES hash_map/hash_map.h hash_map/hash_map.c common/allocator.h common/allocator.c common/data_handler.h common/data_handler.c linked_list/linked_list.h linked_list/linked_list.c linked_list/doubly_linked_list.h linked_list/doubly_linked_list.c hash_map/str_hash_map.h hash_map/str_hash_map.c hash_map/int_hash_map.h hash_map/int_hash_map.c)
set(TEST_SOURCE_FILES test/test_hash_map.h test/test_hash_map.c test/test_linked_list.h test/test_linked_list.c test/test_int_linked_list.h test/test_int_linked_list.c test/test_int_hash_map.h test/test_int_hash_map.c test/test_str_hash_map.h test/test_str_hash_map.c test/test_doubly_linked_list.h test/test_doubly_linked_list.c)

if(CYGWIN)
    # windows cygwin
    message("building for Cygwin")
else()
    # unix
    message("building for Unix")
endif()

# libraries paths
set(COMPARERS_PATH ${CMAKE_SOURCE_DIR}/../comparers)
set(UNIT_TESTS_PATH ${CMAKE_SOURCE_DIR}/../unit_tests)
if(CYGWIN)
    # windows cygwin
    set(COMPARERS_LIB_PATH ${COMPARERS_PATH}/output/windows/lib/static/libcomparers.a)
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_PATH}/output/windows/lib/static/libunit_tests.a)
else()
    # unix
    set(COMPARERS_LIB_PATH ${COMPARERS_PATH}/output/unix/lib/static/libcomparers.a)
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_PATH}/output/unix/lib/static/libunit_tests.a)
endif()

add_library(Collections_Lib SHARED ${SOURCE_FILES})
set_target_properties(Collections_Lib PROPERTIES OUTPUT_NAME collections)
target_link_libraries(Collections_Lib ${COMPARERS_LIB_PATH})

add_library(Collections_Lib_Static ${SOURCE_FILES})
set_target_properties(Collections_Lib_Static PROPERTIES OUTPUT_NAME collections)
target_link_libraries(Collections_Lib_Static ${COMPARERS_LIB_PATH})

add_executable(Collections main.c ${TEST_SOURCE_FILES})
set_target_properties(Collections PROPERTIES OUTPUT_NAME collections)
target_link_libraries(Collections Collections_Lib_Static)
target_link_libraries(Collections ${UNIT_TESTS_LIB_PATH})

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
                  $(MAKE) install
                  DEPENDS ${PROJECT_NAME}
                  COMMENT "Installing ${PROJECT_NAME}")

if(CYGWIN)
    # windows cygwin
    set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/bin)
    set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib)
    set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib/static)
else()
    # unix
    set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/unix/bin)
    set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/unix/lib)
    set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/unix/lib/static)
endif()

install(TARGETS Collections Collections_Lib Collections_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})