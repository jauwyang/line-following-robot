#include "mg995/mg995.h"
#include "stm32f4xx_hal.h"

/**
 * Constants
 * ANGLE_yyy: Servo is half-turn (spins from 0 to 180 degrees)
 * MS_yyy: The pulse width (ms) that produces min and max rotation
 */
#define ANGLE_MIN	 0
#define ANGLE_MAX	 180
#define MS_MIN		(double) 0.5
#define MS_MAX		(double) 2.3

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

}

/**
 * 0 degrees to 180 degrees
 */
void mg995_open_claw(void) {
	mg995_set_angle(ANGLE_MAX);
}

/**
 * 180 degrees to 0 degrees
 */
void mg995_close_claw(void) {
	mg995_set_angle(ANGLE_MIN);
}

void mg995_open_claw_delay(const uint8_t p_angle, const uint32_t delay) {
	uint8_t angle = ANGLE_MIN;
	while (angle < p_angle) {
		mg995_set_angle(angle);
		angle++;
		HAL_Delay(delay);
	}
}

void mg995_close_claw_delay(const uint8_t p_angle, const uint32_t delay) {
	uint8_t angle = ANGLE_MAX;
	while (angle > p_angle) {
		mg995_set_angle(angle);
		angle--;
		HAL_Delay(delay);
	}
}
