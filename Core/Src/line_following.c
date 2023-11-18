#include "line_following.h"
#include "colour_sensor.h"

// PID Gain Constants
static const double Kp = 50;
static const double Kd = 0;
static const double Ki = 0;

static const double GOAL =3001;
static const double STEERING_FACTOR = 1;  //TODO: SCALE THE VALUES SO THAT (I.E. HOW MUCH THE THING SHOULD TURN)
static const double RPM2PWM_FACTOR = 1;  //TODO: ADJUST K TO CONVERT RPM TO PWM HERE


double getPathLinePosition(void){
	double linePosition = getPositionOfColourSource(RED);
	return linePosition;
}


double PIDAlgorithm(double currentLinePosition) {
	static double previousError = 0;

	double error = GOAL - currentLinePosition;

	double errorDerivative = error - previousError;
	double errorIntegral = errorIntegral + error;

	double steeringValue = Kp*error + Ki*errorIntegral + Kd*errorDerivative;

	previousError = error;

	return STEERING_FACTOR*steeringValue;
	
}


double convertRPM2PWM(double rpm){
	return RPM2PWM_FACTOR*rpm;
}


void followLine(motor_t *leftMotor, motor_t *rightMotor){
	double linePosition = getPathLinePosition();
	double steeringAdjustment = PIDAlgorithm(linePosition);
	
	// this "left vs right" of the positive/negative sign of the steeringAdjustment depends on the sensor numbering
	if (steeringAdjustment > 0){  // is on the right
		double newRPM = MAX_RPM - steeringAdjustment;
		if (newRPM < MIN_RPM) {  // TODO: WHAT IF WE ACTUALLY NEED THE MOTOR TO NOT MOVE?
			newRPM = MIN_RPM;  
		}

		double newPWM = convertRPM2PWM(newRPM);

		tb6612fng_move_fwd_single(rightMotor, newPWM);
		tb6612fng_move_fwd_single(leftMotor, MAX_PWM);
	}

	else { // steeringAdjustment is negative (line is to the left)
		double newRPM = MAX_RPM + steeringAdjustment;
		if (newRPM < MIN_RPM) {  // TODO: WHAT IF WE ACTUALLY NEED THE MOTOR TO NOT MOVE?
			newRPM = MIN_RPM;
		}

		double newPWM = convertRPM2PWM(newRPM);

		tb6612fng_move_fwd_single(rightMotor, MAX_PWM);
		tb6612fng_move_fwd_single(leftMotor, newPWM);
	}
}
