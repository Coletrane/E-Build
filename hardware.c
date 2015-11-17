#ifndef hardware_c
#define hardware_c

#include <stdio.h>
#include "hardware.h"
#include "manufacturing.h"
#include "factory_lines.h"
#include "supervisor.h"

#define THREADS 5               // 5 Total manufacturing lines

int attempts = 0;               // Payment attempts
static stats_t STATS;           // Order status

int order_size = 0;				// Global since initialization is in another function
int ord_count = 0;              // Sentinel for calling srandom only once


// Order function: generates random seed and random order size
void order_init()
{
	if (ord_count == 0)
	{
		srandom(time(NULL));
		ord_count++;
	}
	order_size = rand() % 1001 + 1000;
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

    // Create shared memory
    key_t shmkey = SHM_KEY;
    int shmflg = IPC_CREAT | S_IRUSR | S_IWUSR;
    int shmid = shmget(shmkey, SHM_SIZE, shmflg);

    // Attach shared memory
    shared_data *shared = (shared_data *) shmat(shmid, NULL, 0);

    // Initialize semaphores
    sem_init(&shared->done, 1, 0);
    sem_init(&shared->fact_using, 1, 1);
    sem_init(&shared->print_report, 1, 0);
    sem_init(&shared->prod_running, 1, 0);
    sem_init(&shared->message_ready, 1, 0);

    // Initialize order_size in shared memory
    shared->order_size = order_size;
    printf("Initial order size: %d\n", shared->order_size);

    // Variables for exec functions
	const char *lines = "factory_lines";
	const char *super = "supervisor";
	char temp[20];
	char cap[20];
	char dur[20];

	// Fork Supervisor
	char line[20];
	int ln = NUM_LINES;
	sprintf(line, "%d", ln);
	pid_t pid = fork();
	execl(super, "5");

	// Wait for message queue to be initialized
	sem_wait(&shared->message_ready);

	// Fork Lines
	int i;
	for (i = 1; i < NUM_LINES + 1; i++)
	{
		int capi = rand() % 41 + 10;
		sprintf(cap, "%d", capi);

		int duri = rand() % 401 + 100;
		sprintf(dur, "%d", duri);

		pid_t pid = fork();
		if (pid == 0)
		{
			sprintf(temp,"%d", i);

			wait(4);
			execl(lines, temp, cap, dur);
		}
	}

    //Confirm end of manufacturing
	sem_wait(&shared->prod_running);
    printf("All parts manufactured.\n");
    shutDownFactoryLines(shared);

}
void shutDownFactoryLines(shared_data *shared)
{
    printf("Factory line has been shut down.\n");
    sem_post(&shared->print_report);
    sem_wait(&shared->done);
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
