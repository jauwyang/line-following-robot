#include "line_following.h"
#include "colour_sensor.h"
#include <stm32f4xx_hal.h>
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

char pidstuff[256];

// PID Gain Constants
/**
 * TESTS
 * P I D
 * 250, 0, 0
 * 285, 60, 0
 * 285 50 0
 * 275, 85, 0
 * 275 * 1.15, 90 * 1.15, 0.5, RPM = 550 * 0.8
 * 275 * 1.2, 90 * 1.2, 0.5, RPM = 550 * 0.8
 */
const double Sf = 1.2;

static const double Kp = 275 * Sf; //250 is good value
static const double Kd = 90 * Sf; //5
static const double Ki = 0.5; // 0.01

static const double GOAL = 2;
static const double STEERING_FACTOR = 1;

// Use the previous error
static double previousError = 0;
static double error = 0;

double PIDAlgorithm(double currentLinePosition) {
	static double errorIntegral = 0;

	error = GOAL - 1 * currentLinePosition;

	double errorDerivative = error - previousError;
	errorIntegral = errorIntegral + error;

	double steeringValue = Kp*error + Ki*errorIntegral + Kd*errorDerivative;

	previousError = error;

	return STEERING_FACTOR*steeringValue;
}

void followLine(motor_t *leftMotor, motor_t *rightMotor){
	double linePosition = getPositionOfColourSource(RED);

	/**
	 * Check if none of the sensors are detecting the line (off the line).
	 * Use the previousError to determine which way to steer.
	 * If currentLinePosition > GOAL: steer right
	 * If currentLinePosition < GOAL: steer left
	 */
	/*while (linePosition == -1) {
		if (previousError < 0) {
			tb6612fng_move_fwd(leftMotor, rightMotor, MIN_PWM, MAX_PWM);

		} else {
			tb6612fng_move_fwd(leftMotor, rightMotor, MAX_PWM, MIN_PWM);
		}

		// Update the linePosition each iteration
		linePosition = getPositionOfColourSource(RED);
	}*/

	if (linePosition == -1) {
		tb6612fng_stop(leftMotor, rightMotor);
		return;
	}

	// At least one sensor is now back on the line; proceed with computing the steering adjustment
	double steeringAdjustment = PIDAlgorithm(linePosition);
	double leftNewPWM = 0;
	double rightNewPWM = 0;

	// Use MAX_PWM: all newPWMs are less than MAX_PWM
	if (error < 0){  // is on the right, need to turn right
		if (steeringAdjustment < 0) {
			rightNewPWM = MAX_PWM + steeringAdjustment;
		} else {
			rightNewPWM = MAX_PWM - steeringAdjustment;
		}

		if (rightNewPWM < MIN_PWM) {
			rightNewPWM = MIN_PWM;
		}

		if (rightNewPWM > MAX_PWM) {
			rightNewPWM = MAX_PWM;
		}

		leftNewPWM = MAX_PWM;
		tb6612fng_move_fwd(leftMotor, rightMotor, rightNewPWM, leftNewPWM); // FLIPPED IS CORRECT
	}

	else { // Line is on the left, need to turn left
		if (steeringAdjustment > 0) {
			leftNewPWM = MAX_PWM - steeringAdjustment;
		} else {
			leftNewPWM = MAX_PWM + steeringAdjustment;
		}
		if (leftNewPWM < MIN_PWM) {
			leftNewPWM = MIN_PWM;
		}

		if (leftNewPWM > MAX_PWM) {
			leftNewPWM = MAX_PWM;
		}

		rightNewPWM = MAX_PWM;
		tb6612fng_move_fwd(leftMotor, rightMotor, rightNewPWM, leftNewPWM); //FLIPPED IS CORRECT
	}

	// Error, steering value, left motor speed, right motor speed
//	sprintf(pidstuff, "ERROR: %d  |  STEER: %d  |  SPLEFT: %d  |  SPRIGHT: %d  \r\n", (int)error, (int)steeringAdjustment, (int)leftNewPWM, (int)rightNewPWM);
//	HAL_UART_Transmit(&huart2, (uint8_t *)pidstuff, strlen(pidstuff), HAL_MAX_DELAY);
}
