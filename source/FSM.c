#include "FSM.h"

static Order m_order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS];
static Order* m_current_order;
static int m_current_floor;
static int m_current_floor_pos;
static State m_current_state;


void FSM_run() {
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
                FSM_dir_up();
                break;
            
            case STATE_DIR_DOWN:
                FSM_dir_down();
                break;
            
            case STATE_STOP_AT_FLOOR:
                FSM_stop_at_floor();
                break;
            
            case STATE_STOP_NOT_AT_FLOOR:
                FSM_stop_not_at_floor();
                break;
            
        }
        // if (hardware_read_stop_signal() && hardware_read_obstruction_signal() && hardware_read_order(0,HARDWARE_ORDER_UP)){
        //     hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        //     break;
        // }
    }
}

void FSM_init(){
    hardware_lights_off();
    order_init_list(m_order_list);
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    m_current_order = &m_order_list[0][0];
	while(1) {
        if (hardware_check_at_floor(&m_current_floor)) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            m_current_floor_pos = 0;
            break;
        } 
    }
    m_current_state=STATE_IDLE;
}

void FSM_idle(){
    while(m_current_state == STATE_IDLE){
        FSM_check_stop();
        if (order_update_list(m_order_list)) {
            for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++){
                for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
                    if (m_order_list[ot][f].order_active) {
                        m_current_order = &m_order_list[ot][f];
                        FSM_choose_next_state();
                        return;
                    }
                }
            }
        }
    }
}

void FSM_open_door(){
    m_current_floor_pos = 0;
    hardware_command_door_open(1);
    order_remove(m_current_floor, m_order_list);
    FSM_timer();
    hardware_command_door_open(0);
    order_choose_next_order(&m_current_order, m_current_floor, m_order_list);
    FSM_choose_next_state();
}

void FSM_dir_up() {
    if (m_current_order->order_active) {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        while (m_current_state == STATE_DIR_UP){
            FSM_check_stop();
            order_update_list(m_order_list);
            if(hardware_check_at_floor(&m_current_floor) && (m_current_order->order_floor == m_current_floor || m_order_list[0][m_current_floor].order_active || m_order_list[1][m_current_floor].order_active)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                m_current_state = STATE_OPEN_DOOR;
            }
        }
    }
}

void FSM_dir_down() {
    if (m_current_order->order_active){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        while (m_current_state == STATE_DIR_DOWN){
            FSM_check_stop();
            order_update_list(m_order_list);
            if(hardware_check_at_floor(&m_current_floor) && (m_current_order->order_floor == m_current_floor || m_order_list[1][m_current_floor].order_active || m_order_list[2][m_current_floor].order_active)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                m_current_state = STATE_OPEN_DOOR;
            }
        }
    }
}

void FSM_stop_at_floor() {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_stop_light(1);
    hardware_command_door_open(1);
    order_remove_all(m_order_list);
    while(hardware_read_stop_signal());
    hardware_command_stop_light(0);
    m_current_state = STATE_OPEN_DOOR;
}

void FSM_stop_not_at_floor() {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_stop_light(1);
    order_remove_all(m_order_list);
    while(hardware_read_stop_signal());
    hardware_command_stop_light(0);
    m_current_state = STATE_IDLE;
}

void FSM_choose_next_state() {
    if (!m_current_order->order_active) {
        m_current_state = STATE_IDLE;
    } else if ((m_current_order->order_floor == m_current_floor) && (m_current_floor_pos == 0)) {
        m_current_state = STATE_OPEN_DOOR;
    }else if((m_current_order->order_floor < m_current_floor) || ((m_current_order->order_floor == m_current_floor) && (m_current_floor_pos == 1))){
        m_current_state = STATE_DIR_DOWN;
        if (hardware_check_at_floor(&m_current_floor)) {
            m_current_floor_pos = -1;
        }
    }else {
        m_current_state = STATE_DIR_UP;
        if (hardware_check_at_floor(&m_current_floor)) {
            m_current_floor_pos = 1;
        }
    }
}

void FSM_check_stop() {
    if(hardware_read_stop_signal()){
        if (hardware_check_at_floor(&m_current_floor)){
            m_current_state = STATE_STOP_AT_FLOOR;
        }
        else{
            m_current_state = STATE_STOP_NOT_AT_FLOOR;
        }
    }
}

void FSM_timer() {
    clock_t start = clock();
    while ((m_current_state == STATE_OPEN_DOOR) && (float)((clock()-start)/CLOCKS_PER_SEC) < 3){
        FSM_check_stop();
        order_update_list(m_order_list);
        order_remove(m_current_floor, m_order_list);
        if (hardware_read_obstruction_signal() || hardware_read_order(m_current_floor, HARDWARE_ORDER_UP) || hardware_read_order(m_current_floor, HARDWARE_ORDER_DOWN) || hardware_read_order(m_current_floor, HARDWARE_ORDER_INSIDE)) {
            start = clock();
        }
    }
}