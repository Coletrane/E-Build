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

    message_buffer snd_msg, rcv_msg;
    key_t msgQueueKey;
    int msgFlg = IPC_CREAT | 0600;
    msgQueueKey = BASE_MAILBOX_NAME;
    queueID = msgget(msgQueueKey, msgFlg);

    if (queueID < 0) {
		printf("Failed to create mailbox %X. Error code=%d\n", msgQueueKey , errno ) ;
		exit(-2);
	} 
    else
    {
    	printf("Supervisor: mailbox created with id: %d\n", queueID);
    }

	//let hardware know that message queue is ready
	sem_post(&shared->message_ready);

	while (linesActive > 0 ){
		printf ("\nSupervisor: waiting to receive message. Lines active: %d\n",
				linesActive);
		msgStatus = msgrcv(queueID, &rcv_msg, MSG_INFO_SIZE, 0, 0);
	
		if ( msgStatus < 0 )
		{
			printf("Failed to receive message from User process on queueID %d. Error code=%d\n", queueID , errno ) ;
			exit(-2) ;
		}
		if (rcv_msg.mtype == 1) { //message is production
			printf("Message received from Factory line : %d with code: %d\n",
					rcv_msg.info.factory_id, rcv_msg.mtype);
			printf("Updating production log...\n");
			shared->iterations[rcv_msg.info.factory_id] = rcv_msg.info.iterations;
			shared->items_built[rcv_msg.info.factory_id] = rcv_msg.info.num_items;
		}
		else if (rcv_msg.mtype == 2) { //message is termination
			printf("Message received from Factory line : %d with code: %d\n",
					rcv_msg.info.factory_id, rcv_msg.mtype);
			printf("Terminating Factory line: %d\n", rcv_msg.mtype);
			linesActive--;
		}
		else {
			printf("Unsupported Message received, will be discarded.\n");
		}
	}
	//Let parent know that all production lines have completed
	sem_post(&shared->prod_running);

	//Wait for signal to print report
	sem_wait(&shared->print_report);

	int i;
	for (i = 1; i <= NUM_LINES; i++)
	{
		printf("Factory line: %d Total iterations: %d	Total items made: %d\n",
				i, shared->iterations[i], shared->items_built[i]);
	}
	//Let parent know it's done
	sem_post(&shared->done);

	/*
	Inform parent that lines are done
	Wait for permission to print production aggregates
	Print prod agg
	Inform that supervisor is done
	Exit
	*/

	exit(0);
}
