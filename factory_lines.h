#ifndef factory_lines_h
#define factory_lines_h

#include "supervisor.h"

typedef struct {
    int factory_id;
    int capacity;
    int duration;
    int iterations;
    int num_items;
} line_params;

#endif
