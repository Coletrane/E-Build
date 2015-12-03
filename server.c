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
	struct sockaddr_in fsin;
	snd_t *snd;
	rcv_t *rcv;
	unsigned short port = 47;
	int sock;
	unsigned int alen;
	int num_complete = 0;



	order_init();

	sock = serverUDPsock(port);

	printf("Order Size: %d\n", order_size);
	printf("Server waiting...\n");
	while (1)
	{
		if (recvfrom(sock, rcv, sizeof(rcv_t), 0, (SA *) &fsin, sizeof(fsin)) > 0)
		{
			printf("Recieved!\n");
			switch (rcv->msg_code)
			{
				case 1 :
					client_count++;
					printf("Received Message Code: 1 initializing client: %d\n",
							client_count);
					init_client_params(&client[client_count], client_count);
					snd->msg_code = 1;
					snd->param.cap = client[rcv->client_id].cap;
					snd->param.dur = client[rcv->client_id].dur;
					printf("Sending to Client: %d Message Code: 1 (Initialize Client)\n",
							rcv->client_id);
					sendto(sock, (void *) snd, sizeof(snd_t), 0, (SA *) &fsin,
							sizeof(fsin));
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
								(SA *) &fsin, sizeof(fsin));
					}
					else if (order_size < client[rcv->client_id].cap && order_size > 0)
					{
						snd->num_make = order_size;
						printf("Sending to Client: %d Make Request for %d items\n",
								rcv->client_id, snd->num_make);
						sendto(sock, (void *) snd, sizeof(snd_t), 0,
								(SA *) &fsin, sizeof(fsin));
					}
					else
					{
						snd->num_make = 0;
						printf("Sending to Client: %d Message Code: 2 Stop Request\n",
								rcv->client_id);
						sendto(sock, (void *) snd, sizeof(snd_t), 0,
								(SA *) &fsin, sizeof(fsin));
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
