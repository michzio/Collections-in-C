//
// Created by Michal Ziobro on 04/08/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include "common/data_handler.h"


// data handlers
void print_string_data_handler(void *data, size_t data_size) {

    printf("%s, ", (char *) data);
}

void print_int_data_handler(void *data, size_t data_size) {

    printf("%d, ", *((int *) data));
}

void free_data_handler(void *data, size_t data_size) {

    free(data);
}