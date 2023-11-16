#ifndef LINE_FOLLOWING_ROBOT_COLOR_TCS9548_H
#define LINE_FOLLOWING_ROBOT_COLOR_TCS9548_H

#include <stdint.h>
#include <stm32f4xx_hal.h>

/**
 * I2C Multiplexer Addresses
 */
#define TCA9548A_I2C_ADDR	(uint8_t) (0x70 << 1)
#define ADDR_CHANNEL_1		(uint8_t) 0x01
#define ADDR_CHANNEL_2		(uint8_t) 0x02
#define ADDR_CHANNEL_3		(uint8_t) 0x03
#define ADDR_CHANNEL_4		(uint8_t) 0x04
#define ADDR_CHANNEL_5		(uint8_t) 0x05
#define ADDR_CHANNEL_6		(uint8_t) 0x06
#define ADDR_CHANNEL_7		(uint8_t) 0x07

/**
 * User-facing API
 */
HAL_StatusTypeDef tcs9548a_select_channel(uint8_t channel);

#endif // LINE_FOLLOWING_ROBOT_COLOR_TCS9548_H
