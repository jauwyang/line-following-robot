#ifndef LINE_FOLLOWING_ROBOT_COLOUR_TCS3200_H
#define LINE_FOLLOWING_ROBOT_COLOUR_TCS3200_H

#include "stm32f4xx_hal.h"

// Index Keys
#define S0 (uint8_t) 0
#define S1 (uint8_t) 1
#define S2 (uint8_t) 2
#define S3 (uint8_t) 3

const uint8_t SELECT_PIN_COUNT = 4;

/**
 * Wrapper around a single colour sensor
 */
typedef struct _tcs3200_handle_t {

	GPIO_TypeDef* select_ports[SELECT_PIN_COUNT];
	uint16_t select_pins[SELECT_PIN_COUNT];
	uint32_t ic_channel;

} tcs3200_handle_t;

/**
 * User-facing API
 */




#endif // LINE_FOLLOWING_ROBOT_COLOUR_TCS3200_H
