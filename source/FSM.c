#include "FSM.h"

void FSM_init(){
    hardware_lights_off();
    order_init_list();
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
	while(1){
        if (hardware_check_at_floor()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        } 
    }
    m_current_state=STATE_IDLE;
}

void FSM_StateMachine() {
    while(1) {
        switch(m_current_state) {
            case STATE_INIT:
                FSM_init();
                break;
            
            case STATE_IDLE:

                break;
            
            case STATE_OPEN_DOOR:
                break;
            
            case STATE_DIR_UP:

                break;
            
            case STATE_DIR_DOWN:
                break;
            
            case STATE_STOP_AT_FLOOR:
                break;
            
            case STATE_STOP_NAT_FLOOR:
                break;
            
        }
    }
}

void FSM_idle(){
    while(m_current_state==STATE_IDLE) {
        if (order_update_list()) {
            for (int ot=0; ot<HARDWARE_NUMBER_OF_ORDER_TYPES;ot++){
                for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS; f++){
                    if (order_list[ot][f].order_active) {

                    }
                }
            }
        }
    }
}

void FSM_order_execution(Order* order) {
    if (order->order_active){

    }
}