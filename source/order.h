/**
 * @file
 * @brief Module for handeling orders.
*/

#ifndef ORDER_H
#define ORDER_H

#include "hardware.h"
#include "FSM.h"

/**
 * @brief Struct for describing an order.
 */
typedef struct {
    HardwareOrder order_type;
    int order_floor;
    int order_active;
} Order;

Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS];
Order* g_current_order;

/**
 * @brief Initializes @c order_list .
 */
void order_init_list();

/**
 * @brief Updating @c order_list .
 * 
 * @return 1 if there are new orders, 0 otherwise.
 */
int order_update_list();

/**
 * @brief Removes all orders on a given @c floor in @c order_list .
 * 
 * @param floor Inquired floor.
 */
void order_remove(int floor);

/**
 * @brief Removes all orders in @c order_list .
 */
void order_remove_all();

/**
 * @brief Checks @c order_list for active orders.
 * 
 * @return 1 if there are active orders, 0 otherwise.
 */
int order_check_for_order();

/**
 * @brief Sets @c g_current_order to next order based on the elevator's position.
 */
void order_choose_next_order();

/**
 * @brief 
 */
void order_queue();

#endif