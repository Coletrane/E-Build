#ifndef hardware_h
#define hardware_h

#define LIMIT 3 

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
