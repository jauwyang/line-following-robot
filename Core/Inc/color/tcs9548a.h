#ifndef LINE_FOLLOWING_ROBOT_COLOR_TCS9548_H
#define LINE_FOLLOWING_ROBOT_COLOR_TCS9548_H

#include <stdint.h>
#include <stm32f4xx_hal.h>

/**
 * I2C Multiplexer Addresses
 */
#define TCA9548A_I2C_ADDR	 (0x70 << 1)	// 0x77 since A0 - A2 connected to Vcc

/**
 * User-facing API
 */
HAL_StatusTypeDef tcs9548a_select_channel(uint8_t channel);

#endif // LINE_FOLLOWING_ROBOT_COLOR_TCS9548_H
