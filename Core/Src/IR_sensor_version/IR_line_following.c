#include "IR_sensor_version/IR_line_following.h"
#include "IR_sensor_version/IR_sensor.h"
//#include "l298n/l298n.h"

// PID Gain Constants
static const double Kp = 1;
static const double Kd = 0;
static const double Ki = 0;
static const double GOAL = SENSOR_COUNT / 2; // JOSH MIGHT NEED TO SCALE THIS


double IR_getPathLinePosition(const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount) {
	double linePosition = IR_getPositionOfColourSource(IR_rawSensorReadings, sensorCount);
	return linePosition;
}

double IR_PIDAlgorithm(double currentLinePosition) {
	static double previousError = 0;
	static double errorIntegral = 0;

	double error = GOAL - currentLinePosition;

	double errorDerivative = error - previousError;
	errorIntegral = errorIntegral + error;

	double steeringValue = Kp*error + Ki*errorIntegral + Kd*errorDerivative;

	previousError = error;

	return steeringValue;
	//TODO: SCALE THE VALUES SO THAT (I.E. HOW MUCH THE THING SHOULD TURN)
}


double convertRPM2PWM(double RPM){
	return 0;
}


// NOTE: THE SENSORS ARE ARRANGED FROM 0 TO N FROM LEFT TO RIGHT IN THE ROBOT'S POV
void IR_followLine(motor_t *leftMotor, motor_t *rightMotor, const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount){
	double linePosition = IR_getPathLinePosition(IR_rawSensorReadings, sensorCount);
	double steeringAdjustment = IR_PIDAlgorithm(linePosition);

	if (steeringAdjustment > 0){ // line is to the right (in accordance to NOTE above)
		double newRPM = MAX_RPM - steeringAdjustment;
		if (newRPM < MIN_RPM){
			newRPM = MIN_RPM;
		}
		double newPWM = convertRPM2PWM(newRPM);
		l298n_move_fwd_single(rightMotor, newPWM);
		l298n_move_fwd_single(leftMotor, MAX_PWM);

		//TODO: subtract from max speed/PWM
		//TODO: make sure new motor value does not exceed bounds (correct it)
		//TODO: THE POSITIVE/NEGATIVE VALUE ABOUT THE "GOAL" IS DEPENDENT ON THE DIRECTION
		// 		OF SENSOR ARRAY NUMBERING (I.E. WHETHER SENSOR 0 STARTS ON THE LEFT MOST OR
		//		RIGHT MOST SENSOR) SO YOU EITHER ADD TO APPLY THIS MOTOR CHANGE TO EITHER THE LEFT OR RIGHT ACCORDINGLY
	}
	else { // steeringAdjustment is negative (line is to the left)
		//TODO: apply same as above here (but keep in mind this is negative)
		double newRPM = MAX_RPM + steeringAdjustment;
		if (newRPM < MIN_RPM){
			newRPM = MIN_RPM;
		}
		double newPWM = convertRPM2PWM(newRPM);
		l298n_move_fwd_single(rightMotor, MAX_PWM);
		l298n_move_fwd_single(leftMotor, newPWM);
	}
}
