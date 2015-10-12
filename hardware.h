#ifndef hardware_h
#define hardware_h

#define LIMIT;

typedef enum {
  OrderRcvd,
  InvalidPymnt,
  ValidPymnt,
  ManufFailed,
  ManufCompleted,
  LostPackage,
  Received,
} event_t;

typedef enum {
  FAIL,
  LOST,
  DONE
} stats_t;

// Transition functions
void resetAttempts();
void incrementAttempts();
void UpdateStats(stats_t stats);
void ChargeClient();
void StartWarranty();
void Refund();

// Entry/Exit functions
void getPymntMethod();
void dispatchFactoryLines();
void shutDownFactoryLines();
void getAddress();

#endif
