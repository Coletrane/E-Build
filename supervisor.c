
#include "supervisor.h"
#include "message.h"

int main(int argc, char * argv[])
{

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
    int iterations = 0;
    int items_built = 0;

    message_buffer msg;
    key_t msgQueueKey;
    msgQueueKey = BASE_MAILBOX_NAME;
    queueID = msgget(msgQueueKey, IPC_CREAT | 0600);

    if (queueID < 0) {
		sprintf("Failed to create mailbox %X. Error code=%d\n", msgQueKey , errno ) ;
		exit(-2);
	} 

	sem_init(&shared->prod_running, 1, 0);
	
	while (linesActive > 0 ){
		printf ("\nWaiting to receive message ...\n" );
		msgStatus = msgrcv(queueID, &msg, MSG_INFO_SIZE, 1, 0);
	
		if ( msgStatus < 0 )
		{
			sprintf("Failed to receive message from User process on queuID %d. Error code=%d\n", queID , errno ) ;
			exit(-2) ;
		}
		if (mtype == 1) { //message is production
			iterations += msg.info.iterations;
			items_built += msg.info.num_items;

		}
		else if (mtype == 2) { //message is termination
			linesActive--;
		}
		else {
			sprintf("Unsupported Message received, will be discarded.\n");
		}
	}
	
	sem_post(&shared->prod_running);
	
	
	/* 
	Inform parent that lines are done
	Wait for permission to print production aggregates
	Print prod agg
	Inform that supervisor is done
	Exit
	*/

	return 0;
}
