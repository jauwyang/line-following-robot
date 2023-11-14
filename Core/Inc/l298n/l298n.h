#ifndef LINE_FOLLOWING_ROBOT_DCMOTOR_L298N_L298N_H
#define LINE_FOLLOWING_ROBOT_DCMOTOR_L298N_L298N_H

#include <stm32f4xx_hal.h>

/**
 * Wrapper around port and pin definitions for a single motor
 * connected to the L298N motor driver
 */
typedef struct _motor_t {

	GPIO_TypeDef* in_ports[2];
	uint16_t in_pins[2];
	uint32_t pwm_channel;

} motor_t;

typedef enum _direction_e {

	DIR_CW = 0,
	DIR_CCW

} direction_e;

typedef struct _rotation_t {

	uint16_t angle;
	direction_e direction;

} rotation_t;

typedef struct _l298n_drive_t {

	motor_t *motor_left;
	motor_t *motor_right;
	uint16_t pwm_val_left;
	uint16_t pwm_val_right;

} l298n_drive_t;

// TODO: Adjust based on further characterization
static const uint32_t MAX_RPM = 0;
static const uint32_t MIN_RPM = 0;
static const uint32_t MAX_PWM = 570;
static const uint32_t MIN_PWM = 90;

/**
 * User-facing API
 */

//>>>> SINGLE MOTOR DRIVE <<<<//
void l298n_move_fwd_single(motor_t *motor, uint16_t pwm_val);
void l298n_move_rev_single(motor_t *motor, uint16_t pwm_val);
void l298n_stop_single(motor_t *motor);

//>>>> TWO MOTOR DRIVE <<<<//
void l298n_move_fwd(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right);
void l298n_move_rev(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right);
void l298n_stop(motor_t *motor_left, motor_t *motor_right);
void l298n_rotate(motor_t *motor_left, motor_t *motor_right, rotation_t rotation);

#endif // LINE_FOLLOWING_ROBOT_DCMOTOR_L298N_L298N_H
