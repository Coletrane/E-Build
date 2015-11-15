#ifndef factory_lines_h
#define factory_lines_h

#include "manufacturing.h"
#include "shmem_ex.h"
#include <stdlib.h>


typedef struct {
    int factory_id;
    int capacity;
    int duration;
    int iterations;
    int num_items;
} line_params;

#endif
