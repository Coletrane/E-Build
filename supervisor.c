
#include "supervisor.h"

int main(int argc, char * argv[]){
	superID = fork();
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
		*/
	}
	return 0;
}