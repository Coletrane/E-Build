#ifndef hardware_c
#define hardware_c

#include <stdio.h>
#include "hardware.h"

static int attempts = 0;
static stats_t STATS;

// Transition functions
void resetAttempts()
{
  attempts = 0;
}
void incrementAttempts()
{
  attempts++;
}
void updateStats(stats_t stats);
{
  STATS = stats;
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
void showState(char * in){
 printf("Current state is: ");
 switch (in){
  	case 'O': 
	  printf("PROCESSING\n");
	  break;
	case 'V':
	 printf("MANUFACTURING\n");
	 break;
	case 'I':
	 printf("ACCEPTING\n");
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
