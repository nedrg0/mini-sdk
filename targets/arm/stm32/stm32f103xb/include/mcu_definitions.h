#ifndef MCU_DEFINITIONS_H
#define MCU_DEFINITIONS_H

typedef enum {
	HAL_LL_PORT_A = 0,
	HAL_LL_PORT_B,
	HAL_LL_PORT_C,
	HAL_LL_PORT_D,
	HAL_LL_PORT_COUNT,
} hal_ll_gpio_port_t;

/* One bit per pin in a port */
#define HAL_LL_PIN_0     ((uint16_t)(1u << 0))
#define HAL_LL_PIN_1     ((uint16_t)(1u << 1))
#define HAL_LL_PIN_2     ((uint16_t)(1u << 2))
#define HAL_LL_PIN_3     ((uint16_t)(1u << 3))
#define HAL_LL_PIN_4     ((uint16_t)(1u << 4))
#define HAL_LL_PIN_5     ((uint16_t)(1u << 5))
#define HAL_LL_PIN_6     ((uint16_t)(1u << 6))
#define HAL_LL_PIN_7     ((uint16_t)(1u << 7))
#define HAL_LL_PIN_8     ((uint16_t)(1u << 8))
#define HAL_LL_PIN_9     ((uint16_t)(1u << 9))
#define HAL_LL_PIN_10    ((uint16_t)(1u << 10))
#define HAL_LL_PIN_11    ((uint16_t)(1u << 11))
#define HAL_LL_PIN_12    ((uint16_t)(1u << 12))
#define HAL_LL_PIN_13    ((uint16_t)(1u << 13))
#define HAL_LL_PIN_14    ((uint16_t)(1u << 14))
#define HAL_LL_PIN_15    ((uint16_t)(1u << 15))

#define HAL_LL_PIN_ALL   ((uint16_t)0xFFFFu)

#endif /* MCU_DEFINITIONS_H */
