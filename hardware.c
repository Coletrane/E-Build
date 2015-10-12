#ifndef hardware_c
#define hardware_c

static int attempts = 0;
static stats_t STATS;

// Transition functions
void resetAttempts()
{
  attempts = 0;
}
void incrementAttempts()
{
  attempts++;
}
void UpdateStats(stats_t stats);
{
  STATS = stats;
}
void ChargeClient()
{

}
void StartWarranty()
{

}
void Refund()
{

}

// Entry/Exit functions
void getPymntMethod()
{

}
void dispatchFactoryLines()
{

}
void shutDownFactoryLines()
{

}
void getAddress()
{

}

#endif
