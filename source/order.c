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

void order_remove(int floor) {
    for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++) {
        order_list[ot][floor].order_active = 0;
        hardware_command_order_light(floor,(HardwareOrder)ot,0);
    }
}

int order_check_for_order(){
    for (int ot=0; ot<HARDWARE_NUMBER_OF_ORDER_TYPES;ot++){
        for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS; f++){
            if (order_list[ot][f].order_active) {
                return 1;
            }
        }
    }
    return 0;
}

void order_queue(){
    if (g_current_order->order_active){
        if (g_current_order->order_floor < g_current_floor) {
            m_current_state = STATE_DIR_DOWN;
        } else {
            m_current_state = STATE_DIR_UP;
        }
    } else if (!order_check_for_order()) { 
        m_current_state=STATE_IDLE;
    } else {
        for (int ot=0; ot<HARDWARE_NUMBER_OF_ORDER_TYPES;ot++){
            for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS; f++){
                if (order_list[ot][f].order_active) {
                    g_current_order=&order_list[ot][f];
                }
            }
        }
        if (g_current_order->order_floor < g_current_floor) {
            m_current_state = STATE_DIR_DOWN;
        } else {
            m_current_state = STATE_DIR_UP;
        }
    }
}