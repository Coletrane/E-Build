#ifndef order_c
#define order_c

#include "order.h"

int ord_count = 0;

void order_init(order_t *ord)
{
	if (ord_count == 0)
	{
		srandom(time(NULL));
		ord_count++;
	}
	ord->order_size = (random() % 1001) + 1000;
	ord->capacity = (random() % 41) + 10;
	ord->duration = (random() % 5) + 1;
}

void order_process(order_t *ord)
{
	sleep(ord->duration);
	ord_count--;
}


#endif
