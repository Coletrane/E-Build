#ifndef shmem_ex_h
#define shmem_ex_h

#include <semaphore.h>
#include <sys/shm.h>
#include <sys/stat.h>

typedef struct {
    int sarted;
    int finished;
    int order_size;
    sem_t *mutex;
} shared_data;

#define SHMEM_KEY 0x100
#define SHMEM_SIZE sizeof(shared_data)

#endif
