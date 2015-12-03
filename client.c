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
	int sock, n;

	switch (argc)
	{
		case 1:
			break;
		case 3:
			service = argv[2];
			host = argv[1];
			break;
		case 2:
			break;
		default:
			fprintf(stderr, "usage %s [host[port]]\n", argv[0]);
			exit(1);
	}
	printf("Host: %s\nService: %s\n", host, service);
	sock = clientUDPsock(host, service);

	snd_t snd;
	rcv_t rcv;
	snd.msg_code = 1;

	fprintf(stderr, "Client asking server for information\n");
	sendto(sock, (void*) &send, sizeof(snd_t), NULL, 0);

	fprintf(stderr, "Waiting on server...\n");
	n = recvfrom(sock, (void*) &rcv, sizeof(snd_t), NULL, 0);
	printf("Here\n");
	if (n <= 0)
		err_sys("Failed to get init message from server");

	

}
