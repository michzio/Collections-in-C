cmake_minimum_required(VERSION 3.6)
project(Collections)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/hash_map/hash_map.h src/hash_map/hash_map.c include/common/allocator.h src/common/allocator.c include/common/data_handler.h src/common/data_handler.c include/linked_list/linked_list.h src/linked_list/linked_list.c include/linked_list/doubly_linked_list.h src/linked_list/doubly_linked_list.c include/hash_map/str_hash_map.h src/hash_map/str_hash_map.c include/hash_map/int_hash_map.h src/hash_map/int_hash_map.c)
set(TEST_SOURCE_FILES test/test_hash_map.h test/test_hash_map.c test/test_linked_list.h test/test_linked_list.c test/test_int_linked_list.h test/test_int_linked_list.c test/test_int_hash_map.h test/test_int_hash_map.c test/test_str_hash_map.h test/test_str_hash_map.c test/test_doubly_linked_list.h test/test_doubly_linked_list.c)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs)
if(CYGWIN)
    # windows cygwin
    message("building for Cygwin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/cygwin)
elseif(APPLE)
    # apple
    message("building for Apple")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/apple)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/apple)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/apple)
else()
    # unix
    message("building for Unix")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/unix)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/unix)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/unix)
endif()

### MAKING LIBRARIES ###
# include current project headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# subprojects paths
set(COMPARERS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../comparers)
set(COMPARERS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../comparers/outputs)

# add subprojects
add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${COMPARERS_SRC_DIR}
                  # Specifies the directory for the build outputs.
                  ${COMPARERS_BUILD_DIR} )

# include header files of subprojects
set(COMMON_FUNCTIONS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common)
include_directories(${COMPARERS_SRC_DIR}/include)
include_directories(${COMMON_FUNCTIONS_SRC_DIR}/include)

# current project shared and static libraries creation
# SHARED
add_library(Collections_Lib SHARED ${SOURCE_FILES})
set_target_properties(Collections_Lib PROPERTIES OUTPUT_NAME collections)
target_link_libraries(Collections_Lib Comparers_Lib)

# STATIC
add_library(Collections_Lib_Static ${SOURCE_FILES})
set_target_properties(Collections_Lib_Static PROPERTIES OUTPUT_NAME collections)
target_link_libraries(Collections_Lib_Static Comparers_Lib_Static)

### MAKING EXECUTABLE ###
# executable's libraries paths
set(UNIT_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../unit_tests)
if(CYGWIN)
    # windows cygwin
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_SRC_DIR}/outputs/lib/cygwin/libunit_tests.so)
elseif(APPLE)
    # apple
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_SRC_DIR}/outputs/lib/apple/libunit_tests.dylib)
else()
    # unix
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_SRC_DIR}/outputs/lib/unix/libunit_tests.so)
endif()

# executable's libraries import
add_library(Unit_Test_Lib SHARED IMPORTED)
set_target_properties( Unit_Test_Lib PROPERTIES IMPORTED_LOCATION ${UNIT_TESTS_LIB_PATH} )

# executable's libraries include headers
include_directories( ${UNIT_TESTS_SRC_DIR}/include )

# current project executable creation
add_executable(Collections src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Collections PROPERTIES OUTPUT_NAME collections)
target_link_libraries(Collections Collections_Lib)
target_link_libraries(Collections Unit_Test_Lib)