#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "FSM.h"


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    FSM_init();

    while(1){
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

    printf("=== Example Program ===\n");/*
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
