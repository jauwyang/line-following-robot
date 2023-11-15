#include "apds9960/apds9960_config.h"
#include "apds9960/apds9960.h"

#include <stdio.h>
#include <stm32f4xx_hal.h>

extern I2C_HandleTypeDef hi2c1;

/**
 * Low-Level I2C Functions
 */

static HAL_StatusTypeDef i2c_reg_read(const uint8_t i2c_addr, const uint8_t reg, uint8_t *out_value) {
    return HAL_I2C_Mem_Read(&hi2c1, i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, out_value, 1, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef i2c_reg_write(const uint8_t i2c_addr, const uint8_t reg, uint8_t value) {
    return HAL_I2C_Mem_Write(&hi2c1, i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY);
}


/**
 * TU-local struct definitions and functions
 */

typedef struct _hlbyte_pair_t {

	uint8_t low_byte;
	uint8_t high_byte;

} hlbyte_pair_t;


/**
 * User-facing API
 */

void apds9960_color_init(const uint8_t i2c_addr) {
	// Power ON and enable ALS
	i2c_reg_write(i2c_addr, APDS9960_COLOR_REG_ENABLE, APDS9960_COLOR_BITMASK_ENABLE_PON | APDS9960_COLOR_BITMASK_ENABLE_AEN);

	// Set ADC integration time (ATIME) and ALS Gain (AGAIN)
	i2c_reg_write(i2c_addr, APDS9960_COLOR_REG_ATIME, APDS9960_COLOR_BITMASK_ATIME_255);
	i2c_reg_write(i2c_addr, APDS9960_COLOR_REG_CONTROL, APDS9960_COLOR_BITMASK_AGAIN_16X);
}

uint16_t apds9960_read_rgb_single(const uint8_t i2c_addr, const color_e color) {
	uint8_t color_reg_low = 0;
	uint8_t color_reg_high = 0;

	switch (color) {
	case COLOR_RED:
		color_reg_low = APDS9960_COLOR_REG_RDATAL;
		color_reg_high = APDS9960_COLOR_REG_RDATAH;
		break;
	case COLOR_GREEN:
		color_reg_low = APDS9960_COLOR_REG_GDATAL;
		color_reg_high = APDS9960_COLOR_REG_GDATAH;
		break;
	case COLOR_BLUE:
		color_reg_low = APDS9960_COLOR_REG_BDATAL;
		color_reg_high = APDS9960_COLOR_REG_BDATAH;
		break;
	default:
		printf("%s\r\n", "Color argument passed in not supported.");
		break;
	}

	hlbyte_pair_t byte_pair = {0};

	/**
	 * Read sequence: byte pairs, low followed by high
	 */
	i2c_reg_read(i2c_addr, color_reg_low, &(byte_pair.low_byte));
	i2c_reg_read(i2c_addr, color_reg_high, &(byte_pair.high_byte));

	return (byte_pair.high_byte << 8) | byte_pair.low_byte;
}

rgb_cap_t apds9960_read_rgb(const uint8_t i2c_addr) {
	rgb_cap_t rgb = {
		.red = apds9960_read_rgb_single(i2c_addr, COLOR_RED),
		.green = apds9960_read_rgb_single(i2c_addr, COLOR_GREEN),
		.blue = apds9960_read_rgb_single(i2c_addr, COLOR_BLUE)
	};

	return rgb;
}
