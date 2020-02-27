#include "order.h"

void order_init_list(Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]) {
    for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++){
        for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){ 
            order_list[ot][f].order_active = 0;
            order_list[ot][f].order_floor = f;
            order_list[ot][f].order_type = (HardwareOrder)ot;
        }
    }
}

void order_update_list(Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]) {
    for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++){
        for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if (hardware_read_order(f, (HardwareOrder)ot)) {
                order_list[ot][f].order_active = 1;
                hardware_command_order_light(f, (HardwareOrder)ot, 1);
            }
        }
    }
}

void order_remove(int floor, Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]) {
    for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++) {
        order_list[ot][floor].order_active = 0;
        hardware_command_order_light(floor, (HardwareOrder)ot, 0);
    }
}

void order_remove_all(Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]) {
    for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        order_remove(f, order_list);
    }
}


void order_choose_next_order(Order** p_current_order, int current_floor, Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]) {
    if (!(*p_current_order)->order_active) {
        if (current_floor < HARDWARE_NUMBER_OF_FLOORS/2) {
            for (int f = HARDWARE_NUMBER_OF_FLOORS - 1; f >= 0; f--) {
                for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++){
                    if (order_list[ot][f].order_active) {
                        (*p_current_order) = &order_list[ot][f];
                        return;
                    }
                }
            }
        }
        else {
            for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++) {
                for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++){
                    if (order_list[ot][f].order_active) {
                        (*p_current_order) = &order_list[ot][f];
                        return;
                    }
                }
            }
        }
    }
}