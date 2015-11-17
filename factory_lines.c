#include "factory_lines.h"

// Wrapper for shmget(3)
int Shmget(key_t key, size_t size, int shmflg, int factory_id)
{
    int id = shmget(key, size, shmflg);
    if (id != -1)
    {
        printf("Factory line: %d's shared memory segment with id: %d has been created successfully\n", factory_id, id);
    }
    else
    {
        printf("Factory line: %d failed to create a shared memory segment\n", factory_id);
        exit(-1);
    }

    return id;
}

// Wrapper for shmat(3)
void *Shmat(int shmid, const void *shmaddr, int shmflg)
{
    shared_data *p = (shared_data *) shmat(shmid, shmaddr, shmflg);
    if (p == (shared_data *) -1)
    {
        printf("\nFailed to attach shared memory id %d\n", shmid);
        exit(-1);
    }  
}

int main(int argc, char *argv[])
{
    
    char *p;
    line_params *param;
    key_t shmkey;
    int shmflg;
    int shmid; 
    shared_data *shared;

    // Assign parameters from command line input 
    if (argc > 0)
    {
        param->factory_id = strtol(argv[1], &p, 10);
        //param->capacity = strtol(argv[2], &p, 10);
        //param->duration = strtol(argv[3], &p, 10);
    }
    else
    {
        printf("\nPlease enter 3 integer arguments\n");
        exit(-1);
    }

    // Create shared memory 
    shmkey = SHM_KEY;
    shmflg = IPC_CREAT | S_IRUSR | S_IWUSR;
    shmid = Shmget(shmkey, SHM_SIZE, shmflg, param->factory_id);

    // Attach shared memory
    shared = (shared_data *) Shmat(shmid, NULL, 0);
    
    // TEMPORARY SEMAPHORE INIT
    sem_init(&shared->mutex, 1, 0);

    // Loop until order is complete
    while (shared->order_size > 0)
    {
        // Iterations 1 to n-1
        if (shared->order_size > param->capacity)
        {
            // Lock mutex to update order_size
            sem_wait(&shared->mutex);
            shared->order_size -= param->capacity;
            // send message about order_size
            sem_post(&shared->mutex);

            param->iterations++;
            param->num_items += param->capacity;
            sleep(param->duration);
            // Send message iterations, durations
        }
        // Last iteration
        else
        {
            param->num_items += shared->order_size;
            // Lock mutex to update order_size
            sem_wait(&shared->mutex);
            shared->order_size = 0;
            // Send message about order_size
            sem_post(&shared->mutex);
            
            // Update lines' parameters
            param->iterations++;
            sleep(param->duration);
            // Send message iterations, durations
        }
    }
    
}


