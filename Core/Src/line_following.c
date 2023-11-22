#include "line_following.h"
#include "colour_sensor.h"

// PID Gain Constants
static const double Kp = 50;
static const double Kd = 0;
static const double Ki = 0;

static const double GOAL = 200;
static const double STEERING_FACTOR = 1;

static double previousError = 0;

double PIDAlgorithm(double currentLinePosition) {
	static double errorIntegral = 0;

	double error = GOAL - 100 * currentLinePosition;

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
	while (linePosition == -1) {
		if (previousError < 0) {
			tb6612fng_move_fwd(leftMotor, rightMotor, MAX_PWM, 0.25 * MAX_PWM);

		} else {
			tb6612fng_move_fwd(leftMotor, rightMotor, 0.25 * MAX_PWM, MAX_PWM);
		}

		// Update the linePosition each iteration
		linePosition = getPositionOfColourSource(RED);
	}

	// At least one sensor is now back on the line; proceed with computing the steering adjustment
	double steeringAdjustment = PIDAlgorithm(linePosition);

	// Use MAX_PWM: all newPWMs are less than MAX_PWM
	if (steeringAdjustment < 0){  // is on the right
		double newPWM = MAX_PWM + steeringAdjustment;
		if (newPWM < MIN_PWM) {
			newPWM = MIN_PWM;
		}

		tb6612fng_move_fwd(leftMotor, rightMotor, MAX_PWM, newPWM);
	}

	else { // steeringAdjustment is negative (line is to the left)
		double newPWM = MAX_PWM - steeringAdjustment;
		if (newPWM < MIN_PWM) {
			newPWM = MIN_PWM;
		}

		tb6612fng_move_fwd(leftMotor, rightMotor, newPWM, MAX_PWM);
	}
}
