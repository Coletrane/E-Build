#ifndef manufacturing_h
#define manufacturing_h

#include "state.h"

state_t*  manuf_failed();
state_t*  manuf_completed();
void      entry_to();
void      exit_from();

#endif
