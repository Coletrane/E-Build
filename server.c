#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "server.h"

int order_size = 0;
int ord_count = 0;		// Sentinel for calling srandom only once
int client_count = 0;

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

int main()
{
	struct sockaddr_in fsin;
	snd_t *snd;
	rcv_t *rcv;
	unsigned short port = 13;
	int sock;
	unsigned int alen;
	int num_complete = 0;


	order_init();

	sock = serverUDPsock(port);

	printf("Order Size: %d\n", order_size);
	printf("Server waiting...\n");
	while (1)
	{
		alen = sizeof(fsin);
		if (recvfrom(sock, rcv, sizeof(rcv_t), 0, (SA *) &fsin, &alen) > 0)
		{
			switch (rcv->msg_code)
			{
				case 1 :
					client_count++;
					printf("Received Message Code: 1 initializing client: %d\n",
							client_count);

					// Initialize client's parameters
					client[client_count].id = client_count;
					client[client_count].cap = random() % 491 + 10;
					client[client_count].dur = random() % 401 + 100;
					client[client_count].num_iter = 0;
					client[client_count].total_dur = 0;

					// Compose and send a message to the client
					snd->msg_code = 1;
					snd->param.cap = client[client_count].cap;
					snd->param.dur = client[client_count].dur;
					printf("Sending to Client: %d Message Code: 1 (Initialize Client)\n",
							rcv->client_id);
					sendto(sock, (void *) snd, sizeof(snd_t), 0, (SA *) &fsin,
							&alen);
					break;

				case 2 :
					printf("Received from Client: %d Message Code: 2 (Make Request)\n",
							rcv->client_id);
					if (order_size >= client[rcv->client_id].cap)
					{
						snd->num_make = client[rcv->client_id].cap;
						printf("Sending to Client: %d Make Request for %d items\n",
								rcv->client_id, snd->num_make);
						sendto(sock, (void *) snd, sizeof(snd_t), 0,
								(SA *) &fsin, &alen);
					}
					else if (order_size < client[rcv->client_id].cap && order_size > 0)
					{
						snd->num_make = order_size;
						printf("Sending to Client: %d Make Request for %d items\n",
								rcv->client_id, snd->num_make);
						sendto(sock, (void *) snd, sizeof(snd_t), 0,
								(SA *) &fsin, &alen);
					}
					else
					{
						snd->num_make = 0;
						printf("Sending to Client: %d Message Code: 2 Stop Request\n",
								rcv->client_id);
						sendto(sock, (void *) snd, sizeof(snd_t), 0,
								(SA *) &fsin, &alen);
					}
					break;

				case 3 :
					printf("Received from Client: %d Message Code: 3 (Completed Iteration)\n",
							rcv->client_id);
					client[rcv->client_id].num_iter++;
					client[rcv->client_id].num_made += rcv->num_made;
					client[rcv->client_id].total_dur += client[rcv->client_id].total_dur;
					break;
			}
		}

	}
}
