#ifndef ORDER_H
#define ORDER_H

#include "hardware.h"

typedef struct {
    HardwareOrder order_type;
    HardwareFloor order_floor;
    int order_active;
} Order;

static Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS];

void order_update_list();


#endif