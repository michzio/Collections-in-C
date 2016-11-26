//
// Created by Michal Ziobro on 04/08/2016.
//

#ifndef COLLECTIONS_DATA_HANDLER_H
#define COLLECTIONS_DATA_HANDLER_H

#include <stdio.h>

typedef void (*data_handler_t)(void *data, size_t data_size);

// data handlers
void print_string_data_handler(void *data, size_t data_size);
void free_data_handler(void *data, size_t data_size);


#endif //COLLECTIONS_DATA_HANDLER_H
