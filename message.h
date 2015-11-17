#include <sys/types.h>
#include <string.h>
#include "factory_lines.h"

#define MAXNAMELEN 20

typedef struct {
	long mtype ; /* 1: Production , 2: Termination */
	line_params info;
} message_buffer ;

#define MSG_INFO_SIZE ( sizeof(message_buffer) - sizeof(long) )

#define BASE_MAILBOX_NAME 0x20

void printMsg( message_buffer *m ) ;