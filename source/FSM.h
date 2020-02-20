#ifndef FSM_H
#define FSM_H

#include "hardware.h"
#include "order.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum{
    STATE_INIT,
    STATE_IDLE,
    STATE_OPEN_DOOR,
    STATE_DIR_UP,
    STATE_DIR_DOWN,
    STATE_STOP_AT_FLOOR,
    STATE_STOP_NOT_AT_FLOOR
} State;

State g_current_state;



void FSM_init();

void FSM_state_machine();

void FSM_idle();

void FSM_order_dir_up();

void FSM_order_dir_down();

void FSM_open_door();

void FSM_choose_next_state();

void FSM_check_stop();

void FSM_stop_at_floor();

void FSM_stop_not_at_floor();

#endif