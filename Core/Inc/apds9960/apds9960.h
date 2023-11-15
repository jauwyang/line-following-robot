#ifndef LINE_FOLLOWING_ROBOT_APDS9960_APDS9960_H
#define LINE_FOLLOWING_ROBOT_APDS9960_APDS9960_H

#include <stdint.h>

/**
 * Capture low and high byte of sensor RGB readings
 */
typedef struct _rbg_cap_t {

	uint16_t red;
	uint16_t green;
	uint16_t blue;

} rgb_cap_t;

/**
 * Supported colours
 */
typedef enum _color_e {
	COLOR_RED = 0,
	COLOR_GREEN,
	COLOR_BLUE
} color_e;

/**
 * User-facing API
 */
void apds9960_color_init(uint8_t i2c_addr);
uint16_t apds9960_read_rgb_single(uint8_t i2c_addr, color_e color);
rgb_cap_t apds9960_read_rgb(uint8_t i2c_addr);

#endif // LINE_FOLLOWING_ROBOT_APDS9960_APDS9960_H
