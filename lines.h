#ifndef lines_h
#define lines_h

#include "order.h"
#include "manufacturing.h"
#include <semaphore.h>

typedef struct {
	order_t ord;
} line_t;

line_t lines[5];
sem_t line_sema[5];

void line_init(order_t *ord);

#endif
