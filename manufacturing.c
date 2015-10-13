#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "statemodel.h"

state_t manufacturing = {
    default_event_handler,      // order_received
    default_event_handler,      // invalid_payment
    default_event_handler,      // valid_payment 
    manufacture_fail,	      	// manufacture_fail
    manufacture_complete,		// manufacture_complete
    default_event_handler,		// received
    default_event_handler,		// lost_package
    entry_to,                   // entry
    exit_from                   // exit
}

state_t* manufacture_fail()
{
  exit_from();
  updateStats(FAIL);
  return &accepting;
}

state_t* manufacture_complete()
{
	exit_from();
	chargeClient();
    return &shipping;
}

void entry_to()
{
    dispatchFactoryLines();
}

void exit_from()
{
    shutDownFactoryLines();
}

#endif
