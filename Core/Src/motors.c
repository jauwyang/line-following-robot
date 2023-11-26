#include "motors.h"

#include <stdbool.h>
#include <stm32f4xx_hal.h>

#define EXP_POINTS_COUNT		(uint8_t) 10
#define TICK_FACTOR				(uint16_t) 2000	// TIM10 on APB2 (84MHz), PSC = 42000 so f_clock is 2000 kHz, ARR = 65535

extern TIM_HandleTypeDef htim10;

/**
 * Function pointers type definitions for motor single and double drive
 */
typedef void (*moveSingle)(motor_t*, uint16_t);
typedef void (*move)(motor_t*, motor_t*, uint16_t, uint16_t);

/**
 * Characterization points
 */
static DataPoint linearPoints[EXP_POINTS_COUNT] = {
	// Point 1
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 2
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 3
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 4
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 5
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 5
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 7
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 8
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 9
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 10
	{
	 .displacement = 1,
	 .timeSec = 1
	},
};

static DataPoint rotatePoints[EXP_POINTS_COUNT] = {
	// Point 1
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 2
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 3
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 4
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 5
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 5
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 7
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 8
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 9
	{
	 .displacement = 1,
	 .timeSec = 1
	},

	// Point 10
	{
	 .displacement = 1,
	 .timeSec = 1
	},
};

static double interpolateForTime(const double targetDisplacement, DataPoint experimentalPoints[], const uint16_t dataPointsCount) {
	// we should pass +/- distance values (because the motor might behave differently in different directions?). In other words, we should test both forward and backwards directions
	bool dataPointExists = false;

	uint16_t mid;
	uint16_t left = 0;
	uint16_t right = dataPointsCount - 1;

	// checks if the distance has already been recorded (via binary search)
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (experimentalPoints[mid].displacement == targetDisplacement) {
		  dataPointExists = true;
		  break;
		} else if (experimentalPoints[mid].displacement < targetDisplacement) {
		  left = mid + 1;
		} else {
		  right = mid - 1;
		}
	}

	if (dataPointExists == true) {
		return experimentalPoints[mid].timeSec;
	} else {
		// interpolates if the value is not found
		if (mid == 0) {
		  mid++;
		}
	}
	// interpolates using given point and previous point
	double interpolatedTime = experimentalPoints[mid - 1].timeSec +
	  (targetDisplacement - experimentalPoints[mid - 1].displacement) * ((experimentalPoints[mid].timeSec - experimentalPoints[mid - 1].timeSec) /
	  (experimentalPoints[mid].displacement - experimentalPoints[mid - 1].displacement));

	return interpolatedTime;
}

/**
* User-facing API
*/
void travelSetDistance(motor_t *motorLeft, motor_t *motorRight, const LinearParams params) {
	uint16_t time = (uint16_t)(interpolateForTime(params.distanceCm, linearPoints, EXP_POINTS_COUNT));

	// Obtain a handle to the appropriate double motor drive function
	move moveFunction = (params.direction == DIR_FORWARD) ? &tb6612fng_move_fwd : &tb6612fng_move_rev;

	// Get the current time (order of ms)
	uint16_t timerValue =  __HAL_TIM_GET_COUNTER(&htim10);
	while (__HAL_TIM_GET_COUNTER(&htim10) - timerValue >= (time * TICK_FACTOR)) {
		moveFunction(motorLeft, motorRight, LINEAR_PWM, LINEAR_PWM);
	}
}

void rotateRobot(motor_t *motorLeft, motor_t *motorRight, const RotationParams params) {
	uint16_t time = (uint16_t)(interpolateForTime(params.angle, rotatePoints, EXP_POINTS_COUNT));

	uint16_t timerValue = __HAL_TIM_GET_COUNTER(&htim10);
	while (__HAL_TIM_GET_COUNTER(&htim10) - timerValue >= (time * TICK_FACTOR)) {
		if (params.direction == DIR_CW) {
			tb6612fng_move_fwd_single(motorLeft, ROTATION_PWM);
			tb6612fng_move_rev_single(motorRight, ROTATION_PWM);
		} else {
			tb6612fng_move_fwd_single(motorRight, ROTATION_PWM);
			tb6612fng_move_rev_single(motorLeft, ROTATION_PWM);
		}
	}
}
