#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mySock.h"
#include "client.h"

#define MAXBUFLEN 256

int main(int argc, char ** argv){
	char *host = argv[1];
	int port = atoi(argv[2]);
	char *service = "server";
	int sock;

	sock = clientUDPsock(port, service);

	snd_t send;
	snd_t receive;
	send.msg_code = 1;

	fprintf(stderr, "Client asking server for information");
	sendto(s, (void *) &send, sizeof(snd_t), NULL, 0 );

	fprintf(stderr, "waiting on server\n");
	n = recvfrom(s, (void *) receive, sizeof(snd_t), NULL, 0);
	if (n <= 0)
		err_sys("Failed to get init message from server");

	

}