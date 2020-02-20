#ifndef ORDER_H
#define ORDER_H

#include "hardware.h"
#include "FSM.h"


typedef struct {
    HardwareOrder order_type;
    int order_floor;
    int order_active;
} Order;

Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS];
Order* g_current_order;

void order_init_list();

int order_update_list();

void order_remove(int floor);

void order_remove_all();

int order_check_for_order();

void order_choose_next_order();

void order_queue();

#endif