#ifndef HAL_LL_GPIO_H
#define HAL_LL_GPIO_H

#include <stdbool.h>
#include <stdint.h>
#include "hal_ll_err.h"
#include "mcu_definitions.h"


typedef enum {
	HAL_LL_GPIO_INPUT_ANALOG = 0,
	HAL_LL_GPIO_INPUT_FLOATING,
	HAL_LL_GPIO_INPUT_PULLUP,
	HAL_LL_GPIO_INPUT_PULLDOWN,
	HAL_LL_GPIO_OUTPUT_PUSH_PULL,
	HAL_LL_GPIO_OUTPUT_OPEN_DRAIN,
} hal_ll_gpio_mode_t;

typedef enum {
	HAL_LL_GPIO_SPEED_2MHZ = 0,
	HAL_LL_GPIO_SPEED_10MHZ,
	HAL_LL_GPIO_SPEED_50MHZ,
} hal_ll_gpio_speed_t;


/*
 * Configure one or more pins of a port.
 * speed is ignored for input modes
 * Errors: HAL_LL_ERR_PORT, HAL_LL_ERR_PIN
 */
hal_ll_err_t hal_ll_gpio_init_pin(hal_ll_gpio_port_t port,
				  uint16_t pin_mask, 
				  hal_ll_gpio_mode_t mode,
				  hal_ll_gpio_speed_t speed);

/* Drive selected pins high */
hal_ll_err_t hal_ll_gpio_set_pin(hal_ll_gpio_port_t port,
				   uint16_t pin_mask);

/* Drive selected pins low */
hal_ll_err_t hal_ll_gpio_clear_pin(hal_ll_gpio_port_t port,
				   uint16_t pin_mask);

/* Toggle selected pins */
hal_ll_err_t hal_ll_gpio_toggle_pin(hal_ll_gpio_port_t port,
				   uint16_t pin_mask);

/* Read level of selected pins. out is true if any pins are high.
 * Errors: HAL_LL_ERR_PORT, HAL_LL_ERR_PIN, HAL_LL_ERR_NULL_PTR
 */
hal_ll_err_t hal_ll_gpio_read_pin(hal_ll_gpio_port_t port,
				  uint16_t pin_mask,
				  bool *out);

#endif /* HAL_LL_GPIO_H */
