/**
 * @file
 * @brief Module to control movement of elevator
*/

#ifndef FSM_H
#define FSM_H

#include "hardware.h"
#include "order.h"
#include "timer.h"
#include <stdio.h>  //sikker?
#include <stdlib.h>


/**
 * @brief States used in 
 */
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
int g_last_direction; //---------------------------------------------------


/**
 * @brief Initializes the elevator by moving down until it reaches a floor.
 */
void FSM_init();

/**
 * @brief Sends the program between different states based on @c g_current_state
 */
void FSM_state_machine();

/**
 * @brief Searches @c order_list for new orders, and sets @c g_current_order to the first new order
 */
void FSM_idle();

/**
 * @brief Makes the elevator go up until it reaches floor given by @c g_current_order, or closest
 *  floor with an active @c HARDWARE_ORDER_UP or @c HARDWARE_ORDER_INSIDE order.
 */
void FSM_order_dir_up();

/**
 * @brief Makes the elevator go down until it reaches floor given by @c g_current_order, or closest
 *  floor with an active @c HARDWARE_ORDER_DOWN or @c HARDWARE_ORDER_INSIDE order.
 */
void FSM_order_dir_down();

/**
 * @brief Opens door, and closes it after a time given by @c timer_door .
 */
void FSM_open_door();

/**
 * @brief Chooses next state based on @c g_current_order .
 */
void FSM_choose_next_state();

/**
 * @brief Polls stop button, and sets state to @c STATE_STOP_AT_FLOOR or @c STATE_STOP_NOT_AT_FLOOR .
 */
void FSM_check_stop();

/**
 * @brief Stops elevator, opens door, makes stop light glow and remove all orders while stop button is pressed.
 */
void FSM_stop_at_floor();

/**
 * @brief Stops elevator, makes stop light glow and remove all orders while stop button is pressed.
 */
void FSM_stop_not_at_floor();

#endif