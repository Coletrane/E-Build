#ifndef statemodel_c
#define statemodel_c

#include "statemodel.h"
#include <stdlib.h>
#include <stdio.h>

// Define the initial state.
static state_t* current_state = &accepting;

void handle_event(event_t current_event)
{
    state_t* next_state;

    next_state = NULL;
    switch( current_event ) // exit current_state and have the appropriate effect
    {
        case OrderRcvd:
            next_state = current_state->order_rcvd();
            break;
        case InvalidPymnt:
            next_state = current_state->invalid_pymnt();
            break;
        case ValidPymnt:
            next_state = current_state->valid_pymnt();
            break;
        case ManufFailed:
            next_state = current_state->manuf_failed();
            break;
        case ManufCompleted:
            next_state = current_state->manuf_completed();
            break;
        case LostPackage:
            next_state = current_state->lost_package();
            break;
        case Received:
            next_state = current_state->received();
    }

    if (next_state != NULL)
    {
        current_state = next_state; // Change states
        current_state->entry_to();  // enter the new state
    }
}

#endif
