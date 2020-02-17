#include "timer.h"

void timer_door(){
    clock_t start=clock();
    while ((float)((clock()-start)/CLOCKS_PER_SEC) < 3){
        order_update_list();
        order_remove(g_current_floor);
        if (hardware_read_obstruction_signal()) {
            start = clock();
        }
    }
}