#ifndef LINE_FOLLOWING_ROBOT_DRV8833_DRV8833_H
#define LINE_FOLLOWING_ROBOT_DRV8833_DRV8833_H

#include <stdint.h>

/**
 * Constants
 */
// TODO: Motor Characterization
static const uint32_t MIN_RPM = 0;
static const uint32_t MAX_RPM = 0;

static const uint32_t MIN_PWM = 90;
static const uint32_t MAX_PWM = 570;


/**
 * @brief Control structure for the motor driver.
 * Note: This motor driver does not have an enable pin that influences motor speed.
 * See https://www.ti.com/lit/ds/symlink/drv8833.pdf?ts=1700016243532
 */
typedef struct _motor_t {

	uint32_t pwm_ch_xin1;
	uint32_t pwm_ch_xin2;

} motor_t;

typedef enum _direction_e {

	DIR_CW = 0,
	DIR_CCW

} direction_e;

typedef struct _rotation_t {

	uint16_t angle;
	direction_e direction;

} rotation_t;


/**
 * User-facing API
 */

//>>>> SINGLE MOTOR DRIVE <<<<//
void drv8833_move_fwd_single(motor_t *motor, uint16_t pwm_val);
void drv8833_move_rev_single(motor_t *motor, uint16_t pwm_val);
void drv8833_stop_single(motor_t *motor);

//>>>> TWO MOTOR DRIVE <<<<//
void drv8833_move_fwd(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right);
void drv8833_move_rev(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right);
void drv8833_stop(motor_t *motor_left, motor_t *motor_right);
void drv8833_rotate(motor_t *motor_left, motor_t *motor_right, rotation_t rotation);


#endif // LINE_FOLLOWING_ROBOT_DRV8833_DRV8833_H
