#include "FSM.h"

void FSM_init(){
    m_current_floor=HARDWARE_FLOOR_UNDEFINED;
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