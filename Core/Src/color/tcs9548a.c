#include "color/tcs9548a.h"

extern I2C_HandleTypeDef hi2c1;

HAL_StatusTypeDef tcs9548a_select_channel(uint8_t channel) {
	uint8_t shifted = (1 << channel);
	return HAL_I2C_Master_Transmit(&hi2c1, TCA9548A_I2C_ADDR, &shifted, 1, HAL_MAX_DELAY);
}
