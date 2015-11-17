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
#define SHM_KEY 10002
#define SHM_SIZE sizeof(shared_data)

typedef struct {
    int sarted;
    int finished;
    int order_size;
    sem_t mutex;
} shared_data;

state_t*  manufacture_fail();
state_t*  manufacture_complete();
void      entry_to();
void      exit_from();

#endif
