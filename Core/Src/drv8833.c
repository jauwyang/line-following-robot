#include "drv8833/drv8833.h"

#include <stdio.h>
#include <stm32f4xx_hal.h>

#define PWM_CCR_MAX_DUTY_CYCLE (uint16_t) 1000

extern TIM_HandleTypeDef htim1;

/**
 * TIM1_CH1: AIN1
 * TIM1_CH2: AIN2
 * TIM1_CH3: BIN1
 * TIM1_CH4: BIN2
 *
 * Use slow decay (brake) mode to handle recirculation current
 */
static void drv8833_pwm_drive(const uint32_t pwm_channel, const uint16_t pwm_val) {
	switch (pwm_channel) {
	case TIM_CHANNEL_1:
		htim1.Instance->CCR1 = pwm_val;
		break;
	case TIM_CHANNEL_2:
		htim1.Instance->CCR2 = pwm_val;
		break;
	case TIM_CHANNEL_3:
		htim1.Instance->CCR3 = pwm_val;
		break;
	case TIM_CHANNEL_4:
		htim1.Instance->CCR4 = pwm_val;
		break;
	default:
		printf("%s\r\n", "Invalid TIM channel passed in.");
		break;
	}
}

//>>>> SINGLE MOTOR DRIVE <<<<//

void drv8833_move_fwd_single(motor_t *motor, const uint16_t pwm_val) {
	// Keep xIN1 HIGH, PWM control xIN2
	drv8833_pwm_drive(motor->pwm_ch_xin1, PWM_CCR_MAX_DUTY_CYCLE);
	drv8833_pwm_drive(motor->pwm_ch_xin2, pwm_val);
}

void drv8833_move_rev_single(motor_t *motor, const uint16_t pwm_val) {
	// PWM control xIN1, Keep xIN2 HIGH
	drv8833_pwm_drive(motor->pwm_ch_xin1, pwm_val);
	drv8833_pwm_drive(motor->pwm_ch_xin2, PWM_CCR_MAX_DUTY_CYCLE);
}

void drv8833_stop_single(motor_t *motor) {
	// Drive xIN1 and xIN2 HIGH
	drv8833_pwm_drive(motor->pwm_ch_xin1, PWM_CCR_MAX_DUTY_CYCLE);
	drv8833_pwm_drive(motor->pwm_ch_xin2, PWM_CCR_MAX_DUTY_CYCLE);
}


//>>>> TWO MOTOR DRIVE <<<<//
void drv8833_move_fwd(motor_t *motor_left, motor_t *motor_right, const uint16_t pwm_val_left, const uint16_t pwm_val_right) {
	drv8833_move_fwd_single(motor_left, pwm_val_left);
	drv8833_move_fwd_single(motor_right, pwm_val_right);
}

void drv8833_move_rev(motor_t *motor_left, motor_t *motor_right, const uint16_t pwm_val_left, const uint16_t pwm_val_right) {
	drv8833_move_rev_single(motor_left, pwm_val_left);
	drv8833_move_rev_single(motor_right, pwm_val_right);
}

void drv8833_stop(motor_t *motor_left, motor_t *motor_right) {
	drv8833_stop_single(motor_left);
	drv8833_stop_single(motor_right);
}

// TODO: Implement for on the spot rotation
void drv8833_rotate(motor_t *motor_left, motor_t *motor_right, const rotation_t rotation) {

}
