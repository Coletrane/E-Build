#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "server.h"

int order_size = 0;
int ord_count = 0;		// Sentinel for callng srandom only once

// Order function: generates random seed and random order size
void order_init()
{
	if (ord_count == 0)
	{
		srandom(time(NULL));
		ord_count++;
	}
	order_size = random() % 40001 + 10000;
}

void init_client_params(client_param *client, int id)
{
	client->id = id;
	client->cap = random() % 491 + 10;
	client->dur = random() % 401 + 100;
	client->num_iter = 0;
	client->total_dur = 0;
}

int main()
{
	struct sockaddr_in fsin[NUM_CLIENTS +1];
	server_snd snd;
	server_rcv rcv;
	unsigned short port = BASEPORT;
	int sock;
	unsigned int alen;
	int num_complete = 0;

	order_init();

	sock = serverUDPsock(port);

	while (1)
	{
		printf("Server waiting...\n");

		if (recv(sock, &rcv, sizeof(server_rcv), 0) > 0)
		{
			switch (rcv.msg_code)
			{
				case 1 :
					printf("Received from Client: %d Message Code: 1 (Init Client)\n",
							rcv.client_id);
					init_client_params(&client[rcv.client_id], rcv.client_id);
					snd.msg_code = 1;
					snd.init_cap = client[rcv.client_id].cap;
					snd.init_dur = client[rcv.client_id].dur;
					printf("Sending to Client: %d Message Code: 1 (Initialize Client)\n",
							rcv.client_id);
					sendto(sock, &snd, sizeof(server_snd), 0, (SA *) &fsin[rcv.client_id],
							sizeof(fsin[rcv.client_id]));
					break;

				case 2 :
					printf("Received from Client: %d Message Code: 2 (Make Request)\n",
							rcv.client_id);
					if (order_size >= client[rcv.client_id].cap)
					{
						snd.num_make = client[rcv.client_id].cap;
						printf("Sending to Client: %d Make Request for %d items\n",
								rcv.client_id, snd.num_make);
						sendto(sock, &snd, sizeof(server_snd), 0,
								(SA *) &fsin[rcv.client_id], sizeof(fsin[rcv.client_id]));
					}
					else if (order_size < client[rcv.client_id].cap && order_size > 0)
					{
						snd.num_make = order_size;
						printf("Sending to Client: %d Make Request for %d items\n",
								rcv.client_id, snd.num_make);
						sendto(sock, &snd, sizeof(server_snd), 0,
								(SA *) &fsin[rcv.client_id], sizeof(fsin[rcv.client_id]));
					}
					else
					{
						snd.num_make = 0;
						printf("Sending to Client: %d Message Code: 2 Stop Request\n",
								rcv.client_id);
						sendto(sock, &snd, sizeof(server_snd), 0,
								(SA *) &fsin[rcv.client_id], sizeof(fsin[rcv.client_id]));
					}
					break;

				case 3 :
					printf("Received from Client: %d Message Code: 3 (Completed Iteration)\n",
							rcv.client_id);
					client[rcv.client_id].num_iter++;
					client[rcv.client_id].num_made += rcv.num_made;
					client[rcv.client_id].total_dur += client[rcv.client_id].total_dur;
					break;
			}
		}

	}
}
