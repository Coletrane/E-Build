#ifndef shipping_c
#define shipping_c

#include "shipping.h"
#include "statemodel.h"

state_t* lost_package()
{
  Refund();
  UpdateStats(LOST);
  return &accepting;
}

state_t* received()
{
  StartWarranty();
  UpdateStats(DONE);
  return &accepting;
}

void entry_to()
{
  getAddress();
}

#endif
