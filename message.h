#include <sys/types.h>
#include <string.h>

#define MAXNAMELEN 20

typedef struct {
	long mtype ; /* 1: Production , 2: Termination */
	struct {
		pid_t sender  ; 
		int factory_ID;
		int capacity  ; 
		int duration  ; 
		int result    ; 
	} info ;
} message_buffer ;

#define MSG_INFO_SIZE ( sizeof(message_buffer) - sizeof(long) )

#define BASE_MAILBOX_NAME 0x20

void printMsg( message_buffer *m ) ;