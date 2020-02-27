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
 * @brief Initializes @p order_list based on the number of floors and order types.
 * 
 * @param order_list Initialized list.
 */
void order_init_list(Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Updating @p order_list based on pressed order buttons.
 * 
 * @param order_list Updated list.
 */
void order_update_list(Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Removes all orders on a given @p floor in @p order_list .
 * 
 * @param floor Inquired floor.
 * @param order_list Order list in witch the orders will be removed.
 */
void order_remove(int floor, Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Removes all orders in @p order_list .
 * 
 * @param order_list Order list in witch all the orders will be removed.
 */
void order_remove_all(Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

/**
 * @brief Sets @p p_current_order to an order in @p order_list based on @p current_floor .
 * 
 * @param p_current_order Pointer to current order.
 * @param current_floor Current floor the elevator is on.
 * @param order_list Order list the order is picked from.
 */
void order_choose_next_order(Order** p_current_order, int current_floor, Order order_list[HARDWARE_NUMBER_OF_ORDER_TYPES][HARDWARE_NUMBER_OF_FLOORS]);

#endif