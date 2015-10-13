#ifndef driver_c
#define driver_c

#include "statemodel.h"
#include <stdio.h>

int main()
{
	char * input = NULL;
	char * previous = 'O';

	while (input != 'X')
	{
		  	if (input == 'O')
		  	{
		  		handle_event(ORDER_RECEIVED);
		  	}
		  	else if (input == 'V')
		  	{
		  		if (previous == 'O' || previous == 'I')
		  		{
		  			handle_event(VALID_PAYMENT);
		  		} 
		  	}
		  	else if (input == 'I')
		  	{
		  		if (previous == 'O' || previous == 'I')
		  		{
		  			handle_event(INVALID_PAYMENT);
		  		} 
		  	}
		  	else if (input == 'F')
		  	{
		  		if (previous == 'V')
		  		{
		  			handle_event(MANUFACTURE_FAIL);
		  		} 
		  	}
		  	else if (input == 'C')
		  	{
		  		if (previous == 'V')
		  		{
		  			handle_event(MANUFACTURE_COMPLETE);
		  			show_state(input);
		  		} 
		  	}
		  	else if (input == 'R')
		  	{
		  		if (previous == 'C')
		  		{
		  			handle_event(RECEIVED);
		  			show_state(input);
		  		} 
		  	}
		  	else if (input == 'L')
		  		if (previous == 'C')
		  		{
		  			handle_event(LOST_PACKAGE);
		  			show_state(input);
		  		}
		  	scanf("%s", &input)	
 	} 
}
#endif
