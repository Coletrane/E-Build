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
	client_param param;
	int s, n;
	struct sockaddr_in fsin;
	int alen = sizeof(fsin);


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
	//snd->msg_code = 1;
	fprintf(stderr, "Client asking server for information\n");
	send(s, (void *) snd, sizeof(msg_t)+1, 0);

	// Receive message from server
	fprintf(stderr, "Waiting on server...\n");
	n = recv(s, (void *) rcv, sizeof(msg_t)+1, 0);
	if (n <= 0)
		err_sys("Failed to get init message from server");

	param.id = rcv->param.id;
	param.cap = rcv->param.cap;
	param.dur = rcv->param.dur;
	param.num_made = 0;
	param.num_iter = 0;
	param.total_dur = 0;

	// Compose and send production request
	snd->msg_code = 2;
	send(s, (void *) snd, sizeof(msg_t)+1, 0);

	// While the server responds or sends a valid message code
	while (recvfrom(s, rcv, sizeof(msg_t), 0, (SA *) &fsin, &alen) > 0)
	{
		switch (rcv->msg_code)
		{
			case 0:
				break;

			case 1:
				printf("Received Message Code: 1 (Make total capacity)\n");
				param.num_made += param.cap;
				param.total_dur += param.dur;
				param.num_iter++;
				usleep(param.dur * 1000);

				// Compose and send completion message to the server
				snd->msg_code = 3;
				snd->client_id = param.id;
				snd->num_make = param.cap;
				send(s, (void *) snd, sizeof(msg_t)+1, 0);
				break;

			case 2:
				printf("Received Message Code: 1 (Make partial capacity)\n");
				param.num_made += rcv->num_make;
				param.total_dur += param.dur;
				param.num_iter++;
				usleep(param.dur * 1000);

				// Compose and send completion message to the server
				snd->msg_code = 3;
				snd->client_id = param.id;
				snd->num_make = param.cap;
				send(s, (void *) snd, sizeof(msg_t)+1, 0);
				break;
		}

		// Compose and send production request
		snd->msg_code = 2;
		send(s, (void *) snd, sizeof(msg_t)+1, 0);
	}
	
	printf("Line: %d Total iterations: %d Total items: %d Total duration: %d\n",
			param.id, param.num_iter, param.num_made, param.total_dur);
	printf("Line: %d has completed its portion of the order\n", param.id);


}
