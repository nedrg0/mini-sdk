#include "hal_ll_gpio.h"
#include "stm32f1xx.h"
#include <stddef.h>

/* F1 mode nibble: bits [3:2] = CNF, bits [1:0] = MODE */
#define NIBBLE(cnf, mode)   ((uint32_t)(((cnf) << 2) | (mode)))

static bool port_is_valid(hal_ll_gpio_port_t port){
    return port < HAL_LL_PORT_COUNT;
}

static GPIO_TypeDef *port_regs(hal_ll_gpio_port_t port){
    switch (port) {
    case HAL_LL_PORT_A: return GPIOA;
    case HAL_LL_PORT_B: return GPIOB;
    case HAL_LL_PORT_C: return GPIOC;
    case HAL_LL_PORT_D: return GPIOD;
    default:            return NULL;
    }
}

static void port_clock_enable(hal_ll_gpio_port_t port){
    switch (port) {
    case HAL_LL_PORT_A: RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; break;
    case HAL_LL_PORT_B: RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; break;
    case HAL_LL_PORT_C: RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; break;
    case HAL_LL_PORT_D: RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; break;
    default: break;
    }
}

static uint32_t mode_to_nibble(hal_ll_gpio_mode_t mode, hal_ll_gpio_speed_t speed) {
	uint32_t out_mode;

	switch( speed ) {
		case HAL_LL_GPIO_SPEED_2MHZ: 	out_mode = 0x2; break;
		case HAL_LL_GPIO_SPEED_10MHZ: 	out_mode = 0x1; break;
		case HAL_LL_GPIO_SPEED_50MHZ: 	out_mode = 0x3; break;
		default: 			out_mode = 0x2; break;
	}

	switch( mode ) {
		case HAL_LL_GPIO_INPUT_ANALOG: 		return NIBBLE(0x0, 0x0);
		case HAL_LL_GPIO_INPUT_FLOATING: 	return NIBBLE(0x1, 0x0);
		case HAL_LL_GPIO_INPUT_PULLUP: 		return NIBBLE(0x2, 0x0);
		case HAL_LL_GPIO_INPUT_PULLDOWN:	return NIBBLE(0x2, 0x0);
		case HAL_LL_GPIO_OUTPUT_PUSH_PULL:	return NIBBLE(0x0, out_mode);
		case HAL_LL_GPIO_OUTPUT_OPEN_DRAIN:	return NIBBLE(0x0, out_mode);
		default:		 		return NIBBLE(0x1, 0x0);
	}
}

static void write_pin_nibble(GPIO_TypeDef* gpio, uint8_t pin, uint32_t nibble) {
	uint32_t shift;

	if (pin < 8) {
		shift = pin * 4u;
		gpio->CRL = (gpio->CRL & ~(0xFu << shift)) | (nibble << shift);
	}
	else {
		shift = (pin - 8u) * 4u;
		gpio->CRH = (gpio->CRH & ~(0xFu << shift)) | (nibble << shift);
	}
}


/*
 * Configure one or more pins of a port.
 * speed is ignored for input modes
 * Errors: HAL_LL_ERR_PORT, HAL_LL_ERR_PIN
 */
hal_ll_err_t hal_ll_gpio_init_pin(hal_ll_gpio_port_t port,
				  uint16_t pin_mask, 
				  hal_ll_gpio_mode_t mode,
				  hal_ll_gpio_speed_t speed) {

	if( !port_is_valid(port) ) 	return HAL_LL_ERR_PORT; 
	if( pin_mask == 0 ) 		return HAL_LL_ERR_PIN;

	GPIO_TypeDef* gpio = port_regs(port);
	port_clock_enable(port);

	uint32_t nibble = mode_to_nibble(mode, speed);

	for(uint8_t pin = 0; pin < 16; pin++) {
		if(pin_mask & (1u << pin)) {
			write_pin_nibble(gpio, pin, nibble);

			if( mode == HAL_LL_GPIO_INPUT_PULLUP ) {
					gpio->BSRR = (1u << pin);
			} else if ( mode == HAL_LL_GPIO_INPUT_PULLDOWN) {
					gpio->BSRR = (1u << (pin + 16));
			}
			
	
		}
	}

	return HAL_LL_ERR_OK;
}

/* Drive selected pins high */
hal_ll_err_t hal_ll_gpio_set_pin(hal_ll_gpio_port_t port,
				   uint16_t pin_mask){

	if( !port_is_valid(port) ) 	return HAL_LL_ERR_PORT; 
	if( pin_mask == 0 ) 		return HAL_LL_ERR_PIN;

	port_regs(port)->BSRR = pin_mask;
	return HAL_LL_ERR_OK;
}

/* Drive selected pins low */
hal_ll_err_t hal_ll_gpio_clear_pin(hal_ll_gpio_port_t port,
				   uint16_t pin_mask){
	
	if( !port_is_valid(port) ) 	return HAL_LL_ERR_PORT; 
	if( pin_mask == 0 ) 		return HAL_LL_ERR_PIN;

	port_regs(port)->BSRR = ((uint32_t)pin_mask << 16);
	return HAL_LL_ERR_OK;
}

/* Toggle selected pins */
hal_ll_err_t hal_ll_gpio_toggle_pin(hal_ll_gpio_port_t port,
				   uint16_t pin_mask){

	if( !port_is_valid(port) ) 	return HAL_LL_ERR_PORT; 
	if( pin_mask == 0 ) 		return HAL_LL_ERR_PIN;

	GPIO_TypeDef* gpio = port_regs(port);
	uint32_t current = gpio->ODR;

	gpio->BSRR = ((~current & pin_mask) | ((current & pin_mask) << 16));
	return HAL_LL_ERR_OK;

}

/* Read level of selected pins. out is true if any pins are high.
 * Errors: HAL_LL_ERR_PORT, HAL_LL_ERR_PIN, HAL_LL_ERR_NULL_PTR
 */
hal_ll_err_t hal_ll_gpio_read_pin(hal_ll_gpio_port_t port,
				  uint16_t pin_mask,
				  bool *out){
	if( !port_is_valid(port) ) 	return HAL_LL_ERR_PORT; 
	if( pin_mask == 0 ) 		return HAL_LL_ERR_PIN;
	if( out == NULL) 		return HAL_LL_ERR_NULL_PTR;

	*out = (port_regs(port)->IDR & pin_mask) != 0;
	return HAL_LL_ERR_OK;
}
