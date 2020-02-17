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

void FSM_state_machine() {
    m_current_state = STATE_INIT;
    while(1) {
        switch(m_current_state) {
            case STATE_INIT:
                FSM_init();
                break;
            
            case STATE_IDLE:
                FSM_idle();
                break;
            
            case STATE_OPEN_DOOR:
                FSM_open_door();
                break;
            
            case STATE_DIR_UP:
                FSM_order_dir_up();
                break;
            
            case STATE_DIR_DOWN:
                FSM_order_dir_down();
                break;
            
            case STATE_STOP_AT_FLOOR:
                break;
            
            case STATE_STOP_NAT_FLOOR:
                break;
            
        }
        if (hardware_read_stop_signal()){
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
                        if (f==g_current_floor){
                            m_current_state=STATE_OPEN_DOOR;
                        }else if(f<g_current_floor){
                            m_current_state=STATE_DIR_DOWN;
                        }else {
                            m_current_state=STATE_DIR_UP;
                        }
                        g_current_order = &order_list[ot][f];
                        return;
                    }
                }
            }
        }
    }
}

void FSM_order_dir_up() {
    if (g_current_order->order_active){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        while (m_current_state == STATE_DIR_UP){
            order_update_list();
            if(hardware_check_at_floor() && (g_current_order->order_floor==g_current_floor || order_list[0][g_current_floor].order_active || order_list[1][g_current_floor].order_active)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                m_current_state = STATE_OPEN_DOOR;
            }
        }
    }
}

void FSM_order_dir_down() {
    if (g_current_order->order_active){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        while (m_current_state == STATE_DIR_DOWN){
            order_update_list();
            if(hardware_check_at_floor() && (g_current_order->order_floor==g_current_floor || order_list[1][g_current_floor].order_active || order_list[2][g_current_floor].order_active)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                m_current_state = STATE_OPEN_DOOR;
            }
        }
    }
}

void FSM_open_door(){
    hardware_command_door_open(1);
    order_remove(g_current_floor);
    timer_door();
    hardware_command_door_open(0);
    order_queue();
    
}