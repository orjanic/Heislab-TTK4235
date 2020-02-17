#ifndef ORDER_H
#define ORDER_H

#include "hardware.h"

typedef struct {
    HardwareOrder order_type;
    int order_floor;
    int order_active;
} Order;

Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS];

void order_init_list();

int order_update_list();



#endif