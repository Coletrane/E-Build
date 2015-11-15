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

typedef struct {
    int sarted;
    int finished;
    int order_size;
    sem_t *mutex;
} shared_data;


state_t*  manufacture_fail();
state_t*  manufacture_complete();
void      entry_to();
void      exit_from();

#endif
