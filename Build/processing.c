#ifndef processing_c
#define processing_c

#include <stdio.h>
#include "processing.h"
#include "hardware.h"
#include "statemodel.h"

state_t processing = {
    default_event_handler,      // order_received
    invalid_payment,      		// invalid_payment
    valid_payment,      		// valid_payment 
    default_event_handler,	    // manufacture_fail
    default_event_handler,		// manufacture_complete
    default_event_handler,		// received
    default_event_handler,		// lost_package
    entry_to,                   // entry
    default_action              // exit
};

state_t* invalid_payment()
{
  if (getAttempts() >= LIMIT)
  {
    printf("Current state is : ACCEPTING\n");
    return &accepting;
  }
  else
  {
    incrementAttempts();
    printf("Current state is: PROCESSING\n");
    return &processing;
  }
}

state_t* valid_payment()
{
  return &manufacturing;
}

void entry_to()
{
  getPaymentMethod();
}

#endif
