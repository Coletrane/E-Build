#ifndef hardware_c
#define hardware_c

#include <stdio.h>
#include "hardware.h"

int attempts = 0;
static stats_t STATS;

// Transition functions
void resetAttempts()
{
  attempts = 0;
  printf("Payment attempts reset\n");
}
void incrementAttempts()
{
  attempts++;
  printf("Invalid payment attempt #%d\n", attempts);
}
int getAttempts()
{
	return attempts;
}
void updateStats(stats_t stats)
{
  STATS = stats;
  switch (STATS) {
  	case FAIL:
  		printf("Status: Fail\n");
  		break;
  	case LOST:
  		printf("Status: Lost\n");
  		break;
  	case DONE:
  		printf("Status: Done\n");
  		break;
  	default:
  		break;
  }
}
void chargeClient()
{
 printf("The client's account has now been charged.\n"); 
}
void startWarranty()
{
 printf("The warranty on the product is now active.\n");
}
void refund()
{
 printf("The client's account has been refunded.\n");
}

// Entry/Exit functions
void getPaymentMethod()
{
 printf("The user should now enter the payment method.\n");
}
void dispatchFactoryLines()
{
 printf("Factory line has been dispatched.\n");
}
void shutDownFactoryLines()
{
 printf("Factory line has been shut down.\n");
}
void getAddress()
{
 printf("The user should now enter the order address.\n");
}
void show_state(char in){
 printf("Current state is: ");
 switch (in){
  	case 'O': 
	  printf("PROCESSING\n");
	  break;
	case 'V':
	 printf("MANUFACTURING\n");
	 break;
	case 'I':
	 printf("PROCESSING\n");
	 break;
	case 'F':
	 printf("ACCEPTING\n");
	 break;
	case 'C':
	 printf("SHIPPING\n");
	 break;
	case 'R':
	 printf("ACCEPTING\n");
	 break;
	case 'L':
	 printf("ACCEPTING\n");
	 break;
	default:
	 break;
 }
}
#endif
