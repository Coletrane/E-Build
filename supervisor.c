
#include "supervisor.h"

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
/**
	if (superID == 0) {
		if ( excelp("gnome-terminal", "supervisor", "-x", 
					"/bin/bash", "-c", "./supervisor 5", NULL) < 0) {
			perror("excelp Supervisor failed.");
			exit(-1);
		}
		int linesActive = 5;
		/* 
		Recieve message from mailbox
		if (ProdMsg)
			updateProductionAggregates(num-items-built, num-iterations)
		elif (TerminateMsg)
			LinesActive--
		else
			discard(UnsupportedMsg)

		Inform parent that lines are done
		Wait for permission to print production aggregates
		Print prod agg
		Inform that supervisor is done
		Exit

	}*/
	return 0;
}
