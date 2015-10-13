#ifndef shipping_c
#define shipping_c

#include "shipping.h"
#include "hardware.h"
#include "statemodel.h"

state_t shipping = {
    default_event_handler,      // order_received
    default_event_handler,      // invalid_payment
    default_event_handler,      // valid_payment 
    default_event_handler,	    // manufacture_fail
    default_event_handler,		  // manufacture_complete
    received,					          // received
    lost_package,				        // lost_package
    entry_to,                   // entry
    default_action              // exit
};

state_t* lost_package()
{
  refund();
  updateStats(LOST);
  return &accepting;
}

state_t* received()
{
  startWarranty();
  updateStats(DONE);
  return &accepting;
}

void entry_to()
{
  getAddress();
}

#endif
