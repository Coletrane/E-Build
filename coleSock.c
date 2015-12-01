
typedef struct sockaddr SA;
#define BASEPORT 50000
#define MAXBUFLEN 256
#define MAXMSGLEN 256


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mySock.h"

int serverUDPsock(const unsigned short port)
{
	struct sockaddr_in sin;
	int s;
	char msg[MAXMSGLEN];

	memset((void*) &sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port+BASEPORT);

	// Allocate socket
	s = socket(AF_INET, SOCK_DGRAM, 0);
	// Check for errors
	if (s < 0)
	{
		printf("Failed to create socket\n");
		exit(-2);
	}

	// Bind socket
	if (bind(s, (SA *) &sin, sizeof(sin)) < 0)
	{
		printf("Cant bind to port %d\n", port);
		exit(-2);
	}

	printf("Bound socket %d to port %d\n", s, ntohs(sin.sin_port));
	ntohs(sin.sin_port);

	return s;
}
