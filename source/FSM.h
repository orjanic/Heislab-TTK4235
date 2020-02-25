/**
 * @file
 * @brief Module to control movement of elevator
*/

#ifndef FSM_H
#define FSM_H

#include "hardware.h"
#include "order.h"
#include <time.h>



/**
 * @brief States used to control the elevators behaviour.
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

/**
 * @brief Sends the program between different states based on @c m_current_state
 */
void FSM_run();

/**
 * @brief Initializes the elevator by moving down until it reaches a floor.
 */
void FSM_init();

/**
 * @brief Searches @c m_order_list for new orders, and sets @c m_current_order to the first new order
 */
void FSM_idle();

/**
 * @brief Opens door, and closes it after a time given by @c FSM_timer .
 */
void FSM_open_door();

/**
 * @brief Makes the elevator go up until it reaches floor given by @c m_current_order, or closest
 *  floor with an active @c HARDWARE_ORDER_UP or @c HARDWARE_ORDER_INSIDE order.
 */
void FSM_dir_up();

/**
 * @brief Makes the elevator go down until it reaches floor given by @c m_current_order, or closest
 *  floor with an active @c HARDWARE_ORDER_DOWN or @c HARDWARE_ORDER_INSIDE order.
 */
void FSM_dir_down();

/**
 * @brief Stops elevator, opens door, makes stop light glow and remove all orders while stop button is pressed.
 */
void FSM_stop_at_floor();

/**
 * @brief Stops elevator, makes stop light glow and remove all orders while stop button is pressed.
 */
void FSM_stop_not_at_floor();

/**
 * @brief Chooses next state based on @c m_current_order .
 */
void FSM_choose_next_state();

/**
 * @brief Polls stop button, and sets state to @c STATE_STOP_AT_FLOOR or @c STATE_STOP_NOT_AT_FLOOR .
 */
void FSM_check_stop();

/**
 * @brief Counts down three seconds, resets if obstruction is active or an orderbutton from @c m_current_floor is pressed.
 */
void FSM_timer();

#endif