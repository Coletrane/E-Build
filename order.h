#ifndef order_h
#define order_h

#include <stdlib.h>
#include <time.h>

typedef struct {
	int order_size;
	int capacity;
	int duration;
} order_t;

void order_init(order_t *ord);

void order_process(order_t *ord);

#endif
