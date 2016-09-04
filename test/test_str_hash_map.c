//
// Created by Michal Ziobro on 31/08/2016.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_str_hash_map.h"
#include "../hash_map/str_hash_map.h"
#include "../../unit_tests/test/assertion.h"

static str_hash_map_t *str_hash_map;

static void test_create(void) {
    str_hash_map_init(&str_hash_map, NULL, 5);
}

static void test_create_with_allocator(void) {

    // string value allocator
    allocator_t *str_value_allocator;
    allocator_init(&str_value_allocator, string_allocate_handler, string_deallocate_handler);

    str_hash_map_init(&str_hash_map, str_value_allocator, 5);
}

static void test_clean(void) {
    str_hash_map_free(str_hash_map);
}

static void test_clean_with_allocator(void){
    str_hash_map_free(str_hash_map);
}

static void test_str_hash_map_put_get_remove(void) {
    test_create();
    char test_key[] = "test_key";
    char test_val[] = "test value";
    assert_null(str_hash_map_get(str_hash_map, test_key, NULL), "test_str_hash_map_put_get_remove - (1) get from empty str hash map ");
    str_hash_map_put(str_hash_map, test_key, test_val, strlen(test_val));
    assert_equal(str_hash_map_get(str_hash_map, test_key, NULL), test_val, str_cmp_func, "test_str_hash_map_put_get_remove - (2) put/get new KVP into/from str hash map");
    assert_equal_int(str_hash_map_remove(str_hash_map, test_key), SUCCESS, "test_str_hash_map_put_get_remove - (3) removing KVP from str hash map");
    assert_null(str_hash_map_get(str_hash_map, test_key, NULL), "test_str_hash_map_put_get_remove - (4) permanently removed KVP from str hash map ");
    test_clean();
}

static void test_str_hash_map_put_get_remove_with_allocator(void) {
    test_create_with_allocator();
    char test_key[] = "test_key";
    char test_val[] = "test value";
    assert_null(str_hash_map_get(str_hash_map, test_key, NULL), "test_str_hash_map_put_get_remove_with_allocator - (1) get from empty str hash map");
    str_hash_map_put(str_hash_map, test_key, test_val, strlen(test_val));
    assert_equal(str_hash_map_get(str_hash_map, test_key, NULL), test_val, str_cmp_func, "test_str_hash_map_put_get_remove_with_allocator - (2) put/get new KVP into/from str hash map");
    assert_equal_int(str_hash_map_remove(str_hash_map, test_key), SUCCESS, "test_str_hash_map_put_get_remove_with_allocator - (3) removing KVP from str hash map");
    assert_null(str_hash_map_get(str_hash_map, test_key, NULL), "test_str_hash_map_put_get_remove_with_allocator - (4) permanently removed KVP from str hash map");
    test_clean_with_allocator();
}

static void test_str_hash_map_update_kvp(void) {
    test_create();
    char test_key[] = "test key";
    char test_val_1[] = "test value 1";
    char test_val_2[] = "test value 2";
    assert_null(str_hash_map_get(str_hash_map, test_key, NULL), "test_str_hash_map_update_kvp - (1) get from empty str hash map");
    str_hash_map_put(str_hash_map, test_key, test_val_1, strlen(test_val_1));
    assert_equal(str_hash_map_get(str_hash_map, test_key, NULL), test_val_1, str_cmp_func, "test_str_hash_map_update_kvp - (2) put/get new KVP into/from str hash map");
    str_hash_map_put(str_hash_map, test_key, test_val_2, strlen(test_val_2));
    assert_equal(str_hash_map_get(str_hash_map, test_key, NULL), test_val_2, str_cmp_func, "test_str_hash_map_update_kvp - (3) put/get updated KVP into/from str hash map");
    test_clean();
}

static void test_str_hash_map_update_kvp_with_allocator(void) {
    test_create_with_allocator();
    char test_key[] = "test key";
    char test_val_1[] = "test value 1";
    char test_val_2[] = "test value 2";
    assert_null(str_hash_map_get(str_hash_map, test_key, NULL), "test_str_hash_map_update_kvp_with_allocator - (1) get from empty str hash map");
    str_hash_map_put(str_hash_map, test_key, test_val_1, strlen(test_val_1));
    assert_equal(str_hash_map_get(str_hash_map, test_key, NULL), test_val_1, str_cmp_func, "test_str_hash_map_update_kvp_with_allocator - (2) put/get new KVP into/from str hash map");
    str_hash_map_put(str_hash_map, test_key, test_val_2, strlen(test_val_2));
    assert_equal(str_hash_map_get(str_hash_map, test_key, NULL), test_val_2, str_cmp_func, "test_str_hash_map_update_kvp_with_allocator - (3) put/get updated KVP into/from str hash map");
    test_clean_with_allocator();
}

static void test_str_hash_map_to_string(void) {
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
        str_hash_map_put(str_hash_map, key[i], val[i], strlen(val[i]));
    }
    char *string = str_hash_map_to_string(str_hash_map, str_stringify);
    printf("%s", string);
    assert_equal(string , pattern_string, str_cmp_func, __func__);
    free(string);
    for(int i=0; i < 10; i++) {
        free(key[i]);
        free(val[i]);
    }
    test_clean();
}

static void test_str_hash_map_to_string_with_allocator() {
    test_create_with_allocator();
    const char pattern_string[] =   "0;key8=val8,key3=val3,\n"
                                    "1;key7=val7,key2=val2,\n"
                                    "2;key6=val6,key1=val1,\n"
                                    "3;key5=val5,key0=val0,\n"
                                    "4;key9=val9,key4=val4,\n";
    char *key;
    char *val;
    for(int i=0; i < 10; i++) {
        key = malloc(sizeof(char)*4);
        val = malloc(sizeof(char)*4);
        sprintf(key, "key%d", i);
        sprintf(val, "val%d", i);
        str_hash_map_put(str_hash_map, key, val, strlen(val));
        free(key);
        free(val);
    }
    char *string = str_hash_map_to_string(str_hash_map, str_stringify);
    printf("%s", string);
    assert_equal(string , pattern_string, str_cmp_func, __func__);
    free(string);
    test_clean_with_allocator();
}

static void run_tests(void) {
    test_str_hash_map_put_get_remove();
    test_str_hash_map_put_get_remove_with_allocator();
    test_str_hash_map_update_kvp();
    test_str_hash_map_update_kvp_with_allocator();
    test_str_hash_map_to_string();
    test_str_hash_map_to_string_with_allocator();
}

test_str_hash_map_t test_str_hash_map = { .run_tests = run_tests };