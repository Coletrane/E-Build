
#include "supervisor.h"
#include "message.h"

int main(int argc, char * argv[])
{
	int num_lines = atoi(argv[0]);
	// Create shared memory
    key_t shmkey = SHM_KEY;
    int shmflg = IPC_CREAT | S_IRUSR | S_IWUSR;
    int shmid = shmget(shmkey, SHM_SIZE, shmflg);
    if (shmid != -1)
    {
        printf("Supervisor: shared memory segment with id: %d has been created successfully\n", shmid);
    }
    else
    {
        printf("Supervisor: %d failed to create a shared memory segment\n");
        exit(-1);
    }

    // Attach shared memory
    shared_data *shared = (shared_data *) shmat(shmid, NULL, 0);

    int queueID;
    int msgStatus;
    int linesActive = NUM_LINES;

    message_buffer msg;
    key_t msgQueueKey;
    msgQueueKey = BASE_MAILBOX_NAME;
    queueID = msgget(msgQueueKey, IPC_CREAT | 0600);

    if (queueID < 0) {
		sprintf("Failed to create mailbox %X. Error code=%d\n", msgQueKey , errno ) ;
		exit(-2);
	} 

	sem_post(&shared->message_ready);	
	
	while (linesActive > 0 ){
		printf ("\nWaiting to receive message ...\n" );
		msgStatus = msgrcv(queueID, &msg, MSG_INFO_SIZE, 1, 0);
	
		if ( msgStatus < 0 )
		{
			printf("Failed to receive message from User process on queueID %d. Error code=%d\n", queueID , errno ) ;
			exit(-2) ;
		}
		if (msg.mtype == 1) { //message is production
			shared->iterations[msg.info.factory_id - 1] += msg.info.iterations;
			shared->items_built[msg.info.factory_id - 1] += msg.info.num_items;

		}
		else if (msg.mtype == 2) { //message is termination
			linesActive--;
		}
		else {
			printf("Unsupported Message received, will be discarded.\n");
		}
	}
	
	sem_post(&shared->prod_running);

	sem_wait(&shared->print_report);

	int i = 0;
	for (i = 0, i < 5, i++){
		printf("Iterations performed by line %d: %d\n", i+1, shared->iterations[i]);
		printf("Items built by line %d: %d\n", i+1, shared->iterations[i]);
	}

	sem_post(&shared->done);

	/* 
	Inform parent that lines are done
	Wait for permission to print production aggregates
	Print prod agg
	Inform that supervisor is done
	Exit
	*/

	return 0;
}
