#ifndef statemodel_c
#define statemodel_c

#include "statemodel.h"
#include <stdlib.h>
#include <stdio.h>

// Define the initial state.
static state_t* current_state = &accepting;

void handle_event(event current_event)
{
    state_t * next_state;

    next_state = NULL;
    printf("Handling event\n");
    switch( current_event ) // exit current_state and have the appropriate effect
    {
        case ORDER_RECEIVED:
            printf("Order received\n");
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
            break;
        default:
            printf("event handling failure\n");
            break;
    }

    if (next_state != NULL)
    {
        current_state = next_state; // Change states
        current_state->entry_to();  // enter the new state
    }
    else {
        printf("next_state is null!\n");
    }
}

#endif
