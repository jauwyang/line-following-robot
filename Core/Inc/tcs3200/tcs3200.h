#ifndef LINE_FOLLOWING_ROBOT_COLOUR_TCS3200_H
#define LINE_FOLLOWING_ROBOT_COLOUR_TCS3200_H

#include <stdint.h>
#include <stm32f4xx_hal.h>

// Defines for port and pin access
#define SELECT_PIN_COUNT (uint8_t) 4
#define S0 (uint8_t) 0
#define S1 (uint8_t) 1
#define S2 (uint8_t) 2
#define S3 (uint8_t) 3

typedef struct _tcs3200_t {

	GPIO_TypeDef* select_ports[SELECT_PIN_COUNT];
	uint16_t select_pins[SELECT_PIN_COUNT];

} tcs3200_t;

typedef enum _filter_colour_e {

	FILTER_RED = 0,
	FILTER_BLUE = 0x01,
	FILTER_CLEAR = 0x02,
	FILTER_GREEN = 0x04

} filter_colour_e;

typedef enum _frequency_scale_e {

	FREQ_PWDWN = 0,
	FREQ_2_PERCENT = 0x01,
	FREQ_20_PERCENT = 0x02,
	FREQ_100_PERCENT = 0x04

} frequency_scale_e;

void tcs3200_select_filter(tcs3200_t *sensor, filter_colour_e filter);
void tcs3200_select_frequency(tcs3200_t *sensor, frequency_scale_e frequency);

#endif // LINE_FOLLOWING_ROBOT_COLOUR_TCS3200_H
