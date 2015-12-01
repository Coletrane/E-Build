#include "server.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mySock.h"

#define NUM_CLIENTS 5

typedef struct {
	int id;
	int cap;
	int dur;
	int num_made;
	int iter;
} client_param;

client_param client[NUM_CLIENTS];
int order_size = 0;

// Order function: generates random seed and random order size
void order_init()
{
	if (ord_count == 0)
	{
		srandom(time(NULL));
		ord_count++;
	}
	order_size = random() % 1001 + 1000;
}

void init_client_params(client_param *client, int id)
{
	client->id = id;
	client->cap = random() % 491 + 10;
	client->dur = random() % 401 + 100;
}

int main()
{
	struct sockaddr_in fsin[NUM_CLIENTS];
	char buf[MAXBUFLEN];
	unsigned short port = BASEPORT;
	int sock;
	unsigned int alen;

	order_init();

	sock = serverUDPsock(port);

	while (1)
	{
		if (order_size == 0)
			break;

		alen = sizeof(fsin);
		printf("Server waiting...\n");

		// Receive message
		// Message format:  Index 0 = message code
		//					Index 1 = client id
		//					Index 2 =
		if (recv(sock, buf, MAXBUFLEN, 0) > 0)
		{
			int mcode = atoi(buf[0]);
			switch (mcode)
			{
				case 1 :
					int id = atoi(buf[0]);
					init_client_params(&client[id], id);
					break;

				case 2 :
					int cid = atoi(buf[1]);
					char snd[MAXBUFLEN];
					// Message format:  Index 0 = message code
					//					Index 1..n = num items to make
					if (order_size >= client[cid].cap)
					{
						snd = "1";
						sendto(sock, snd, MAXBUFLEN, 0, fsin[cid], sizeof(fsin[cid]));
					}
					else if (order_size < client[cid].cap)
					{
						char c[20] = client[cid].cap + '0';
						snd = '2', c;
						//sendto(sock,)
					}
			}
		}

	}
}
