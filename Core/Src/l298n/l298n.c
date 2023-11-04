#include "l298n/l298n.h"

#define CCR_MIN_50HZ 	(uint16_t) 80
#define CCR_MIN_100HZ 	(uint16_t) 90
#define CCR_MAX 		(uint16_t) 570

extern TIM_HandleTypeDef htim1;

static void l298n_drive(const uint32_t pwm_channel, uint16_t pwm_val) {
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
void l298n_move_fwd_single(motor_t *motor, uint16_t pwm_val) {
	HAL_GPIO_WritePin(motor->in_ports[0], motor->in_pins[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->in_ports[1], motor->in_pins[1], GPIO_PIN_SET);

	l298n_drive(motor->pwm_channel, pwm_val);
}

void l298n_move_rev_single(motor_t *motor, uint16_t pwm_val) {
	HAL_GPIO_WritePin(motor->in_ports[0], motor->in_pins[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(motor->in_ports[1], motor->in_pins[1], GPIO_PIN_RESET);

	l298n_drive(motor->pwm_channel, pwm_val);
}

void l298n_stop_single(motor_t *motor) {
	// Input into both of the IN pins
	HAL_GPIO_WritePin(motor->in_ports[0], motor->in_pins[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->in_ports[1], motor->in_pins[1], GPIO_PIN_RESET);

	// Enable pin should remain high
}

//>>>> TWO MOTOR DRIVE <<<<//
void l298n_move_fwd(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_a, uint16_t pwm_val_b) {
	l298n_move_fwd_single(motor_left, pwm_val_a);
	l298n_move_fwd_single(motor_right, pwm_val_b);
}

void l298n_move_rev(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_a, uint16_t pwm_val_b) {
	l298n_move_rev_single(motor_left, pwm_val_a);
	l298n_move_rev_single(motor_right, pwm_val_b);
}

void l298n_stop(motor_t *motor_left, motor_t *motor_right) {
	l298n_stop_single(motor_left);
	l298n_stop_single(motor_right);
}

void l298n_rotate(motor_t *motor_left, motor_t *motor_right, rotation_t rotation) {

}
