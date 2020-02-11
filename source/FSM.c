#include "FSM.h"

void FSM_init(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
	while(1){
        if (hardware_read_floor_sensor(0) || hardware_read_floor_sensor(1) || hardware_read_floor_sensor(2) || hardware_read_floor_sensor(3)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        } 
    }
}