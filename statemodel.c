#ifndef statemodel_c
#define statemodel_c

#include "statemodel.h"
#include <stdlib.h>
#include <stdio.h>

// Define the initial state.
static state_t* current_state = & opened; 

void handle_event( event current_event)
{
    state_t* next_state;

    next_state = NULL;
    switch( current_event ) // exit current_state and have the appropriate effect
    {
        case CLOSE_BUTTON_PRESSED:
            next_state = current_state->close_button_pressed();
            break;
        case CLOSED_DETECTED:
            next_state = current_state->closed_detected();
            break;
        case OPEN_BUTTON_PRESSED:
            next_state = current_state->open_button_pressed();
            break;
        case OPENED_DETECTED:
            next_state = current_state->opened_detected();
            break;
    }

    if (next_state != NULL)
    {
        current_state = next_state; // Change states
        current_state->entry_to();  // enter the new state
    }
}

#endif
