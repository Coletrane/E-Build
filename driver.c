#ifndef driver_c
#define driver_c

#include "statemodel.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char input = NULL;
	event previous;

	printf("Enter input: ");
	input = getchar();

	while (input != 'X')
	{
	  	if (input == 'O')
	  	{
	  		if (previous != VALID_PAYMENT || previous != ORDER_RECEIVED || previous != MANUFACTURE_COMPLETE)
	  		{
	  			handle_event(ORDER_RECEIVED);
	  			show_state(input);
	  			previous = ORDER_RECEIVED;
	  		}	
	  	}
	  	else if (input == 'V')
	  	{
	  		if (previous == ORDER_RECEIVED || previous == INVALID_PAYMENT)
	  		{
	  			handle_event(VALID_PAYMENT);
	  			show_state(input);
	  			previous = VALID_PAYMENT;
	  		} 
	  	}
	  	else if (input == 'I')
	  	{
	  		if (previous == ORDER_RECEIVED || previous == INVALID_PAYMENT)
	  		{
	  			handle_event(INVALID_PAYMENT);
	  			previous = INVALID_PAYMENT;
	  		} 
	  	}
	  	else if (input == 'F')
	  	{
	  		if (previous == VALID_PAYMENT)
	  		{
	  			handle_event(MANUFACTURE_FAIL);
	  			show_state(input);
	  			previous = MANUFACTURE_FAIL;
	  		} 
	  	}
	  	else if (input == 'C')
	  	{
	  		if (previous == VALID_PAYMENT)
	  		{
	  			handle_event(MANUFACTURE_COMPLETE);
	  			show_state(input);
	  			previous = MANUFACTURE_COMPLETE;
	  		} 
	  	}
	  	else if (input == 'R')
	  	{
	  		if (previous == MANUFACTURE_COMPLETE)
	  		{
	  			handle_event(RECEIVED);
	  			show_state(input);
	  			previous = RECEIVED;
	  		} 
	  	}
	  	else if (input == 'L')
	  	{
	  		if (previous == MANUFACTURE_COMPLETE)
	  		{
	  			handle_event(LOST_PACKAGE);
	  			show_state(input);
	  			previous = LOST_PACKAGE;
	  		}
	  	} 
	  	input = getchar();	

 	}

 	return 0; 
}
#endif
