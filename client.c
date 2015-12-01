#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mySock.h"
#include "client.h"

int main(int argc, char ** argv){
	char *host = argv[1];
	char *port = argv[2];
	char *service = "server";

	s = clientUDPsock(host, service);

	snd_t send;
	rcv_t receive;
	send.msg_code = 1;

	fprintf(stderr, "Client asking server for information");
	sendto(s, (void *) &send, sizeof(snd_t), NULL, 0)
}