#ifndef statemodel_c
#define statemodel_c

#include "statemodel.h"
#include <stdlib.h>
#include <stdio.h>

// Define the initial state.
static state_t* current_state = &accepting;

void handle_event(event_t current_event)
{
    state_t * next_state;

    next_state = NULL;
    switch( current_event ) // exit current_state and have the appropriate effect
    {
        case ORDER_RECEIVED:
            next_state = current_state->order_received();
            break;
        case INVALID_PAYMENT:
            next_state = current_state->invalid_payment();
            break;
        case VALID_PAYMENT:
            next_state = current_state->valid_payment();
            break;
        case MANUFACTURE_FAIL:
            next_state = current_state->manufacture_fail();
            break;
        case MANUFACTURE_COMPLETE:
            next_state = current_state->manufacture_complete();
            break;
        case LOST_PACKAGE:
            next_state = current_state->lost_package();
            break;
        case RECEIVED:
            next_state = current_state->received();
    }

    if (next_state != NULL)
    {
        current_state = next_state; // Change states
        current_state->entry_to();  // enter the new state
    }
}

#endif
