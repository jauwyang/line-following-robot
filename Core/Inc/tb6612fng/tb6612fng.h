#ifndef LINE_FOLLOWING_ROBOT_MOTOR_TB6612FNG_H
#define LINE_FOLLOWING_ROBOT_MOTOR_TB6612FNG_H

#include <stm32f4xx_hal.h>

static const uint32_t MAX_RPM = 0;
static const uint32_t MIN_RPM = 0;
static const uint32_t MAX_PWM = 570;
static const uint32_t MIN_PWM = 90;


typedef enum _direction_e {

	DIR_CW = 0,
	DIR_CCW

} direction_e;

typedef struct _rotation_t {

	uint16_t angle;
	direction_e direction;

} rotation_t;

/**
 * Port-pin sequence is as follows:
 * AIN1, AIN2, STBY (Standby)
 */
typedef struct _motor_t {

	GPIO_TypeDef* ports[2];
	uint16_t pins[2];
	uint32_t pwm_channel;

} motor_t;


/**
 * User-facing API
 * Assume fwd is CW
 */

//>>>> SINGLE MOTOR DRIVE <<<<//
void tb6612fng_move_fwd_single(motor_t *motor, uint16_t pwm_val);
void tb6612fng_move_rev_single(motor_t *motor, uint16_t pwm_val);
void tb6612fng_stop_single(motor_t *motor);

//>>>> TWO MOTOR DRIVE <<<<//
void tb6612fng_move_fwd(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right);
void tb6612fng_move_rev(motor_t *motor_left, motor_t *motor_right, uint16_t pwm_val_left, uint16_t pwm_val_right);
void tb6612fng_stop(motor_t *motor_left, motor_t *motor_right);
void tb6612fng_rotate(motor_t *motor_left, motor_t *motor_right, rotation_t rotation);

#endif // LINE_FOLLOWING_ROBOT_MOTOR_TB6612FNG_H
