#include "FSM.h"

void FSM_init(){
    hardware_lights_off();
    order_init_list();
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    g_current_order = &order_list[0][0];
	while(1) {
        if (hardware_check_at_floor()) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            g_current_floor_pos = 0;
            break;
        } 
    }
    g_current_state=STATE_IDLE;
}

void FSM_state_machine() {
    g_current_state = STATE_INIT;
    while(1) {
        switch(g_current_state) {
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
                FSM_stop_not_at_floor();
                break;
            
        }
        if (hardware_read_stop_signal() && hardware_read_obstruction_signal() && hardware_read_order(0,HARDWARE_ORDER_UP)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
    }
}

void FSM_idle(){
    while(g_current_state == STATE_IDLE){
        FSM_check_stop();
        if (order_update_list()) {
            for (int ot = 0; ot < HARDWARE_NUMBER_OF_ORDER_TYPES; ot++){
                for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
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
    if (g_current_order->order_active) {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        while (g_current_state == STATE_DIR_UP){
            FSM_check_stop();
            order_update_list();
            if(hardware_check_at_floor() && (g_current_order->order_floor == g_current_floor || order_list[0][g_current_floor].order_active || order_list[1][g_current_floor].order_active)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                g_current_state = STATE_OPEN_DOOR;
            }
        }
    }
}

void FSM_order_dir_down() {
    if (g_current_order->order_active){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        while (g_current_state == STATE_DIR_DOWN){
            FSM_check_stop();
            order_update_list();
            if(hardware_check_at_floor() && (g_current_order->order_floor == g_current_floor || order_list[1][g_current_floor].order_active || order_list[2][g_current_floor].order_active)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                g_current_state = STATE_OPEN_DOOR;
            }
        }
    }
}

void FSM_open_door(){
    g_current_floor_pos = 0;
    hardware_command_door_open(1);
    order_remove(g_current_floor);
    FSM_timer();
    hardware_command_door_open(0);
    order_choose_next_order();
    FSM_choose_next_state();
}

void FSM_choose_next_state() {
    if (!g_current_order->order_active) {
        g_current_state = STATE_IDLE;
    } else if ((g_current_order->order_floor == g_current_floor) && (g_current_floor_pos == 0)) {
        g_current_state = STATE_OPEN_DOOR;
    }else if((g_current_order->order_floor < g_current_floor) || ((g_current_order->order_floor == g_current_floor) && (g_current_floor_pos == 1))){
        g_current_state = STATE_DIR_DOWN;
        if (hardware_check_at_floor()) {
            g_current_floor_pos = -1;
        }
    }else {
        g_current_state = STATE_DIR_UP;
        if (hardware_check_at_floor()) {
            g_current_floor_pos = 1;
        }
    }
}

void FSM_check_stop() {
    if(hardware_read_stop_signal()){
        if (hardware_check_at_floor()){
            g_current_state = STATE_STOP_AT_FLOOR;
        }
        else{
            g_current_state = STATE_STOP_NOT_AT_FLOOR;
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
    g_current_state=STATE_OPEN_DOOR;
}

void FSM_stop_not_at_floor() {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_stop_light(1);
    order_remove_all();
    while(hardware_read_stop_signal());
    hardware_command_stop_light(0);
    g_current_state = STATE_IDLE;
}

void FSM_timer() {
    clock_t start = clock();
    while ((g_current_state == STATE_OPEN_DOOR) && (float)((clock()-start)/CLOCKS_PER_SEC) < 3){
        FSM_check_stop();
        order_update_list();
        order_remove(g_current_floor);
        if (hardware_read_obstruction_signal() || hardware_read_order(g_current_floor, HARDWARE_ORDER_UP) || hardware_read_order(g_current_floor, HARDWARE_ORDER_DOWN) || hardware_read_order(g_current_floor, HARDWARE_ORDER_INSIDE)) {
            start = clock();
        }
    }
}