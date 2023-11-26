#include "mg995/mg995.h"
#include "stm32f4xx_hal.h"

/**
 * Constants
 * ANGLE_yyy: Servo is half-turn (spins from 0 to 180 degrees)
 * MS_yyy: The pulse width (ms) that produces min and max rotation
 */
#define ANGLE_MIN	(uint8_t) 0
#define ANGLE_MAX	(uint8_t) 180
#define MS_MIN		(double) 0.5
#define MS_MAX		(double) 2.3

/**
 * User-defined constants
 *
 * Based on how the servo motor is mounted (right gear, wires outside):
 * Angle --> 180 <==> Close
 * Angle -->   0 <==> Open
 */
#define ROBOT_ANGLE_CLOSE	(uint8_t) 70
#define ROBOT_ANGLE_OPEN	(uint8_t) 0
#define ROBOT_DELAY_MS		(uint32_t) 10

extern TIM_HandleTypeDef htim2;

void mg995_set_angle(uint8_t angle) {
	// Constrain input angle
	if (angle > ANGLE_MAX) {
		angle = ANGLE_MAX;
	}

	// Linear interpolation to obtain desired ms value
	double ms_mapped = MS_MAX - ((MS_MAX - MS_MIN) * (ANGLE_MAX - angle)) / 180;
	htim2.Instance->CCR1 = (uint16_t)(ms_mapped * htim2.Instance->ARR) / 20;
}

void mg995_move_range(uint8_t angle_from, uint8_t angle_to, const uint32_t delay) {
	if (angle_from < angle_to) {
		uint8_t angle = angle_from;
		while (angle < angle_to) {
			mg995_set_angle(angle);
			angle++;
			HAL_Delay(delay);
		}
	} else {
		uint8_t angle = angle_to;
		while (angle > angle_from) {
			mg995_set_angle(angle);
			angle--;
			HAL_Delay(delay);
		}
	}
}

/**
 * Convenience Functions for use with user-defined constants
 */

/**
 * Move to open or closed position
 */
void mg995_open_claw(void) {
	mg995_set_angle(ROBOT_ANGLE_OPEN);
}

void mg995_close_claw(void) {
	mg995_set_angle(ROBOT_ANGLE_CLOSE);
}


/**
 * Move from closed position to open position
 */
void mg995_open_claw_delay(void) {
	mg995_move_range(ROBOT_ANGLE_CLOSE, ROBOT_ANGLE_OPEN, ROBOT_DELAY_MS);
}

void mg995_close_claw_delay(void) {
	mg995_move_range(ROBOT_ANGLE_OPEN, ROBOT_ANGLE_CLOSE, ROBOT_DELAY_MS);
}
