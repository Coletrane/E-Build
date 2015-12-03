#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include "mySock.h"
#include "client.h"

// 143 Lab IPs: 134.126.141.xx
#define MAXBUFLEN 256

int main(int argc, char *argv[]){
	char *host = "localhost";
	char *service = "server";
	msg_t *snd;
	msg_t *rcv;
	int s, n;


	switch (argc)
	{
		case 1:
			break;
		case 3:
			service = argv[2];
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr, "usage %s [host[port]]\n", argv[0]);
			exit(1);
	}
	printf("Host: %s\nService: %s\n", host, service);
	s = clientUDPsock(host, service);

	// Compose and send message to server for parameter initialization
	snd->msg_code = 1;
	fprintf(stderr, "Client asking server for information\n");
	send(s, (void *) snd, sizeof(msg_t)+1, 0);

	fprintf(stderr, "Waiting on server...\n");
	n = recv(s, (void *) rcv, sizeof(msg_t)+1, 0);

	if (n <= 0)
		err_sys("Failed to get init message from server");

	

}
