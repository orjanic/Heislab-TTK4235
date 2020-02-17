#include "order.h"

void order_init_list() {
    for (int ot=0; ot<HARDWARE_NUMBER_OF_ORDER_TYPES;ot++){
        for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS; f++){
            if (hardware_legal_floor(f,(HardwareOrder)ot)) {
                order_list[ot][f].order_active = 0;
                order_list[ot][f].order_floor = f;
                order_list[ot][f].order_type = (HardwareOrder)ot;
            }
        }
    }
}

int order_update_list(){
    int new_order = 0;
    for (int ot=0; ot<HARDWARE_NUMBER_OF_ORDER_TYPES;ot++){
        for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS; f++){
            if (hardware_read_order(f, (HardwareOrder)ot)) {
                (order_list[ot][f]).order_active=1;
                hardware_command_order_light(f,(HardwareOrder)ot,1);
                new_order = 1;
            }
        }
    }
    return new_order;
}