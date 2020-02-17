#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "FSM.h"
#include "order.h"
#include "timer.h"


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    //Skal vi sette denne inni?
    //FSM_init();
    //FSM_idle();
    //FSM_order_dir_up();
    //timer_door();
    //FSM_order_dir_down();
    FSM_state_machine();

/*
    while(1){
        order_update_list();
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
        if(hardware_read_order(2,HARDWARE_ORDER_UP)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            while (1) {
                if (hardware_read_floor_sensor(2)){
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    break;
                }
            }
        }
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardware_command_movement(HARDWARE_MOVEMENT_UP);

    while(1){
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
    }*/
}
