#ifndef FSM_H
#define FSM_H

#include "hardware.h"
#include "order.h"

typedef enum{
    STATE_INIT,
    STATE_IDLE,
    STATE_OPEN_DOOR,
    STATE_DIR_UP,
    STATE_DIR_DOWN,
    STATE_STOP_AT_FLOOR,
    STATE_STOP_NAT_FLOOR
} State;

State m_current_state;



void FSM_init();

void FSM_StateMachine();

void FSM_idle();

void FSM_order_execution(Order* order);



#endif