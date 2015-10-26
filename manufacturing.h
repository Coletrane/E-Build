#ifndef manufacturing_h
#define manufacturing_h

#include "state.h"

typedef struct {
	int order_size;
	int capacity;
	int duration;
} order_t;

int ord_count = 0;

state_t*  manufacture_fail();
state_t*  manufacture_complete();
void      entry_to();
void      exit_from();
void order_init(order_t *ord);
void order_process(order_t *ord);

#endif