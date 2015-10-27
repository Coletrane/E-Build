#ifndef manufacturing_h
#define manufacturing_h

#include "state.h"

typedef struct {
	int order_size;
	int capacity;
	int duration;
} order_t;


state_t*  manufacture_fail();
state_t*  manufacture_complete();
void      entry_to();
void      exit_from();

#endif
