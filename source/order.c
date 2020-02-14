#include "order.h"


void order_update_list(){
    for (int ot=0; ot<HARDWARE_NUMBER_OF_ORDER_TYPES;ot++){
        for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS; f++){
            if (hardware_read_order(f, (HardwareOrder)ot)) {
                (order_list[ot][f]).order_active=1;
                hardware_command_order_light(f,(HardwareOrder)ot,1);
            }
        }
    }
}