#ifndef supervisor_h
#define supervisor_h

#include "state.h"
#include "manufacturing.h"
#include "hardware.h"
#include "statemodel.h"
#include "factory_lines.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#define NUM_LINES 5
#define SHM_KEY 2323232
#define SHM_SIZE sizeof(shared_data)

typedef struct {
    int iterations[NUM_LINES + 1];
    int items_built[NUM_LINES + 1];
    int order_size;
 	int lines_active;
    sem_t fact_using;
    sem_t message_ready;
    sem_t prod_running;
    sem_t print_report; //init in Close
    sem_t done;
    sem_t line_finish;
} shared_data;

state_t*  manufacture_fail();
state_t*  manufacture_complete();
void      entry_to();
void      exit_from();

#endif
