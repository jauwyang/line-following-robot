#include "tb6612fng/tb6612fng.h"

#define PWM_CCR_MIN (uint16_t) 0		// duty cycle = 0
#define PWM_CCR_MAX (uint16_t) 1000		// duty cycle = 100

extern TIM_HandleTypeDef htim1;

static void tb6612fng_drive(const uint32_t pwm_channel, uint16_t pwm_val) {
	// Develop a linear model according to the PWM value characterization

	//uint16_t pulse_width = CCR_MAX - (RPM_MAX - pwm_val)* ((CCR_MAX - PW_MIN) / (RPM_MAX - RPM_MIN));
	switch (pwm_channel) {
	case TIM_CHANNEL_1:
		htim1.Instance->CCR1 = pwm_val;
		break;
	case TIM_CHANNEL_2:
		htim1.Instance->CCR2 = pwm_val;
		break;
	default:
		break;
	}
}

//>>>> SINGLE MOTOR DRIVE <<<<//

// Assume CW is fwd
void tb6612fng_move_fwd_single(motor_t *motor, uint16_t pwm_val) {
	// AIN1 = H, AIN2 = L, STBY = H
	HAL_GPIO_WritePin(motor->ports[0], motor->pins[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(motor->ports[1], motor->pins[1], GPIO_PIN_RESET);

	tb6612fng_drive(motor->pwm_channel, pwm_val);
}

void tb6612fng_move_rev_single(motor_t *motor, uint16_t pwm_val) {
	// AIN1 = L, AIN2 = H, STBY = H
	HAL_GPIO_WritePin(motor->ports[0], motor->pins[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->ports[1], motor->pins[1], GPIO_PIN_SET);

	tb6612fng_drive(motor->pwm_channel, pwm_val);
}

void tb6612fng_stop_single(motor_t *motor) {
	// AIN1 = L, AIN2 = L, STBY = H, PWM = (Max Duty Cycle)
	HAL_GPIO_WritePin(motor->ports[0], motor->pins[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->ports[1], motor->pins[1], GPIO_PIN_RESET);

	tb6612fng_drive(motor->pwm_channel, PWM_CCR_MAX);
}

//>>>> TWO MOTOR DRIVE <<<<//
void tb6612fng_move_fwd(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right) {
	tb6612fng_move_fwd_single(motor_left, pwm_val_left);
	tb6612fng_move_fwd_single(motor_right, pwm_val_right);
}

void tb6612fng_move_rev(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right) {
	tb6612fng_move_rev_single(motor_left, pwm_val_left);
	tb6612fng_move_rev_single(motor_right, pwm_val_right);
}

void tb6612fng_stop(motor_t *motor_left, motor_t *motor_right) {
	tb6612fng_stop_single(motor_left);
	tb6612fng_stop_single(motor_right);
}

void tb6612fng_rotate(motor_t *motor_left, motor_t *motor_right, rotation_t rotation) {

}
