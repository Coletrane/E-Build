#ifndef accepting_c
#define accepting_c

#include "accepting.h"
#include "statemodel.h"

state_t accepting = {
    order_received,      		// order_received
    default_event_handler,      // invalid_payment
    default_event_handler,      // valid_payment 
    default_event_handler,	    // manufacture_fail
    default_event_handler,		// manufacture_complete
    default_event_handler,		// received
    default_event_handler,		// lost_package
    default_action,             // entry
    default_action              // exit
};

state_t* order_received()
{
  resetAttempts();
}

#endif
