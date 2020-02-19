#include "timer.h"

void timer_door(){
    clock_t start=clock();
    while (m_current_state==STATE_OPEN_DOOR && (float)((clock()-start)/CLOCKS_PER_SEC) < 3){
        FSM_check_stop();
        order_update_list();
        order_remove(g_current_floor);
        if (hardware_read_obstruction_signal()) {
            start = clock();
        }
    }
}