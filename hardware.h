#ifndef hardware_h
#define hardware_h

#define LIMIT 3 

typedef struct {
	int capacity;
	int duration;
    pthread_t tid;
} thread_params_t;

typedef enum {
  ORDER_RECEIVED,
  INVALID_PAYMENT,
  VALID_PAYMENT,
  MANUFACTURE_FAIL,
  MANUFACTURE_COMPLETE,
  LOST_PACKAGE,
  RECEIVED,
  NUMBER_OF_EVENTS
} event;

typedef enum {
  FAIL,
  LOST,
  DONE
} stats_t;

// Order functions
void order_init(order_t *ord);
void order_process(order_t *ord);

// Transition functions
void resetAttempts();
void incrementAttempts();
int getAttempts();
void updateStats(stats_t stats);
void chargeClient();
void startWarranty();
void refund();

// Entry/Exit functions
void getPaymentMethod();
void dispatchFactoryLines();
void shutDownFactoryLines();
void getAddress();

// Helper Function
void show_state(char in);

#endif
