#ifndef processing_c
#define processing_c

#include "processing.h"
#include "statemodel.h"

state_t processing = {

};

state_t* invalid_pymnt();
{
  if (attempts < LIMIT)
  {
    incrementAttempts();
    return &processing
  }
  else
    return &accepting;

}

state_t* valid_pymnt();
{
  return &manufacturing;
}

void entry_to()
{
  getPymntMethod();
}

#endif
