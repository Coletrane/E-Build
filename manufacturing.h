#ifndef manufacturing_h
#define manufacturing_h

#include "state.h"

state_t*  manufacture_fail();
state_t*  manufacture_complete();
void      entry_to();
void      exit_from();

#endif
