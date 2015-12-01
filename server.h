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
	int msg_code;
	int client_id;
	int num_made;
} server_rcv;

typedef struct {
	int msg_code;	// 1 = initialize capacity and duration, 2 = make items, 3 = make no more items
	int init_cap;
	int init_dur;
	int num_make;
} server_snd;

client_param client[NUM_CLIENTS + 1];	// Will not use 0
#endif
