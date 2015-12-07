#ifndef server_h
#define server_h

#include "mySock.h"

#define NUM_CLIENTS 5

typedef struct {
	int id;
	int cap;
	int dur;
	int num_made;
	int num_iter;
	int total_dur;
} client_param;

typedef struct {
	int msg_code;	// From Client: 0 = Stop 1 = initialize parameters, 2 = make items, 3 = production update
					// From Server: 0 = Stop 1 = make total capacity, 2 = make less than capacity
	int client_id;
	client_param param;
	int num_make;
} msg_t;

client_param client[NUM_CLIENTS + 1];	// Will not use 0
#endif
