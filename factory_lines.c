#include "factory_lines.h"
#include "message.h"

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
    message_buffer snd_msg, rcv_msg;

    // Assign parameters from command line input 
    if (argc > 0)
    {
        param->factory_id = atoi(argv[0]);
        param->capacity = atoi(argv[1]);
        param->duration = atoi(argv[2]);
        printf("Factory line: %d created with capacity: %d and duration: %d\n",
                param->factory_id, param->capacity, param->duration);
    }
    else
    {
        printf("\nPlease enter 3 integer arguments\n");
        exit(-1);
    }
    param->iterations = 0;
    param->num_items = 0;
    param->first_line_closed = 0;

    // Create shared memory 
    shmkey = SHM_KEY;
    shmflg = IPC_CREAT | S_IRUSR | S_IWUSR;
    shmid = Shmget(shmkey, SHM_SIZE, shmflg, param->factory_id);

    // Attach shared memory
    shared = (shared_data *) Shmat(shmid, NULL, 0);

    // Create message queue
    int queueID, msgStatus, result;
    message_buffer msg;
    key_t msgQueueKey;
    msgQueueKey = BASE_MAILBOX_NAME;
    queueID = msgget(msgQueueKey, IPC_EXCL | 0600);

    if (queueID < 0) {
        printf("Failed to create mailbox %X. Error code=%d\n", msgQueueKey , errno ) ;
        exit(-2);
    }
    else
    {
        printf("Factory line: %d mailbox created successfully with id: %d\n",
                param->factory_id, queueID);
    }

    // Loop until order is complete
    while (shared->order_size > 0)
    {
        // Iterations 1 to n-1
        if (shared->order_size > param->capacity)
        {
            // Lock semaphore to update order_size
            sem_wait(&shared->fact_using);
            printf("Factory line: %d order size: %d\n",
                    param->factory_id, shared->order_size);
            shared->order_size -= param->capacity;
            printf("Factory line: %d order size: %d\n",
                    param->factory_id, shared->order_size);
            sem_post(&shared->fact_using);

            // Update params
            param->iterations++;
            param->num_items += param->capacity;
            printf("Factory line: %d Iterations: %d Parts Made: %d\nMaking parts...\n",
                    param->factory_id, param->iterations, param->num_items);
            usleep(param->duration * 1000);

            // Send message of params to supervisor
            snd_msg.mtype = 1;
            snd_msg.info = *param;
            printf("Factory Line: %d Sending message to supervisor with code: %d\n\n",
                    param->factory_id, snd_msg.mtype);
            msgsnd(queueID, &snd_msg, MSG_INFO_SIZE, 0);
        }
        // Last iteration
        else
        {
            // Lock semaphore to update order_size
            sem_wait(&shared->fact_using);
            param->num_items += shared->order_size;
            printf("Factory line: %d order size: %d\n",
                    param->factory_id, shared->order_size);
            shared->order_size = 0;

            // Send message about order_size
            sem_post(&shared->fact_using);
            printf("Factory line: %d order size: %d\n",
                    param->factory_id, shared->order_size);

            // Update lines' parameters
            param->iterations++;
            printf("Factory line: %d Iterations: %d Parts Made: %d\nMaking parts...\n",
                    param->factory_id, param->iterations, param->num_items);
            usleep(param->duration * 1000);

            // Send message of params to supervisor
            snd_msg.mtype = 2;
            snd_msg.info = *param;
            printf("Factory line: %d sending message to supervisor with code: %d\n\n",
                    param->factory_id,snd_msg.mtype);
            msgsnd(queueID, &snd_msg, MSG_INFO_SIZE, 0);
            param->first_line_closed = 1;
        }
    }
    // Terminate remaining lines
    if (param->first_line_closed == 0)
    {
        snd_msg.mtype = 2;
        snd_msg.info = *param;
        printf("Factory line: %d Sending message to supervisor with code: %d\n\n",
                param->factory_id, snd_msg.mtype);
        msgsnd(queueID, &snd_msg, MSG_INFO_SIZE, 0);
     }
     //if (shared->lines_active == 0)
        //    sem_post(&shared->line_finish);
}


