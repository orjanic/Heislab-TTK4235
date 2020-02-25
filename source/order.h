/**
 * @file
 * @brief Module for handeling orders.
*/

#ifndef ORDER_H
#define ORDER_H

#include "hardware.h"

/**
 * @brief Struct for describing an order.
 */
typedef struct {
    HardwareOrder order_type;
    int order_floor;
    int order_active;
} Order;

/**
 * @brief Initializes an order list based on the number of floors and order types.
 * 
 * @param p_order_list Initialized list.
 */
void order_init_list(Order p_order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Updating an order list based on pressed order buttons.
 * 
 * @param p_order_list Updated list.
 * 
 * @return 1 if there are new orders, 0 otherwise.
 */
int order_update_list(Order p_order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Removes all orders on a given @c floor in an order list.
 * 
 * @param floor Inquired floor.
 * @param p_order_list Order list in witch the orders will be removed.
 */
void order_remove(int floor, Order p_order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Removes all orders in an order list.
 * 
 * @param p_order_list Order list in witch all the orders will be removed.
 */
void order_remove_all(Order p_order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Sets a pointer to an order in an order list based on current position.
 * 
 * @param p_current_order Pointer to current order.
 * @param current_floor Current @p floor the elevator is on.
 * @param p_order_list Order list the order is picked from.
 */
void order_choose_next_order(Order** p_current_order, int current_floor, Order p_order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);



#endif