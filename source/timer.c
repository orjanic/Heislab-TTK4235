#include "timer.h"

void timer_door() {
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