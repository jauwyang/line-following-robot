#ifndef LINE_FOLLOWING_ROBOT_APDS9960_APDS9960_CONFIG_H
#define LINE_FOLLOWING_ROBOT_APDS9960_APDS9960_CONFIG_H

/**
 * @file apds9960_config.h
 * #brief Configuration file for the APDS9960 colour sensor.
 * 		  Register addresses and bit masks taken from the datasheet at https://cdn.sparkfun.com/datasheets/Sensors/Proximity/apds9960.pdf
 */

/**
 * Device I2C Address
 */

// Note: left shift by 1 since I2C takes MSB of address first, and
// address frame is only 7 bits
#define APDS9960_I2C_ADDR  (0x39 << 1)	// Address is fixed

/**
 * Register Addresses
 */
#define APDS9960_COLOR_REG_ENABLE	 0x80	// Enable register
#define APDS9960_COLOR_REG_ATIME	 0x81	// ALS ADC Integration Time
#define APDS9960_COLOR_REG_CONTROL	 0x8F	// Control
#define APDS9960_COLOR_REG_RDATAL	 0x96	// Red Data, Low Byte
#define APDS9960_COLOR_REG_RDATAH	 0x97	// Red Data, High Byte
#define APDS9960_COLOR_REG_GDATAL	 0x98	// Green Data, Low Byte
#define APDS9960_COLOR_REG_GDATAH	 0x99	// Green Data, High Byte
#define APDS9960_COLOR_REG_BDATAL	 0x9A	// Blue Data, Low Byte
#define APDS9960_COLOR_REG_BDATAH	 0x9B	// Blue Data, High Byte


/**
 * Bit masks
 */
#define APDS9960_COLOR_BITMASK_ENABLE_PON	 0x01	// Power ON
#define APDS9960_COLOR_BITMASK_ENABLE_AEN	 0x02	// ALS Enable

#define APDS9960_COLOR_BITMASK_AGAIN_16X	 0x03	// 16x ALS Gain Control
#define APDS9960_COLOR_BITMASK_ATIME_255	 0xFF	// 1 cycle, 2.78 ms, 1025 max count

#endif // LINE_FOLLOWING_ROBOT_APDS9960_APDS9960_CONFIG_H
