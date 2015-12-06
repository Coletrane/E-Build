#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "server.h"

int main()
{
	struct sockaddr_in fsin;
	msg_t snd;
	msg_t rcv;
	unsigned short port = 13;
	int sock;
	unsigned int alen;
	int running[NUM_CLIENTS + 1];
	int num_complete = 0;
	int client_count = 0;
	int i;
	int prod_not_done = 0;

	// Declare and initialize order size
	int order_size;
	srandom(time(NULL));
	order_size = random() % 40001 + 10000;

	sock = serverUDPsock(port);

	printf("Order Size: %d\n", order_size);
	printf("Server waiting...\n");
	while (1)
	{
		alen = sizeof(fsin);
		if (recvfrom(sock, &rcv, sizeof(msg_t), 0, (SA *) &fsin, &alen) > 0)
		{
			printf("Order size: %d\n", order_size);
			switch (rcv.msg_code)
			{
				case 0 :
					printf("Received from Client: %d Message Code: 0 (Client Finished)\n",
							rcv.client_id);
					running[rcv.client_id] = 0;
					break;
				case 1 :
					client_count++;
					running[client_count] = 1;
					printf("Received Message Code: 1 initializing client: %d\n",
							client_count);

					// Initialize client's parameters
					client[client_count].id = client_count;
					client[client_count].cap = random() % 491 + 10;
					client[client_count].dur = random() % 401 + 100;
					client[client_count].num_iter = 0;
					client[client_count].total_dur = 0;


					// Compose and send a message to the client
					snd.param.cap = client[client_count].cap;
					snd.param.dur = client[client_count].dur;
					snd.param.id = client_count;
					printf("Sending to Client: %d Message Code: 1 (Initialize Client)\n",
							client_count);
					sendto(sock, (msg_t *) &snd, sizeof(msg_t), 0, (SA *) &fsin, alen);
					printf("here\n");
					break;

				case 2 :
					printf("Received from Client: %d Message Code: 2 (Make Request)\n",
							rcv.client_id);
					if (order_size >= client[rcv.client_id].cap)
					{
						snd.msg_code = 1;
						snd.num_make = client[rcv.client_id].cap;
						printf("Sending to Client: %d Make Request granted for %d items\n",
								rcv.client_id, snd.num_make);

						sendto(sock, (msg_t *) &snd, sizeof(msg_t)+1, 0,
								(SA *) &fsin, alen);
					}
					else if (order_size < client[rcv.client_id].cap && order_size > 0)
					{
						snd.msg_code = 2;
						snd.num_make = order_size;
						printf("Sending to Client: %d Make Request granted for %d items\n",
								rcv.client_id, snd.num_make);
						sendto(sock, (msg_t *)&snd, sizeof(msg_t), 0,
								(SA *) &fsin, alen);
					}
					else
					{
						snd.num_make = 0;
						snd.msg_code = 0;
						printf("Sending to Client: %d Message Code: 0 Stop Request\n",
								rcv.client_id);
						sendto(sock, (msg_t *) &snd, sizeof(msg_t), 0,
								(SA *) &fsin, alen);
					}
					break;

				case 3 :
					printf("Received from Client: %d Message Code: 3 (Completed Iteration)\n",
							rcv.client_id);
					order_size -= rcv.num_make;
					client[rcv.client_id].num_iter++;
					client[rcv.client_id].num_made += rcv.num_make;
					client[rcv.client_id].total_dur += client[rcv.client_id].dur;
					break;
			}
			prod_not_done = 0;
			for (i = 1; i < NUM_CLIENTS + 1; i++)
			{
				if (running[i] == 1)
				{
					prod_not_done = 1;
				}
			}
			if (!prod_not_done){
				break;
			}
		}
	}
	//print information
	printf("Order Size: %d\n", order_size);
	for (i = 1; i < NUM_CLIENTS + 1; i++)
	{
		printf("Client %d has completed %d total items made in %d time in %d iterations.\n",
				client[i].id, client[i].num_made, client[i].total_dur, client[i].num_iter);
	}

	order_size = 0;

}
