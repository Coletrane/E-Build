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
			break;
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr, "usage %s [host[port]]\n", argv[0]);
			exit(1);
	}
	sock = clientUDPsock(host, service);

	snd_t snd;
	rcv_t rcv;
	snd.msg_code = 1;

	fprintf(stderr, "Client asking server for information");
	send(sock, &send, sizeof(snd_t), 0 );

	fprintf(stderr, "waiting on server\n");
	n = recv(sock, &rcv, sizeof(snd_t), 0);
	if (n <= 0)
		err_sys("Failed to get init message from server");

	

}
