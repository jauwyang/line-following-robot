#include "IR_line_following.h"
#include "IR_colour_sensor.h"

// PID Gain Constants
static const double Kp = 1;
static const double Kd = 0;
static const double Ki = 0;


double IR_getPathLinePosition(){
	double linePosition = IR_getPositionOfColourSource(SENSOR_COUNT);
	return linePosition;
}

double IR_PIDAlgorithm(double currentLinePosition) {
	static double previousError = 0;

	double error = GOAL - currentLinePosition;

	double errorDerivative = error - previousError;
	double errorIntegral = errorIntegral + error;

	double steeringValue = Kp*error + Ki*errorIntegral + Kd*errorDerivative;

	previousError = error;

	return steeringValue;
	//TODO: SCALE THE VALUES SO THAT (I.E. HOW MUCH THE THING SHOULD TURN)
}


void IR_followLine(){
	double linePosition = IR_getPathLinePosition();
	double steeringAdjustment = IR_PIDAlgorithm(linePosition);

	if (steeringAdjustment > 0){
		//TODO: subtract from max speed/PWM
		//TODO: make sure new motor value does not exceed bounds (correct it)
		//TODO: THE POSITIVE/NEGATIVE VALUE ABOUT THE "GOAL" IS DEPENDENT ON THE DIRECTION
		// 		OF SENSOR ARRAY NUMBERING (I.E. WHETHER SENSOR 0 STARTS ON THE LEFT MOST OR
		//		RIGHT MOST SENSOR) SO YOU EITHER ADD TO APPLY THIS MOTOR CHANGE TO EITHER THE LEFT OR RIGHT ACCORDINGLY
	}
	else { // is negative
		//TODO: apply same as above here (but keep in mind this is negative)
	}
}