#ifndef HAL_LL_ERR_H
#define HAL_LL_ERR_H

typedef enum {
	HAL_LL_ERR_OK = 0,
	HAL_LL_ERR_PORT,
	HAL_LL_ERR_PIN,
	HAL_LL_ERR_NULL_PTR,
	HAL_LL_ERR_TIMEOUT,
	HAL_LL_ERR_NOT_SUPPORTED,
} hal_ll_err_t;


#endif /* HAL_LL_ERR_H */
