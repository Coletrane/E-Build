#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "statemodel.h"

state_t* manuf_failed()
{
  updateStats(FAIL);
  return &accepting;
}

state_t* manuf_completed()
{
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
