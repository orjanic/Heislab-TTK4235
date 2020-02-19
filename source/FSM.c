#include "FSM.h"

void FSM_init(){
    hardware_lights_off();
    order_init_list();
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    g_current_order=&order_list[0][0];
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
                FSM_stop_at_floor();
                break;
            
            case STATE_STOP_NOT_AT_FLOOR:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                order_remove_all();
                m_current_state=STATE_IDLE;
                break;
            
        }
        if (hardware_read_stop_signal() && hardware_read_obstruction_signal() && hardware_read_order(0,HARDWARE_ORDER_UP)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
    }
}

void FSM_idle(){
    while(m_current_state==STATE_IDLE){
        FSM_check_stop();
        if (order_update_list()) {
            for (int ot=0; ot<HARDWARE_NUMBER_OF_ORDER_TYPES;ot++){
                for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS; f++){
                    if (order_list[ot][f].order_active) {
                        g_current_order = &order_list[ot][f];
                        FSM_choose_next_state();
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
            FSM_check_stop();
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
            FSM_check_stop();
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

void FSM_choose_next_state(){
    if (g_current_order->order_floor==g_current_floor){
        m_current_state=STATE_OPEN_DOOR;
    }else if(g_current_order->order_floor<g_current_floor){
        m_current_state=STATE_DIR_DOWN;
    }else {
        m_current_state=STATE_DIR_UP;
    }
}

void FSM_check_stop(){
    if(hardware_read_stop_signal()){
        if (hardware_check_at_floor()){
            m_current_state=STATE_STOP_AT_FLOOR;
        }
        else{
            m_current_state=STATE_STOP_NOT_AT_FLOOR;
        }
    }
}

void FSM_stop_at_floor() {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_stop_light(1);
    hardware_command_door_open(1);
    order_remove_all();
    while(hardware_read_stop_signal());
    hardware_command_stop_light(0);
    m_current_state=STATE_OPEN_DOOR;
}