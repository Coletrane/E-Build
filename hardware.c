#ifndef hardware_c
#define hardware_c

#include <stdio.h>
#include "hardware.h"
#include "manufacturing.h"

#define THREADS 5      //5 Total manufacturing lines

int attempts = 0;
static stats_t STATS;

int ord_count = 0;
int order_size = 0;

void *thread(thread_params_t *param);

// Order functions
void order_init()
{
	if (ord_count == 0)
	{
		srandom(time(NULL));
		ord_count++;
	}
	order_size = (random() % 1001) + 1000;
}

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
    printf("The user should enter a valid payment method.\n");
}
void dispatchFactoryLines()
{
    order_t ord;
    order_init(&ord);
    int i;
    for (i = 0; i < THREADS; i++)
    {

    }
    //printf("Factory line has been dispatched.\n");
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

void *thread(thread_params_t *param)
{
    param->capacity = (random() % 41) + 10;
		param->duration = (random() % 5) + 1;
}
#endif
