#ifndef hardware_c
#define hardware_c

#include <stdio.h>
#include "hardware.h"
#include "manufacturing.h"

#define THREADS 5               // 5 Total manufacturing lines

int attempts = 0;               // Payment attempts
static stats_t STATS;           // Order status

int ord_count = 0;              // Sentinel for calling srandom only once
int order_size = 0;             // [1000-2000]

pthread_mutex_t mutex;          // Mutex for manufacturing_line

void *manufacturing_line(void *);

// Order function: generates random seed and random order size
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
    // Pick a random order size [1000-2000]
    order_init();
    printf("Initial order size: %d\n", order_size);

    pthread_mutex_init(&mutex, NULL);    
        
    thread_params_t thrd_param[6];      //Will not use thrd_param[0] 
    pthread_t thread[6];
    
    // Init thread params and create the threads
    int i;
    for (i = 1; i < THREADS + 1; i++)
    {
        thrd_param[i].iterations = 0;
        thrd_param[i].num_items = 0;
        thrd_param[i].capacity = (random() % 41) + 10;
	    thrd_param[i].duration = (random() % 5) + 1;
        thrd_param[i].tid = i;
        pthread_create(&thread[i], NULL, manufacturing_line, &thrd_param[i]);  
    }
    
    // Wait for the threads to finish
    for (i = 1; i < THREADS + 1; i++)
    {
        pthread_join(thread[i], NULL);
    }
    
    //Confirm end of manufacturing
    printf("All parts manufactured.\n");
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

// Thread function
void *manufacturing_line(void *ptr)
{
    thread_params_t *param = ptr;
    
    printf("Factory line %d has been dispatched with capacity: %d and duration: %d\n"
            , param->tid, param->capacity, param->duration);

    while (order_size > 0)
    { 
        // Iterations 1 to n-1
        if (order_size > param->capacity)
        {
            // Lock mutex to update order_size
            pthread_mutex_lock(&mutex);
            order_size -= param->capacity;
            printf("Order size: %d\n", order_size);
            pthread_mutex_unlock(&mutex);
            
            // Update lines' parameters
            param->iterations++;
            param->num_items += param->capacity;
            sleep(param->duration);
            printf("Factory line %d iteration complete. All time iterations: %d All time parts made: %d\n"
                   ,param->tid, param->iterations, param->num_items); 
        }
        // Last iteration
        else 
        {
            // Lock mutex to update order_size
            param->num_items += order_size; 
            pthread_mutex_lock(&mutex);
            order_size = 0;
            printf("Order size: %d\n", order_size);
            pthread_mutex_unlock(&mutex);
            
            // Update lines' parameters
            param->iterations++;
            sleep(param->duration);
            printf("Factory line %d iteration complete. All time iterations: %d All time parts made: %d\n"
                   ,param->tid, param->iterations, param->num_items); 
        }       
    }
}
#endif
