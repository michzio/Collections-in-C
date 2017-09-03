//
// Created by Michal Ziobro on 28/08/2016.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_hash_map.h"
#include "hash_map/hash_map.h"
#include "test/assertion.h"

static hash_map_t *hash_map;

static void test_create(void) {
    hash_map_init(&hash_map, NULL, NULL, str_cmp_func, str_hash_func, 5);
}

static void test_create_with_allocator(void) {

    // int key allocator
    allocator_t *int_key_allocator;
    allocator_init(&int_key_allocator, int_allocate_handler, int_deallocate_handler);

    // string value allocator
    allocator_t *str_value_allocator;
    allocator_init(&str_value_allocator, string_allocate_handler, string_deallocate_handler);

    hash_map_init(&hash_map, int_key_allocator, str_value_allocator, int_ptr_cmp_func, int_ptr_hash_func, 5);
}

static void test_clean(void) {
    hash_map_free(hash_map);
}

static void test_clean_with_allocator(void) {
    hash_map_free(hash_map);
}

static void test_hash_map_put_get_remove(void) {
    test_create();
    char test_key[] = "test_key";
    char test_val[] = "test value";
    assert_null(hash_map_get(hash_map, test_key, NULL),  "test_hash_map_put_get_remove - (1) get from empty hash map");
    hash_map_put(hash_map, test_key, strlen(test_key), test_val, strlen(test_val));
    assert_equal(hash_map_get(hash_map, test_key, NULL), test_val, str_cmp_func, "test_hash_map_put_get_remove - (2) put/get new KVP into/from hash map");
    assert_equal_int(hash_map_remove(hash_map, test_key), SUCCESS, "test_hash_map_put_get_remove - (3) removing KVP from hash map");
    assert_null(hash_map_get(hash_map, test_key, NULL), "test_hash_map_put_get_remove - (4) permanently removed KVP from hash map");
    test_clean();
}

static void test_hash_map_put_get_remove_with_allocator(void) {
    test_create_with_allocator();
    int test_key = 123;
    char test_val[] = "test value";
    assert_null(hash_map_get(hash_map, &test_key, NULL), "test_hash_map_put_get_remove_with_allocator - (1) get from empty hash map");
    hash_map_put(hash_map, &test_key, sizeof(test_key), test_val, strlen(test_val));
    assert_equal(hash_map_get(hash_map, &test_key, NULL), test_val, str_cmp_func, "test_hash_map_put_get_remove_with_allocator - (2) put/get new KVP into/from hash map");
    assert_equal_int(hash_map_remove(hash_map, &test_key), SUCCESS, "test_hash_map_put_get_remove_with_allocator - (3) removing KVP from hash map");
    assert_null(hash_map_get(hash_map, &test_key, NULL), "test_hash_map_put_get_remove_with_allocator - (4) permanently removed KVP from hash map");
    test_clean_with_allocator();
}

static void test_hash_map_update_kvp(void) {
    test_create();
    char test_key[] = "test key";
    char test_val_1[] = "test value 1";
    char test_val_2[] = "test value 2";
    assert_null(hash_map_get(hash_map, test_key, NULL), "test_hash_map_update_kvp - (1) get from empty hash map");
    hash_map_put(hash_map, test_key, strlen(test_key), test_val_1, strlen(test_val_1));
    assert_equal(hash_map_get(hash_map, test_key, NULL), test_val_1, str_cmp_func, "test_hash_map_update_kvp - (2) put/get new KVP into/from hash map");
    hash_map_put(hash_map, test_key, strlen(test_key), test_val_2, strlen(test_val_2));
    assert_equal(hash_map_get(hash_map, test_key, NULL), test_val_2, str_cmp_func, "test_hash_map_update_kvp - (3) put/get updated KVP into/from hash map");
    test_clean();
}

static void test_hash_map_update_kvp_with_allocator(void) {
    test_create_with_allocator();
    int test_key = 123;
    char test_val_1[] = "test value 1";
    char test_val_2[] = "test value 2";
    assert_null(hash_map_get(hash_map, &test_key, NULL), "test_hash_map_update_kvp_with_allocator - (1) get from empty hash map");
    hash_map_put(hash_map, &test_key, sizeof(test_key), test_val_1, strlen(test_val_1));
    assert_equal(hash_map_get(hash_map, &test_key, NULL), test_val_1, str_cmp_func, "test_hash_map_update_kvp_with_allocator - (2) put/get new KVP into/from hash map");
    hash_map_put(hash_map, &test_key, sizeof(test_key), test_val_2, strlen(test_val_2));
    assert_equal(hash_map_get(hash_map, &test_key, NULL), test_val_2, str_cmp_func, "test_hash_map_update_kvp_with_allocator - (3) put/get updated KVP into/from hash map");
    test_clean_with_allocator();
}

static void test_hash_map_to_string(void) {
    test_create();
    const char pattern_string[] =   "0;key8=val8,key3=val3,\n"
                                    "1;key7=val7,key2=val2,\n"
                                    "2;key6=val6,key1=val1,\n"
                                    "3;key5=val5,key0=val0,\n"
                                    "4;key9=val9,key4=val4,\n";
    char *key[10];
    char *val[10];
    for(int i = 0; i < 10; i++) {
        key[i] = malloc(sizeof(char)*4);
        val[i] = malloc(sizeof(char)*4);
        sprintf(key[i], "key%d", i);
        sprintf(val[i], "val%d", i);
        hash_map_put(hash_map, key[i], strlen(key[i]), val[i], strlen(val[i]));
    }
    char *string = hash_map_to_string(hash_map, str_stringify, str_stringify);
    printf("%s", string);
    assert_equal(string , pattern_string, str_cmp_func, __func__);
    free(string);
    for(int i=0; i < 10; i++) {
        free(key[i]);
        free(val[i]);
    }
    test_clean();
}

static void test_hash_map_to_string_with_allocator() {
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
        hash_map_put(hash_map, &key, sizeof(key), val, strlen(val));
        free(val);
    }
    char *string = hash_map_to_string(hash_map, int_stringify, str_stringify);
    printf("%s", string);
    assert_equal(string , pattern_string, str_cmp_func, __func__);
    free(string);
    test_clean_with_allocator();
}

static void run_tests(void) {
    test_hash_map_put_get_remove();
    test_hash_map_put_get_remove_with_allocator();
    test_hash_map_update_kvp();
    test_hash_map_update_kvp_with_allocator();
    test_hash_map_to_string();
    test_hash_map_to_string_with_allocator();
}

test_hash_map_t test_hash_map = { .run_tests = run_tests };