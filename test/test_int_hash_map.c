//
// Created by Michal Ziobro on 31/08/2016.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_int_hash_map.h"
#include "hash_map/int_hash_map.h"
#include "test/assertion.h"

static int_hash_map_t *int_hash_map;

static void test_create(void) {
    int_hash_map_init(&int_hash_map, NULL, 5);
}

static void test_create_with_allocator(void) {

    // string value allocator
    allocator_t *str_value_allocator;
    allocator_init(&str_value_allocator, string_allocate_handler, string_deallocate_handler);

    int_hash_map_init(&int_hash_map, str_value_allocator, 5);
}

static void test_clean(void) {
    int_hash_map_free(int_hash_map);
}

static void test_clean_with_allocator(void){
    int_hash_map_free(int_hash_map);
}

static void test_int_hash_map_put_get_remove(void) {
    test_create();
    int  test_key = 111;
    char test_val[] = "test value";
    assert_null(int_hash_map_get(int_hash_map, test_key, NULL), "test_int_hash_map_put_get_remove - (1) get from empty int hash map ");
    int_hash_map_put(int_hash_map, test_key, test_val, strlen(test_val));
    assert_equal(int_hash_map_get(int_hash_map, test_key, NULL), test_val, str_cmp_func, "test_int_hash_map_put_get_remove - (2) put/get new KVP into/from int hash map");
    assert_equal_int(int_hash_map_remove(int_hash_map, test_key), SUCCESS, "test_int_hash_map_put_get_remove - (3) removing KVP from int hash map");
    assert_null(int_hash_map_get(int_hash_map, test_key, NULL), "test_int_hash_map_put_get_remove - (4) permanently removed KVP from int hash map ");
    test_clean();
}

static void test_int_hash_map_put_get_remove_with_allocator(void) {
    test_create_with_allocator();
    int test_key = 111;
    char test_val[] = "test value";
    assert_null(int_hash_map_get(int_hash_map, test_key, NULL), "test_int_hash_map_put_get_remove_with_allocator - (1) get from empty int hash map");
    int_hash_map_put(int_hash_map, test_key, test_val, strlen(test_val));
    assert_equal(int_hash_map_get(int_hash_map, test_key, NULL), test_val, str_cmp_func, "test_int_hash_map_put_get_remove_with_allocator - (2) put/get new KVP into/from int hash map");
    assert_equal_int(int_hash_map_remove(int_hash_map, test_key), SUCCESS, "test_int_hash_map_put_get_remove_with_allocator - (3) removing KVP from int hash map");
    assert_null(int_hash_map_get(int_hash_map, test_key, NULL), "test_int_hash_map_put_get_remove_with_allocator - (4) permanently removed KVP from int hash map");
    test_clean_with_allocator();
}

static void test_int_hash_map_update_kvp(void) {
    test_create();
    int test_key = 111;
    char test_val_1[] = "test value 1";
    char test_val_2[] = "test value 2";
    assert_null(int_hash_map_get(int_hash_map, test_key, NULL), "test_int_hash_map_update_kvp - (1) get from empty int hash map");
    int_hash_map_put(int_hash_map, test_key, test_val_1, strlen(test_val_1));
    assert_equal(int_hash_map_get(int_hash_map, test_key, NULL), test_val_1, str_cmp_func, "test_int_hash_map_update_kvp - (2) put/get new KVP into/from int hash map");
    int_hash_map_put(int_hash_map, test_key, test_val_2, strlen(test_val_2));
    assert_equal(int_hash_map_get(int_hash_map, test_key, NULL), test_val_2, str_cmp_func, "test_int_hash_map_update_kvp - (3) put/get updated KVP into/from int hash map");
    test_clean();
}

static void test_int_hash_map_update_kvp_with_allocator(void) {
    test_create_with_allocator();
    int test_key = 111;
    char test_val_1[] = "test value 1";
    char test_val_2[] = "test value 2";
    assert_null(int_hash_map_get(int_hash_map, test_key, NULL), "test_int_hash_map_update_kvp_with_allocator - (1) get from empty int hash map");
    int_hash_map_put(int_hash_map, test_key, test_val_1, strlen(test_val_1));
    assert_equal(int_hash_map_get(int_hash_map, test_key, NULL), test_val_1, str_cmp_func, "test_int_hash_map_update_kvp_with_allocator - (2) put/get new KVP into/from int hash map");
    int_hash_map_put(int_hash_map, test_key, test_val_2, strlen(test_val_2));
    assert_equal(int_hash_map_get(int_hash_map, test_key, NULL), test_val_2, str_cmp_func, "test_int_hash_map_update_kvp_with_allocator - (3) put/get updated KVP into/from int hash map");
    test_clean_with_allocator();
}

static void test_int_hash_map_to_string(void) {
    test_create();
    const char pattern_string[] =   "0;555=val5,0=val0,\n"
                                    "1;999=val9,444=val4,\n"
                                    "2;888=val8,333=val3,\n"
                                    "3;777=val7,222=val2,\n"
                                    "4;666=val6,111=val1,\n";
    char *val[10];
    for(int i = 0; i < 10; i++) {
        int key = i*111;
        val[i] = malloc(sizeof(char)*4);
        sprintf(val[i], "val%d", i);
        int_hash_map_put(int_hash_map, key, val[i], strlen(val[i]));
    }
    char *string = int_hash_map_to_string(int_hash_map, str_stringify);
    printf("%s", string);
    assert_equal(string , pattern_string, str_cmp_func, __func__);
    free(string);
    for(int i=0; i < 10; i++) {
        free(val[i]);
    }
    test_clean();
}

static void test_int_hash_map_to_string_with_allocator(void) {
    test_create_with_allocator();
    const char pattern_string[] =   "0;555=val5,0=val0,\n"
                                    "1;999=val9,444=val4,\n"
                                    "2;888=val8,333=val3,\n"
                                    "3;777=val7,222=val2,\n"
                                    "4;666=val6,111=val1,\n";
    char *val;
    for(int i=0; i < 10; i++) {
        int key = i*111;
        val = malloc(sizeof(char)*4);
        sprintf(val, "val%d", i);
        int_hash_map_put(int_hash_map, key, val, strlen(val));
        free(val);
    }
    char *string = int_hash_map_to_string(int_hash_map, str_stringify);
    printf("%s", string);
    assert_equal(string , pattern_string, str_cmp_func, __func__);
    free(string);
    test_clean_with_allocator();
}

static void run_tests(void) {
    test_int_hash_map_put_get_remove();
    test_int_hash_map_put_get_remove_with_allocator();
    test_int_hash_map_update_kvp();
    test_int_hash_map_update_kvp_with_allocator();
    test_int_hash_map_to_string();
    test_int_hash_map_to_string_with_allocator();
}

test_int_hash_map_t test_int_hash_map = { .run_tests = run_tests };